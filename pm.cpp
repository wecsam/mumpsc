/*===========================================================================
 *   Mumps Compiler Run-Time Support Functions
 *      Pattern Matching Operations, supported by PCRE, the Perl-Compatible
 *      Regular Expressions Library
 *   Copyright (c) 2002 by Matthew Lockner
 *   lockner@cns.uni.edu
 *
 *   This library is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU Lesser General Public
 *   License as published by the Free Software Foundation; either
 *   version 2.1 of the License, or (at your option) any later version.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *   Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public
 *   License along with this library; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *===========================================================================*/

/* pm.c - Mumps Runtime Library
 *
 * Implementation of the Mumps pattern match operator.
 * The pm() function implements the '?' operator in Mumps, by translating
 * Mumps patterns into Perl-compatible regular expressions.  These are then
 * compiled and executed using the PCRE library, resulting in a Boolean
 * truth value.  perlmatch() additionally provides support for direct
 * usage of Perl regular expressions in Mumps source.
 *
 * EBNF of Mumps patterns used:
 *
 * pattern         ::= {pattern_atom}
 * pattern_atom    ::= count pattern_element
 * count           ::= int | '.' | '.' int
 *                   | int '.' | int '.' int
 * pattern_element ::= pattern_code {pattern_code} | string | alternation
 * pattern_code    ::= 'A' | 'C' | 'E' | 'L' | 'N' | 'P' | 'U'
 * alternation     ::= '(' pattern_atom {',' pattern_atom} ')'
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <pcre.h>

#include <mumpsc/defines.h>
#include <mumpsc/fcns.h>

char *sym_(int symflg, unsigned char *a, unsigned char *b, struct MSV * svPtr);

void sigint(int);

/* ASCII 210 being used to represent embedded quotes in literals */
#define DOUBLE_QUOTE '\xd2'

/* Max number of backreferences; maximum of 99 supported by PCRE */
#define MAX_BACKREFS 99

/* Length of 'offsets' buffer in perl_pm */
#define OFFSET_BUF_LEN (MAX_BACKREFS * 3 / 2 + 1)

/* Ubiquitous min macro */
#define min(x,y) ((x) < (y) ? (x) : (y))

enum token_type {
     INT, STRING, LPAREN, RPAREN, COMMA,
     DOT, PATTERN_CODE, EOT, ERROR
};

struct token {
    enum token_type kind;
    struct bstring  text;
};

struct scanner {
    const char*  input;
    const char*  current_char;
    struct token current_token;
};

struct parser {
    struct token current_token;
    struct scanner s;
};

static struct scanner  new_scanner (const char[]);
static struct token    scan        (struct scanner*);
static enum token_type scan_token  (struct scanner*);
static void            take_char   (struct scanner*);

static struct parser  new_parser (struct scanner);
static void           parse      (struct parser*, char* result);
static struct bstring parse_pattern           (struct parser*);
static struct bstring parse_pattern_atom      (struct parser*);
static struct bstring parse_count             (struct parser*);
static struct bstring parse_pattern_element   (struct parser*);
static struct bstring parse_pattern_atom_list (struct parser*);
static struct bstring leaning_toothpickize    (const struct bstring);
static void           accept     (struct parser*, const enum token_type);
static void           accept_it  (struct parser*);

int perl_pm (const char[], const char[], const int,struct MSV *);
static void syntax_error (const char[], const char[], const int);

static const char pattern_codes[] = "ACELNPU";
static const char * const char_classes[] = {
    "[:alpha:]", "[:cntrl:]", "[:print:][:cntrl:]",
    "[:lower:]", "\\d", "[:punct:]", "[:upper:]"
};

/*===========================================================================*
 *                                    pm                                     *
 *===========================================================================*/
int pm (const unsigned char string[], const unsigned char pattern[],struct MSV * svPtr) {
    struct parser p = new_parser (new_scanner ((char*) pattern));
    char pcre_pattern[STR_MAX];

    parse (&p, pcre_pattern);
    if (PM_DEBUG) printf ("%s\n%s\n", pattern, pcre_pattern);
    return perl_pm ((char*) string, pcre_pattern, 0,svPtr);
}

/*===========================================================================*
 *                                 perlmatch                                 *
 *===========================================================================*/
const char * perlmatch (struct MSV * svPtr, char* ignored, char* string, char* pattern) {
    return (const char *) (perl_pm ((const char *) string, (const char *) pattern, 1,svPtr) ? "1" : "0");
      }

int perlcpp (char* ignored, const char* string, const char* pattern, struct MSV * svPtr) {
    return perl_pm (string, pattern, 1,svPtr);
      }

/*===========================================================================*
 *                                  perl_pm                                  *
 *===========================================================================*/
int perl_pm (const char string[],
             const char pattern[],
             const int allow_partial,
             struct MSV * svPtr) {
    const char* error;
    int errptr, offsets[OFFSET_BUF_LEN];
    int length = strlen ((char*) string), matched;
    pcre* regex;
    const char* substr;
    int i, e, nmatches;
    unsigned char backref[34] = {'_', '0', '0', '\0'};

    regex = pcre_compile (pattern, 0, &error, &errptr, NULL);
    if (regex == NULL) {
        fprintf (stderr, "*** Unable to compile pattern '%s'\n", pattern);
        sigint (100);
    }
    nmatches = pcre_exec (regex, NULL, string, length,
                          0, 0, offsets, OFFSET_BUF_LEN);
    pcre_free (regex);
    matched = nmatches >= 0 && 
        (allow_partial || (offsets[1] - offsets[0]) == length);
    if (!allow_partial || nmatches < 2) return matched;
    for (i = 1; i < min(nmatches, MAX_BACKREFS + 1); i++) {
        if ((e = pcre_get_substring (string, offsets,
                                     nmatches, i, &substr)) < 0) {
            fprintf (stderr,
                    "*** Could not get pattern backreferences: %d\n", e);
            sigint (100);
        }

        sprintf ( (char *) &backref[1], "%d", i);
        sym_ (SymStore, backref, (unsigned char*) substr,svPtr);
        pcre_free_substring (substr);
    }
    for (i = nmatches; i <= MAX_BACKREFS; i++) {
        sprintf ( (char *) &backref[1], "%d", i);
        sym_ (SymDeleteExplicit, backref, (unsigned char *) "",svPtr);
    }
    return matched;
}

/*===========================================================================*
 *                                new_scanner                                *
 *===========================================================================*/
struct scanner new_scanner (const char input[]) {
    struct token t;
    struct scanner s;

    t.kind = ERROR;
    t.text = new_bstring ("");
    s.input = input;
    s.current_char = input;
    s.current_token = t;
    return s;
}

/*===========================================================================*
 *                                   scan                                    *
 *===========================================================================*/
struct token scan (struct scanner* s) {
    s->current_token.text = new_bstring ("");
    s->current_token.kind = scan_token (s);
    return s->current_token;
}

/*===========================================================================*
 *                                scan_token                                 *
 *===========================================================================*/
enum token_type scan_token (struct scanner* s) {
    switch (toupper (*(s->current_char))) {
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            do {
                take_char (s);
            } while (isdigit (*(s->current_char)));
            return INT;
        case '"':
            take_char (s);
            while (*(s->current_char) != '"')
                take_char (s);
            take_char (s);
            return STRING;
        case '(':
            take_char (s);
            return LPAREN;
        case ')':
            take_char (s);
            return RPAREN;
        case ',':
            take_char (s);
            return COMMA;
        case '.':
            take_char (s);
            return DOT;
        case 'A': case 'C': case 'E': case 'L':
        case 'N': case 'P': case 'U':
            take_char (s);
            return PATTERN_CODE;
        case '\0':
            return EOT;
        default:
            syntax_error ("Syntax error in pattern: invalid character",
                          s->input, 1 + s->current_char - s->input);
            take_char (s);
            return ERROR;
    }
}

/*===========================================================================*
 *                                 take_char                                 *
 *===========================================================================*/
void take_char (struct scanner* s) {
    bcatchr (&(s->current_token.text), *(s->current_char));
    s->current_char++;
}

/*===========================================================================*
 *                                new_parser                                 *
 *===========================================================================*/
struct parser new_parser (struct scanner s) {
    struct parser result;

    result.current_token.kind = ERROR;
    result.current_token.text = new_bstring ("");
    result.s = s;
    return result;
}

/*===========================================================================*
 *                                   parse                                   *
 *===========================================================================*/
void parse (struct parser* p, char* s) {
    struct bstring result;

    p->current_token = scan (&(p->s));
    result = parse_pattern (p);
    if (p->current_token.kind != EOT) {
        syntax_error ("Syntax error in pattern",
                      p->s.input, p->s.current_char - p->s.input);
    }
    make_cstring (s, result);
}

/*===========================================================================*
 *                               parse_pattern                               *
 *===========================================================================*/
struct bstring parse_pattern (struct parser* p) {
    struct bstring result = new_bstring ("");

    while (p->current_token.kind == INT
            || p->current_token.kind == DOT) {
        result = bstrcat (result, parse_pattern_atom (p));
    }
    return result;
}

/*===========================================================================*
 *                            parse_pattern_atom                             *
 *===========================================================================*/
struct bstring parse_pattern_atom (struct parser* p) {
    struct bstring count = parse_count (p);
    struct bstring element = parse_pattern_element (p);

    return bstrcat (element, count);
}

/*===========================================================================*
 *                                parse_count                                *
 *===========================================================================*/
struct bstring parse_count (struct parser* p) {
    struct bstring result;

    switch (p->current_token.kind) {
        case INT: {
            struct bstring lowerbound = p->current_token.text;

            accept_it (p);
            result = new_bstring ("{");
            switch (p->current_token.kind) {
                case DOT:
                    accept_it (p);
                    result = bstrcat (result,
                             bstrcat (lowerbound, new_bstring (",")));
                    if (p->current_token.kind == INT) {
                        result = bstrcat (result,
                                          p->current_token.text);
                        accept_it (p);
                    }
                    break;
                default:
                    result = bstrcat (result, lowerbound);
                    break;
            }
            bcatchr (&result, '}');
            break;
        }
        default:        /* Must have been a DOT. */
            accept_it (p);
            if (p->current_token.kind == INT) {
                result = bstrcat (new_bstring ("{0,"),
                         bstrcat (p->current_token.text,
                                  new_bstring ("}")));
                accept_it (p);
            }
            else {
                result = new_bstring ("*");
            }
            break;
    }
    return result;
}

/*===========================================================================*
 *                           parse_pattern_element                           *
 *===========================================================================*/
struct bstring parse_pattern_element (struct parser* p) {
    struct bstring result;

    switch (p->current_token.kind) {
        case PATTERN_CODE:
            result = new_bstring ("[");
            do {
                int i = strchr (pattern_codes,
                                toupper (p->current_token.text.string[0]))
                        - pattern_codes;
                result = bstrcat (result, new_bstring (char_classes[i]));
                accept_it (p);
            } while (p->current_token.kind == PATTERN_CODE);
            bcatchr (&result, ']');
            break;
        case STRING:
            /* Grouping needed due to precedence issues */
            result = bstrcat (new_bstring ("("),
                              leaning_toothpickize (p->current_token.text));
            bcatchr (&result, ')');
            accept_it (p);
            break;
        case LPAREN:
            accept_it (p);
            result = bstrcat (new_bstring ("("),
                              parse_pattern_atom_list (p));
            accept (p, RPAREN);
            bcatchr (&result, ')');
            break;
        default:
            result = new_bstring ("");
            syntax_error ("Syntax error in pattern",
                          p->s.input, p->s.current_char - p->s.input);
            break;
    }
    return result;
}

/*===========================================================================*
 *                          parse_pattern_atom_list                          *
 *===========================================================================*/
struct bstring parse_pattern_atom_list (struct parser* p) {
    struct bstring result = parse_pattern_atom (p);

    while (p->current_token.kind == COMMA) {
        accept_it (p);
        bcatchr (&result, '|');
        result = bstrcat (result, parse_pattern_atom (p));
    }
    return result;
}

/*===========================================================================*
 *                                  accept                                   *
 *===========================================================================*/
void accept (struct parser* p, const enum token_type expected_kind) {
    if (p->current_token.kind != expected_kind) {
        syntax_error ("Syntax error in pattern",
                      p->s.input, p->s.current_char - p->s.input);
    }
    accept_it (p);
}

/*===========================================================================*
 *                                 accept_it                                 *
 *===========================================================================*/
void accept_it (struct parser* p) {
    p->current_token = scan (&(p->s));
}

/*===========================================================================*
 *                           leaning_toothpickize                            *
 *===========================================================================*/
struct bstring leaning_toothpickize (const struct bstring unmangled) {
    struct bstring result = new_bstring ("");
    int i;

    for (i = 0; i < unmangled.length; i++) {
        if (unmangled.string[i] == DOUBLE_QUOTE) {
            bcatchr (&result, '\"');
            continue;
        }
        if (unmangled.string[i] != '\"') {
            if (ispunct (unmangled.string[i])) {
                bcatchr (&result, '\\');
            }
            bcatchr (&result, unmangled.string[i]);
        }
    }
    return result;
}

/*===========================================================================*
 *                               syntax_error                                *
 *===========================================================================*/
void syntax_error (const char* msg, const char* line, const int pos) {
    printf ("*** %s\n", msg);
    printf ("%s\n", line);
    printf ("%*c\n", pos, '^');
    sigint (100);
}

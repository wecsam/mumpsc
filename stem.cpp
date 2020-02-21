//#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//#+    Mumps Compiler Run-Time Support Functions
//#+    Copyright (c) A.D. 2001, 2002, 2005 by Kevin C. O'Kane
//#+    kc.okane@gmail.com
//#+    http://threadsafebooks.com/
//#+
//#+    This library is free software; you can redistribute it and/or
//#+    modify it under the terms of the GNU Lesser General Public
//#+    License as published by the Free Software Foundation; either
//#+    version 2.1 of the License, or (at your option) any later version.
//#+
//#+    This library is distributed in the hope that it will be useful,
//#+    but WITHOUT ANY WARRANTY; without even the implied warranty of
//#+    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//#+    Lesser General Public License for more details.
//#+
//#+   You should have received a copy of the GNU Lesser General Public
//#+    License along with this library; if not, write to the Free Software
//#+    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//#+
//#+    http://www.cs.uni.edu/~okane
//#+
//#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/* stem.c - Mumps Runtime Library
 *
 * These functions provide support for word stemming, used as helper
 * functions for implementing $ZALTER and $ZNORMAL.  These may be
 * commonly used in text processing applications.
 */

#include <string.h>
#include <iostream>

#include <mumpsc/defines.h>
#include <mumpsc/fcns.h>
#include <mumpsc/strmove.h>

using namespace std;

int wstem(char *, int);

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * the following are locations in the conflation table
 *+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#define fin 1

struct endings {
    const char * prefix;               /* ending string */
    int offset;                 /* length */
    const char * replace;              /* replacement */
    };

const struct endings prefix[] = {

        {"pre", 3, "",},
        {"post", 4, "",},
        {"non", 3, "",},
        {"", 0, ""},
    };

const struct ends
        d_endings[] = {

        { "nned",  4, "n",    1, fin,},
        { "rated", 5, "rate", 4, fin,},
        { "cated", 5, "cate", 4, fin,},	/* sophisticated */
        { "iated", 5, "iate", 4, fin,},	/* associated */
        { "mated", 5, "mate", 4, fin,},	/* animated automated */
        { "gated", 5, "gate", 4, fin,},	/* aggregated */
        { "lated", 5, "late", 4, fin,}, /* accumulated */
        { "bated", 5, "bate", 4, fin,}, /* debate */
        { "nated", 5, "nate", 4, fin,}, /* dominated donated */
        { "ated",  4, "te",   2, fin,},
        { "eted",  4, "ete",  3, fin,},	/* competed deleted */
        { "ated",  4, "ate",  3, fin,},	/* alternated */
        { "kted",  4, "kt",   2, fin,},	/* marketed */
        { "oted",  4, "ote",  3, fin,},	/* promoted */
        { "uted",  4, "ute",  3, fin,},	/* distributed */
        { "sted",  4, "ste",  3, fin,},	/* wasted */
        { "ted",   3, "t",    1, fin,},
        { "ered",  4, "er",   2, fin,},	/* offered */
        { "dded",  4, "dd",   2, fin,},	/* added */
        { "rred",  4, "r",    1, fin,}, /* concurred */
        { "ored",  4, "r",    1, fin,}, /* sponsored */
        { "red",   3, "re",   2, fin,},
        { "zed",   3, "ze",   2, fin,},
        { "oded",  4, "de",   2, fin,},	/* coded */
        { "oved",  4, "ove",  3, fin,}, /* improved */
        { "eved",  4, "eve",  3, fin,},
        { "ied",   3, "y",    1, fin,},
        { "ced",   3, "ce",   2, fin,},
        { "olled", 4, "ol",   2, fin,},	/* controlled */
        { "alled", 5, "al",   2, fin,},	/* called */
        { "ooled", 5, "00l",  3, fin,},	/* cooled */
        { "oled",  4, "l",    1, fin,},	/* cooled */
        { "lled",  4, "l",    1, fin,},	/* installed */
        { "led",   3, "le",   2, fin,},	/* scheduled */
        { "reed",  4, "ree",  3, fin,},	/* disagreed */
        { "eed",   3, "eed",  3, fin,},	/* speed */
        { "ased",  4, "ased", 4, fin,},	/* based */
        { "ssed",  4, "ss",   2, fin,},	/* addressed */
        { "ccused",6, "ccuse",5, fin,},	/* accussed */
        { "used",  4, "us",   2, fin,},	/* focus */
        { "sed",   3, "se",   2, fin,},	/* closed */
        { "ved",   3, "ve",   2, fin,},	/* archived */
        { "ined",  4, "ne",   2, fin,},	/* defined */
        { "ned",   3, "n",    1, fin,},	/* assign */
        { "ached", 6, "ache", 4, fin,},	/* cached */
        { "hed",   3, "h",    1, fin,},	/* attached */
        { "ged",   3, "ge",   2, fin,},	/* charged */
        { "med",   3, "me",   2, fin,},	/* named */
        { "mmed",  4, "m",    1, fin,},	/* programmed */
        { "ued",   3, "ue",   2, fin,},	/* queued */
        { "mbed",  4, "b",    1, fin,},	/* bombed */
        { "bed",   3, "be",   2, fin,},	/* described */
        { "ended", 5, "end",  3, fin,},	/* intended */
        { "nded",  4, "d",    1, fin,},	/* abounded amended */
        { "aded",  4, "d",    1, fin,},	/* loaded */
        { "ded",   3, "de",   2, fin,},	/* included */
        { "ored",  4, "or",   2, fin,},	/* author */
        { "pped",  4, "p",    1, fin,},	/* overlapped */
        { "ed",    2, "",     0, fin,},
        { "",      0, "",     0, fin},
    },

s_endings[] = {

        { "tiveness", 5, "tive",  4, fin,},	/* competitiveness */
        { "iness",    5, "iness", 0, fin,},
        { "ness",     4, "",      0, fin,},
        { "ss",       2, "ss",    1, fin,},
        { "sses",     4, "ss",    2, fin,},
        { "xes",      3, "x",     1, fin,},
        { "xas",      3, "xas",   3, fin,},	/* texas */
        { "ious",     4, "ious",  4, fin,},
        { "nous",     4, "nous",  4, fin,},	/* asynchronous */
        { "uous",     4, "e",     1, fin,},	/* continuous */
        { "ous",      3, "",      0, fin,},
        { "aries",    5, "ary",   3, fin,},
        { "eries",    5, "ery",   3, fin,},
        { "ories",    5, "ory",   3, fin,},	/* accessories */
        { "tries",    5, "try",   4, fin,},	/* countries */
        { "ries",     4, "ries",  4, fin,},
        { "ies",      3, "y",     1, fin,},
        { "bios",     4, "bios",  4, fin,},	/* netbios */
        { "dus",      3, "dus",   3, fin,},	/* aldus */
        { "ves",      3, "ve",    2, fin,},
        { "res",      3, "re",    2, fin,},
        { "sis",      3, "sis",   3, fin,},
        { "ases",     4, "ase",   3, fin,},   /* bases */
        { "ses",      3, "s",     1, fin,},   /* focuses */
        { "ces",      3, "ce",    2, fin,},
        { "dos",      3, "dos",   3, fin,},
        { "des",      3, "de",    2, fin,},   /* decides */
        { "cus",      3, "cus",   3, fin,},	/* focus */
        { "tus",      3, "tus",   3, fin,},	/* lotus */
        { "ays",      3, "ay",    2, fin,},	/* gateways */
        { "nys",      3, "ny",    2, fin,},	/* companys */
        { "ys",       2, "ys",    2, fin,},	/* unisys */
        { "ius",      3, "ius",   3, fin,},	/* radius */
        { "is",       2, "",      0, fin,},
        { "hes",      3, "h",     1, fin,},	/* approach */
        { "ves",      3, "ve",    2, fin,},	/* archives */
        { "tes",      3, "te",    2, fin,},	/* competes */
        { "nus",      3, "nu",    2, fin,},	/* menus */
        { "us",       2, "us",    2, fin,},	/* virus */
        { "news",     4, "news",  4, fin,},	/* news */
        { "s",        1, "",      0, 0,},
        { "",         0, "",      0, 0},
    },

g_endings[] = {

        { "zing",     4, "ze",    2, fin,},
        { "olling",   5, "l",     2, fin,},
        { "lling",    5, "ll",    2, fin,},	/* calling */
        { "aling",    5, "al",    2, fin,},	/* appealing */
        { "eling",    5, "el",    2, fin,},   /* traveling */
        { "iling",    5, "il",    2, fin,},   /* ailing */
        { "ling",     4, "le",    2, fin,},
        { "writting", 8, "write", 5, fin,},
        { "iting",    5, "it",    2, fin,},
        { "ipting",   6, "ipt",   3, fin,},
        { "epting",   6, "ept",   3, fin,},   /* accepting */
        { "apting",   6, "apt",   3, fin,},   /* adapting */
        { "pting",    5, "t",     1, fin,},
        { "mming",    5, "m",     1, fin,},
        { "cting",    5, "ct",    2, fin,},
        { "inting",   6, "int",   3, fin,},
        { "nting",    5, "nt",    2, fin,},
        { "fting",    5, "ft",    2, fin,},
        { "rting",    5, "rt",    2, fin,},
        { "atting",   6, "at",    2, fin,},
        { "cating",   6, "cate",  4, fin,},	/* communicating */
        { "dating",   6, "date",  4, fin,},	/* accomodating */
        { "nating",   6, "nate",  4, fin,},	/* alternating */
        { "mating",   6, "mate",  4, fin,},	/* automating */
        { "eating",   6, "eate",  4, fin,},	/* automating */
        { "operating", 9, "operating", 9, fin,},   /* operating */
        { "pating",   6, "pate",  4, fin,},   /* dissipating */
        { "lating",   6, "late",  4, fin,},   /* accumulating */
        { "rating",   6, "rate",  4, fin,},   /* concentrating */
        { "ating",    5, "at",    2, fin,},
        { "sting",    5, "st",    2, fin,},	/* testing */
        { "eting",    5, "et",    2, fin,},	/* meeting */
        { "hting",    5, "ht",    2, fin,},   /* weighting */
        { "ting",     4, "te",    2, fin,},
        { "sting",    5, "st",    2, fin,},
        { "rming",    5, "rm",    2, fin,},	/* alarming */
        { "mming",    5, "m",     1, fin,},	/* programming */
        { "ming",     4, "me",    2, fin,},
        { "ering",    5, "er",    2, fin,},	/* offering */
        { "loring",   6, "lore",  4, fin,},	/* exploring */
        { "oring",    5, "or",    2, fin,},	/* monitoring mirroring */
        { "aring",    5, "ar",    2, fin,},   /* bearing */
        { "uing",     4, "ue",    2, fin,},   /* continuing */
        { "ring",     4, "re",    2, fin,},
        { "rning",    5, "rn",    2, fin,},
        { "nning",    5, "n",     1, fin,},
        { "oning",    5, "on",    2, fin,},
        { "gning",    5, "gn",    2, fin,},	/* designing */
        { "fining",   6, "ine",   3, fin,},	/* defining */
        { "ining",    5, "in",    2, fin,},	/* training */
        { "ning",     4, "ne",    2, fin,},
        { "cing",     4, "ce",    2, fin,},
        { "ving",     4, "ve",    2, fin,},
        { "ssing",    5, "ss",    2, fin,},	/* processing */
        { "using",    5, "use",   3, fin,},	/* accusing */
        { "asing",    5, "as",    2, fin,},	/* aliasing */
        { "sing",     4, "se",    2, fin,},	/* licensing */
        { "gging",    5, "g",     1, fin,},	/* debugging */
        { "ging",     4, "ge",    2, fin,},	/* charging */
        { "bing",     4, "be",    2, fin,},	/* describing */
        { "rding",    5, "rding", 5, fin,},	/* according */
        { "nding",    5, "nd",    2, fin,},	/* corresponding defending */
        { "dding",    5, "d",     1, fin,},	/* embedding */
        { "eding",    5, "ed",    2, fin,},	/* speeding */
        { "ding",     4, "de",    2, fin,},	/* including */
        { "aying",    5, "ay",    2, fin,},	/* decaying */
        { "nying",    5, "ny",    2, fin,},	/* accompanying */
        { "lying",    5, "y",     1, fin,},	/* applying */
        { "ying",     4, "y",     1, fin,},	/* underlying copying */
        { "ing",      3, "",      0, fin,},
        { "",         0, "",      0, fin},
    },

n_endings[] = {

        { "aturation", 9, "aturate", 7, fin,},
        { "eration",   7, "eration", 7, fin,},	/* operation */
        { "tration",   7, "ter",     3, fin,},	/* administration */
        { "oration",   7, "r",       1, fin,},      /* corporation */
        { "ration",    6, "re",      2, fin,},
        { "tition",    6, "te",      2, fin,},	/* competition */
        { "ection",    6, "ect",     3, fin,},	/* connection */
        { "version",   7, "version", 7, fin,},	/* version */
        { "ersion",    6, "ert",     3, fin,},	/* conversion */
        { "ssion",     5, "ss",      2, fin,},	/* compression */
        { "rmation",   7, "rmation", 7, fin,},	/* information */
        { "mation",    6, "mate",    4, fin,},	/* animation */
        { "otation",   7, "otate",   5, fin,},	/* annotation */
        { "ication",   7, "ication", 7, fin,},	/* application */
        { "cation",    6, "cate",    4, fin,},	/* communication */
        { "iction",    6, "iction",  6, fin,},	/* jurisdiction */
        { "nction",    6, "nction",  6, fin,},	/* function */
        { "uction",    6, "uce",     3, fin,},	/* introduction */
        { "ction",     5, "ct",      2, fin,},	/* abstraction */
        { "ilation",   7, "ile",     3, fin,},	/* compilation */
        { "lation",    6, "late",    4, fin,},	/* demodulation */
        { "tation",    6, "t",       1, fin,},
        { "nician",    6, "nical",   5, fin,},	/* technician */
        { "ican",      4, "ica",     3, fin,},	/* american */
        { "dation",    6, "date",    4, fin,},	/* accomodation */
        { "",          0, "",        0, fin},
    },

e_endings[] = {

        { "rable",   5, "are",     3, fin,},	/* comparable */
        { "eable",   5, "e",       1, fin,},	/* aggreeable */
        { "lable",   5, "le",      2, fin,},	/* scalable */
        { "ortable", 7, "ortable", 2, fin,},    /* portable */
        { "table",   5, "te",      2, fin,},     /* debatable */
        { "zable",   5, "ze",      2, fin,},     /* customizable */
        { "able",    4, "",        0, fin,},
        { "tible",   5, "tible",   5, fin,},
        { "ible",    4, "",        0, fin,},
        { "titive",  6, "te",      2, fin,},	/* competitive */
        { "ective",  6, "ect",     3, fin,},	/* connective */
        { "native",  6, "nate",    4, fin,},	/* alternative */
        { "lyze",    4, "lysis",   5, fin,},	/* analyze */
        { "",        0, "",        0, fin},
    },

l_endings[] = {

        { "ational", 7, "ational", 7, fin,},	/* international */
        { "tional",  6, "tion",    4, fin,},	/* additional */
        { "tial",    4, "tial",    4, fin,},
        { "ial",     3, "ial",     3, fin,},
        { "eral",    4, "eral",    4, fin,},	/* general */
        { "ral",     3, "re",      2, fin,},
        { "ual",     3, "ual",     3, fin,},
        { "mal",     3, "mal",     3, fin,},
        { "onal",    4, "on",      2, fin,},	/* traditional */
        { "nal",     3, "nal",     3, fin,},	/* journal */
        { "hical",   5, "hic",     3, fin,},	/* graphical */
        { "cal",     3, "cal",     3, fin,},	/* technical */
        { "eal",     3, "eal",     3, fin,},	/* appeal */
        { "bal",     3, "bal",     3, fin,},	/* global */
        { "sal",     3, "sal",     3, fin,},	/* universal */
        { "val",     3, "ve",      2, fin,},      /* retrieval */
        { "ntal",    4, "nt",      2, fin,},      /* accidental */
        { "tal",     3, "tal",     3, fin,},      /* digital */
        { "al",      2, "",        0, fin,},
        { "",        0, "",        0, fin},
    },

c_endings[] = {

        { "istic", 5, "",     0, fin,},
        { "ific",  4, "",     0, fin,},
        { "thmic", 5, "thm",  3, fin,},	/* algorithmic */
        { "matic", 5, "mate", 4, fin,},	/* automatic */
        { "",      0, "",     0, fin},
    },

y_endings[] = {

        { "rably",    5, "re",     2, fin,},	/* comparably */
        { "ably",     4, "",       0, fin,},
        { "ibly",     4, "",       0, fin,},
        { "ily",      3, "",       0, fin,},
        { "tically",  7, "te",     2, fin,},	/* automatically */
        { "fically",  7, "fic",    3, fin,},	/* specifically */
        { "ically",   6, "ical",   4, fin,},	/* techincally */
        { "ically",   6, "ic",     2, fin,},  /* drastically */
        { "cally",    5, "c",      1, fin,},
        { "titively", 6, "te",     2, fin,},	/* competitively */
        { "bly",      3, "bly",    3, fin,},	/* assembly */
        { "ly",       2, "",       0, fin,},
        { "tary",     4, "tary",   4, fin,},
        { "sary",     4, "sary",   4, fin,},	/* necessary */
        { "rary",     4, "rary",   4, fin,},	/* library */
        { "ary",      3, "",       0, fin,},
        { "ability",  7, "",       0, fin,},
        { "tibility", 8, "tible",  5, fin,},
        { "ibility",  7, "",       0, fin,},
        { "tivity",   6, "t",      1, fin,},	/* connectivity */
        { "vity",     4, "ve",     2, fin,},
        { "sity",     4, "sity",   4, fin,},
        { "arity",    5, "ar",     2, fin,},  /* familiarity */
        { "rity",     4, "re",     2, fin,},
        { "cility",   6, "cility", 6, fin,},
        { "ality",    5, "",       0, fin,},
        { "nity",     4, "nity",   4, fin,},	/* community */
        { "city",     4, "city",   4, fin,},	/* capacity */
        { "lity",     4, "lity",   4, fin,},  /* utility */
        { "uity",     4, "uity",   4, fin,},  /* annuity */
        { "ity",      3, "",       0, fin,},
        { "ify",      3, "",       0, fin,},
        { "uitry",    5, "uit",    3, fin,},	/* circuitry */
        { "",         0, "",       0, fin},
    },

v_endings[] = {

        { "iv",  2, "",     0, fin,},
        { "olv", 3, "olut", 4, fin,},
        { "",    0, "",     0, fin},
    },

t_endings[] = {

        { "eement", 6, "ee",    2, fin,},	/* agreement */
        { "rment",  5, "rment", 5, fin,},	/* deferment */
        { "ement",  5, "e",     1, fin,},	/* announcement */
        { "at",     2, "",      0, fin,},
        { "antt",   4, "antt",  4, -1,},
        { "lyst",   4, "lysis", 5, fin,},	/* analyst */
        { "",       0, "",      0, fin},
    },

r_endings[] = {

        { "vector",   6, "vector", 6, fin,},	/* vector */
        { "ector",    5, "ect",    3, fin,},	/* connector */
        { "titor",    5, "te",     2, fin,},	/* competitor */
        { "rator",    5, "rate",   4, fin,},	/* accelerator concentrator */
        { "mator",    5, "mate",   4, fin,},	/* animator */
        { "super",    5, "super",  5, fin,},	/* super */
        { "supplier", 8, "supply", 6, fin,},	/* supplier */
        { "lator",    5, "late",   4, fin,},	/* demodulator */
        { "ifier",    5, "ify",    3, fin,},	/* amplifier */
        { "lyser",    5, "lyze",   4, fin,},	/* analyser */
        { "lyzer",    5, "lyze",   4, fin,},	/* analyzer */
        { "der",      3, "d",      1, fin,},	/* loader */
        { "erter",    5, "ert",    3, fin,},	/* converter */
        { "piler",    5, "pile",   4, fin,},	/* compiler */
        { "zer",      3, "ze",     2, fin,},	/* compiler */
        { "nner",     4, "n",      1, fin,},
        { "",         0, "",       0, fin},
    };

/*===========================================================================*
 *                                   stem                                    *
 *===========================================================================*/

char * Stem (struct MSV * svPtr, char *ep, char *word) {
    wstem(word,strlen(word));
    return word;
    }

int wstem(char *word, int wl) {


    /*#+*********************************************************************
     *#+	if the ending of word[] is in endings.ending, it is removed and any
     *#+	replacement string is tacked on the end; search and replacement
     *#+	is controlled by endings.next.
     *#+**********************************************************************/

    int i;

    /*#+ check against possible endings */

    i = wl - 1;

    switch (word[i]) {
        case 'd':
            return escan(word, wl, d_endings);

        case 's':
            return escan(word, wl, s_endings);

        case 'g':
            return escan(word, wl, g_endings);

        case 'n':
            return escan(word, wl, n_endings);

        case 'e':
            return escan(word, wl, e_endings);

        case 'l':
            return escan(word, wl, l_endings);

        case 'y':
            return escan(word, wl, y_endings);

        case 'v':
            return escan(word, wl, v_endings);

        case 't':
            return escan(word, wl, t_endings);

        case 'r':
            return escan(word, wl, r_endings);

        default:
            return wl;
        }
    }

/*===========================================================================*
 *                                   escan                                   *
 *===========================================================================*/
int escan(char word[], int wl, const struct ends endings[]) {

    int i = 0;

    while (endings[i].ending[0]) {

        if ( wl - endings[i].offset > 3 &&
                strcmp(&word[wl - endings[i].offset], endings[i].ending) == 0) {
            strmove((unsigned char*) &word[wl - endings[i].offset],
                    (unsigned char*) endings[i].replace);
            wl += endings[i].replen - endings[i].offset;

            if (endings[i].next) break;

            i = 0;
            }
        else i++;
        }

    return (wl);

    }

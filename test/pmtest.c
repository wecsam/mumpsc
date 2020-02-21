/*===========================================================================
 *   Mumps Compiler Tests
 *   Coverage tests for Mumps pattern matcher
 *   Copyright (c) 2005 by Matthew Lockner
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

/* pmtest.c
 *
 * This file is intended to link up to the source tree's copy of pm.c, and
 * run a series of tests which will approach 100% statement coverage when
 * verified by the gcov tool.  Mostly what is missed are the pathological
 * error cases. Another weakness is the dummy hook functions provided so
 * as not, for instance, to terminate upon a syntax error.  Opting not to
 * terminate where the matcher normally would is moderately contrived.
 *
 * Author: M. Lockner
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/mumpsc/pm.h"

#define MATCH 1
#define NOMATCH 0

char* sym_ (int symflg, unsigned char* a, unsigned char* b, void* unused) {
    printf ("sym_: Operation %d with key %s and value %s\n", symflg, a, b);
}

void sigint (int code) {
    /* no action */
}

void pm_test (const char* s, const char* p, int expect) {
    int result = pm (s, p, NULL);
    printf ("... Matching string '%s' against pattern '%s'\n", s, p);
    if (result == expect) {
        printf ("+++ Success, %d == %d\n", result, expect);
    }
    else {
        printf ("--- Failed, %d != %d\n", result, expect);
    }
}

void perlmatch_test (const char* s, const char* p, int expect) {
    char* result = perlmatch (NULL, s, p, NULL);
    printf ("... Matching string '%s' against pattern '%s'\n", s, p);
    if (atoi (result) == expect) {
        printf ("+++ Success, %d == %d\n", atoi (result), expect);
    }
    else {
        printf ("--- Failed, %d != %d\n", atoi (result), expect);
    }
}

void perlcpp_test (const char* s, const char* p, int expect) {
    int result = perlcpp (NULL, s, p, NULL);
    printf ("... Matching string '%s' against pattern '%s'\n", s, p);
    if (result == expect) {
        printf ("+++ Success, %d == %d\n", result, expect);
    }
    else {
        printf ("--- Failed, %d != %d\n", result, expect);
    }
}

int main() {
    pm_test ("Hello World", ".A", NOMATCH);
    pm_test ("HelloWorld", ".A", MATCH);
    pm_test ("1234", "2.5N", MATCH);
    pm_test ("1234", ".3N", NOMATCH);
    pm_test ("1234", "1(2.5N,.A)", MATCH);
    pm_test ("Hello World", "1\"Hello World\"", MATCH);
    pm_test ("Hello World.", "1\"Hello World.\"", MATCH);
    pm_test ("abcd", "2\"Hello World\"", NOMATCH);
    pm_test ("Hello WorldHello World", "2\"Hello World\"", MATCH);
    pm_test ("\"Hello World\"", "1\"\xd2Hello World\xd2\"", MATCH);
    
    perlmatch_test ("abcd", "\\w+", MATCH);
    perlcpp_test ("12:34:56", "(..):(..):(..)", MATCH);
    
    /* Syntax error tests */
    pm_test ("Hello World", "1(2.5N,.A", NOMATCH);
    pm_test ("Hello World", "BCD", NOMATCH);
    pm_test ("Hello World", "1)", NOMATCH);

    return EXIT_SUCCESS;
}

/*===========================================================================
 *   Mumps Compiler Run-Time Support Functions
 *   Fixed-length-buffer string handling routines
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

/* bstring.c
 *
 * The "better string" library - implements a library for strings
 * represented as a struct of length and array of char.  It's slower,
 * but safer - and malloc()-free.
 *
 * Author: M. Lockner
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mumpsc/bstring.h>

static int checked_strlen(const char[]);
void sigint(int);

/*===========================================================================*
 *                                new_bstring                                *
 *===========================================================================*/
struct bstring new_bstring(const char initial[])
{
    struct bstring result;

    result.length = checked_strlen(initial);
    strncpy(result.string, initial, result.length);

    return result;
}

/*===========================================================================*
 *                                  bstrcat                                  *
 *===========================================================================*/
struct bstring bstrcat(const struct bstring left,
                       const struct bstring right)
{
    int catlength = left.length + right.length;

    if (catlength > STR_MAX) {
        fprintf(stderr, "String too long - aborting.\n");
        sigint(100);
    }
    else {
        struct bstring result;

        result.length = catlength;
        strncpy(result.string, left.string, left.length);
        result.string[left.length] = '\0';
        strncat(result.string, right.string, right.length);

        return result;
    }

    /* Dummy return - unreachable */
    return new_bstring ("");
}

/*===========================================================================*
 *                                  bcatchr                                  *
 *===========================================================================*/
struct bstring bcatchr(struct bstring *str, const char c)
{
    str->length++;
    if (str->length > STR_MAX) {
        fprintf(stderr, "String too long, aborting.\n");
        sigint(100);
    }
    str->string[str->length - 1] = c;
    str->string[str->length] = '\0';

    return *str;
}

/*===========================================================================*
 *                               make_cstring                                *
 *===========================================================================*/
void make_cstring(char *dest, const struct bstring src)
{
    strncpy(dest, src.string, src.length);
    dest[src.length] = '\0';
}

/*===========================================================================*
 *                              checked_strlen                               *
 *===========================================================================*/
int checked_strlen(const char cstring[])
{
    int i;

    for (i = 0; i <= STR_MAX; i++) {
        if (cstring[i] == '\0') {
            return i;
        }
    }
    fprintf(stderr, "String too long - aborting.\n");
    sigint(100);

    /* Dummy return - unreachable */
    return 0;
}

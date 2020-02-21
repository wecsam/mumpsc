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

/* bstring.h
 *
 * The "better string" library - implements a library for strings
 * represented as a struct of length and array of char.  It's slower,
 * but safer - and malloc()-free.
 *
 * Author: M. Lockner
 */

#include <mumpsc/sysparms.h>

struct bstring {
    int length;
    char string[STR_MAX];
};

struct bstring new_bstring(const char[]);
struct bstring bstrcat(const struct bstring, const struct bstring);
struct bstring bcatchr(struct bstring *, const char);
void make_cstring(char *, const struct bstring);

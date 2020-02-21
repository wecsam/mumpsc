/*#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *#+    Mumps Compiler Run-Time Support Functions
 *#+    Copyright (c) A.D. 2001, 2002, 2017 by Kevin C. O'Kane
 *#+    okane@cs.uni.edu
 *#+
 *#+    This library is free software; you can redistribute it and/or
 *#+    modify it under the terms of the GNU Lesser General Public
 *#+    License as published by the Free Software Foundation; either
 *#+    version 2.1 of the License, or (at your option) any later version.
 *#+
 *#+    This library is distributed in the hope that it will be useful,
 *#+    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *#+    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *#+    Lesser General Public License for more details.
 *#+
 *#+   You should have received a copy of the GNU Lesser General Public
 *#+    License along with this library; if not, write to the Free Software
 *#+    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *#+
 *#+    http://www.cs.uni.edu/~okane
 *#+
 *#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#ifndef STRMANIP_H
#define STRMANIP_H

/* strmanip.h - Mumps runtime library
 *
 * These routines provide a few slight extensions to the standard C string
 * handling library, used by many other parts of the runtime and
 * in the Mumps to C translations.
 */

/* Extract a substring of length len from in starting at start. */
void substr(unsigned char *, unsigned char *, int start, int len);

int xindex(const unsigned char *, const unsigned char *, short);

#ifdef _MSC_VER
char *rindex(char *, int);
#endif

/* Join in with a '\x01', putting the result in out. */
void strcatx(unsigned char *, unsigned char *);

/* Pad strin on the left with blanks. */
void lpad(unsigned char *, unsigned char *, short);
#endif

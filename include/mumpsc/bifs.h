/*#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *#+    Mumps Compiler Run-Time Support Functions
 *#+    Copyright (c) A.D. 2001, 2002, 2006 by Kevin C. O'Kane
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

/* bifs.h - Mumps runtime library
 *
 * Mumps Built-In FunctionS
 * ========================
 * The majority of Mumps builtins are translated to calls to the
 * following functions, whose names look like the function implemented.
 */

#ifndef BIFS_H
#define BIFS_H

#include <mumpsc/stateVector.h>

void _ascii(unsigned char *, unsigned char *,
             unsigned char *);
void _horolog(unsigned char *);
void _justify(unsigned char *, unsigned char *, unsigned char *, unsigned char *);
void _length(unsigned char *, unsigned char *, unsigned char *);
void _piece(unsigned char *, unsigned char *, unsigned char *,
             unsigned char *, unsigned char *, int ,
             unsigned char *, struct MSV * );
void _random(unsigned char *, unsigned char *);

#ifndef _INTERP_
void zfcn(unsigned char *, unsigned char *, struct MSV *);
#endif

void ServiceInterface(unsigned char *, unsigned char *, unsigned char *, unsigned char *, 
                      unsigned char *, char, struct MSV *);
// int BuildGlobal(int,int,unsigned char *,unsigned char *, struct MSV *);
// int BuildLocal(int,int,unsigned char *,unsigned char *, struct MSV *);
#endif

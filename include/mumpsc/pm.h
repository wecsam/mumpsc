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

#ifndef PM_H
#define PM_H
#define PM_DEBUG 0
#include <mumpsc/stateVector.h>

#ifndef _INTERP_
int pm (const unsigned char *, const unsigned char *, struct MSV *);
#endif

int perl_pm(const char *, const char *, const int, struct MSV *);

const char * perlmatch (struct MSV *, char *, char *, char *);

#endif

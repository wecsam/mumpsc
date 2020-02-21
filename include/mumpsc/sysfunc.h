/*#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *#+    Mumps Compiler Run-Time Support Functions
 *#+    Copyright (c) A.D. 2001, 2002, 2003, 2017 by Kevin C. O'Kane
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

/* sysfunc.h - Mumps Runtime Library
 *
 * These functions are the most operating-system specific.  Some others
 * aren't very OS-specific, but are somehow related to those that are.
 */
 
#ifndef SYSFUNC_H 
#define SYSFUNC_H

#include <stdio.h>
#include <signal.h>
#include <mumpsc/stateVector.h>

int getstr1(FILE * opnfile, unsigned char **area);
int TimeOut_getstr1(int io, unsigned char area[], char *timeout, int dirflg);

#ifndef _INTERP_

int DirectRead(int io, unsigned char *to);
void ErrorMessage(const char *,long);
void GlobalNext(unsigned char *, unsigned char *, struct MSV *);
void LocalNext(unsigned char *, unsigned char *, struct MSV *);
void LocalOrder(unsigned char *, unsigned char *, unsigned char *, struct MSV *);

#else

void LocalNext(unsigned char *, unsigned char *, struct MSV *);
void LocalOrder(unsigned char *, unsigned char *, unsigned char *, struct MSV *);

#endif

unsigned char * VariableNotFound(long LineNumber);
unsigned char * VariableNotFound1(long LineNumber, unsigned char *);

int Merge(unsigned char *, unsigned char *, struct MSV *);
void GlobalData(unsigned char *, unsigned char *, struct MSV *);
void GlobalName(unsigned char *, unsigned char , struct MSV *);
void LocalGet(unsigned char *, unsigned char *, unsigned char *, struct MSV *);
void GlobalGet(unsigned char *, unsigned char *, unsigned char *, struct MSV *);
void LocalQuery(unsigned char *, unsigned char *, struct MSV *);
void fullUnpad(unsigned char *, struct MSV *);

#endif

/*#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *#+    Mumps Compiler Run-Time Support Functions
 *#+    Copyright (c) A.D. 2001, 2002, 2003 by Kevin C. O'Kane
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

#ifndef CPPSYSFUNC_H 
#define CPPSYSFUNC_H

// extern "C" int getstr1(FILE * opnfile, unsigned char area[]);
extern "C" int TimeOut_getstr1(int io, unsigned char area[], char *timeout, int dirflg);
extern "C" int DirectRead(int io, unsigned char *to);
extern "C" unsigned char * VariableNotFound(long LineNumber);
extern "C" void ErrorMessage(const char *,long);
extern "C" void sigint(int i);
extern "C" int Merge(unsigned char *, unsigned char *, struct MSV *);
extern "C" void GlobalData(unsigned char *, unsigned char *, struct MSV *);
extern "C" void LocalData(unsigned char *, unsigned char *, struct MSV *);
extern "C" void GlobalOrder(unsigned char *, unsigned char *, unsigned char *, struct MSV *);
extern "C" void LocalOrder(unsigned char *, unsigned char *, unsigned char *, struct MSV *);
extern "C" void LocalNext(unsigned char *, unsigned char *, struct MSV *);
extern "C" void GlobalNext(unsigned char *, unsigned char *, struct MSV *);
extern "C" void LocalName(unsigned char *, unsigned char *, unsigned char *, struct MSV *);
extern "C" void GlobalName(unsigned char *, unsigned char *, unsigned char *, struct MSV *);
extern "C" void LocalName(unsigned char *, unsigned char *, unsigned char *, struct MSV *);
extern "C" void LocalGet(unsigned char *, unsigned char *, unsigned char *, struct MSV *);
extern "C" void GlobalGet(unsigned char *, unsigned char *, unsigned char *, struct MSV *);
extern "C" void GlobalQuery(unsigned char *, unsigned char *, char, struct MSV *);
extern "C" void LocalQuery(unsigned char *, unsigned char *, struct MSV *);
extern "C" void fullUnpad(unsigned char *, struct MSV *);
#endif

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

/* sym.h - Mumps Runtime Library
 *
 * Mumps symbol table management.  Variables not handled by global.h
 * and friends should be handled by these routines.
 */

#ifndef SYM_H
#define SYM_H

#include <iostream>
#include <cctype>
#include <string>

using namespace std;

char * strsep(char **p, char* delim);

void sigint (int);

struct stab {
    char *name;
    struct stab *next;
    string * data;  // these must be allocated with new rather that malloc()
    string * OrigName;  // these must be allocated with new rather that malloc()
    int size;
    int copy;
    int exec;
};

// char *sym_(int symflg, unsigned char *a, unsigned char *b, struct MSV * svPtr);

/* Not normally defined here, but must be for a lib. */
/* This line comes from line 496 of mumps.c.         */


void GlobalName(unsigned char *, unsigned char , struct MSV *);
void fullUnpad(unsigned char *, struct MSV *);

#ifdef _INTERP_
// void keyfix(unsigned char *, struct MSV *);
#else
// void keyfix(unsigned char *, struct MSV *);
#endif

char *sym_(int symflg, unsigned char *a, unsigned char *b, struct MSV * svPtr);
int _SymFree(int i, struct MSV * svPtr);
void SysDump(long pid, struct MSV * svPtr);
// void Mltoa(long, unsigned char *);
#include <mumpsc/arith.h>
void ErrorMessage(const char *, long);

int BuildGlobal(int,int,unsigned char *,unsigned char *, struct MSV *);
//int BuildLocal(int,int,unsigned char *,unsigned char *, struct MSV *);

void Qsub (unsigned char *, unsigned char *, unsigned char *, struct MSV *);
void GlobalQuery(unsigned char *, unsigned char *, char, struct MSV *);
void ServiceInterface(unsigned char *, unsigned char *, unsigned char *, unsigned char *, 
                      unsigned char *, char, struct MSV *);
void Qlength(unsigned char *, unsigned char *, struct MSV *);
void LocalName(unsigned char *, unsigned char *, unsigned char *, struct MSV *);
int xindex(const unsigned char *, const unsigned char *, short );
void substr(unsigned char *, unsigned char *, int start, int len);
void lpad(unsigned char *, unsigned char *, short l);
void _fnumber(unsigned char *, unsigned char *, unsigned char *, unsigned char *, MSV *);

#endif

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

#ifndef INTERP_H
#define INTERP_H

#include <mumpsc/defines.h>

/* interp.h - Mumps Runtime Library
 *
 * Mumps interpretation routines - can be used for indirection operations
 * in the compiled code.
 */

#define TSTACK 10

#define BREAK 'b'
#define CMMNT ';'
#define DATAKILL 'k'
#define DO 'd'
#define ELSE 'e'
#define FCN '$'
#define FILECLOSE 'c'
#define FILELOCK 'l'
#define FILEOPEN 'o'
#define FOR 'f'
#define GOTO 'g'
#define HALT 'h'
#define HTML '<'
#define IF 'i'
#define JOB 'j'
#define QUIT 'q'
#define READ 'r'
#define SET 's'
#define MERGE 'm'
#define TAB '\t'
#define USE 'u'
#define WRITE 'w'
#define XECUTE 'x'
#define ZCMDS 'z'
#define NEW 'n'

#define QUOTE '\''
#define POPEN 0
#define DIVIDE 1
#define MULTIPLY 2
#define MINUS 3
#define PLUS 4
#define OPERAND 5
#define OPENC 6
#define CONCAT 7
#define EQUALS 8
#define GREATER 9
#define PEMPTY 10
#define LESSTHAN 11
#define NOT 12
#define INTDIVIDE 13
#define MODULO 14
#define CONTAINS 15
#define FOLLOWS 16
#define PATTERN 17
#define NOTEQ 18
#define NOT_NOT 18
#define NOTGREATER 19
#define NOTLESS 20
#define NOTCONTAINS 21
#define NOTFOLLOWS 22
#define NOTPATTERN 23
#define AND 24
#define OR 25
#define NOTAND 26
#define NOTOR 27
#define INDIRECT 28
#define EXPONEN 29
#define PREDICATEVAR '~'

int Interpret(char *parm1, struct MSV *);
int parse_(struct MSV *);
void prnterr(int i,struct MSV * svPtr,int);
int BuildGlobal(int,int,unsigned char *, unsigned char *, struct MSV *);
int BuildLocal(int,int,unsigned char *, unsigned char *, struct MSV *);

#include <mumpsc/symbasic.h>
#endif

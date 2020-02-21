//#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//#+   
//#+     Mumps Compiler 
//#+     Copyright (C) 2003 by Kevin C. O'Kane  
//#+
//#+     Kevin C. O'Kane
//#+     Department of Computer Science
//#+     University of Northern Iowa
//#+     Cedar Falls, IA 50613-0507 USA
//#+
//#+     anamfianna@earthlink.net
//#+     okane@cs.uni.edu
//#+     http://www.cs.uni.edu/~okane
//#+
//#+
//#+ This program is free software; you can redistribute it and/or modify
//#+ it under the terms of the GNU General Public License as published by
//#+ the Free Software Foundation; either version 2 of the License, or
//#+ (at your option) any later version.
//#+ 
//#+ This program is distributed in the hope that it will be useful,
//#+ but WITHOUT ANY WARRANTY; without even the implied warranty of
//#+ MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//#+ GNU General Public License for more details.
//#+ 
//#+ You should have received a copy of the GNU General Public License
//#+ along with this program; if not, write to the Free Software
//#+ Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//#+
//#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//#+
//#+    Some of this code was originally written in Fortran
//#+    which will explain the odd array and label usage,
//#+    especially arrays beginning at index 1.
//#+
//#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <stdio.h>

struct nmes {
    char        *name;
    struct nmes *next;
};

extern int gpad;
extern long xpx;
extern short Jflg;
extern short ierr1;
extern short ierr;
extern short int ctrlc;
extern short int tpx;
extern short iorg;
extern short pd1len;
extern short sdlim;
extern short setpiece;
extern short symlen;
extern short t0px;
extern short t2;
// extern struct nmes *nstart;
struct nmes *nstart;
extern unsigned char bd[];
extern unsigned char pd1[];
extern unsigned char setname[];
extern unsigned char symflg;
extern unsigned char v1d[];
extern unsigned char xd[];

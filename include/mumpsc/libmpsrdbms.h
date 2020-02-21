//#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//#+   
//#+     Mumps Compiler 
//#+     Copyright (C) A.D. 2000, 2001, 2002, 2003 by Kevin C. O'Kane  
//#+
//#+     Kevin C. O'Kane
//#+     Department of Computer Science
//#+     University of Northern Iowa
//#+     Cedar Falls, IA 50613-0507 USA
//#+
//#+     okane@cs.uni.edu
//#+     anamfianna@earthlink.net
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

#ifndef RDBMSLIB_H
#define RDBMSLIB_H
#define SELECT(arr,out,exp) Select(svPtr,"",arr,out,exp)
#define PRINT(arr,exp) Print(svPtr,"",arr,exp)
#define UNION(arr1,arr2,out) Union(svPtr,"",arr1,arr2,out)
#define PROJECT(arr,out,cols) Project(svPtr,"",arr,out,cols)
#define SUBTRACT(arr,sub,out) Subtract(svPtr,"",arr,sub,out)
#define INTERSECT(arr,sub,out) Intersect(svPtr,"",arr,sub,out)
#define JOIN(arr1,arr2,out,exp) Join(svPtr,"",arr1,arr2,out,exp)

char * Select(struct MSV *, char *, const char *, const char *, const char *);
char * Print(struct MSV *, char *, const char *, const char *);
char * Union(struct MSV *, char *, const char*, const char *, const char *);
char * Project(struct MSV *, char *, const char*, const char *, const char *);
char * Subtract(struct MSV *, char *, const char*, const char *, const char *);
char * Intersect(struct MSV *, char *,const char*,const char *,const char *);
char * Join(struct MSV *, char *, const char *, const char*, const char *, const char *);
char * TablePrint(struct MSV *, char *, const char *, const char*, const char *);
#endif

/*#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *#+	Mumps Compiler Run-Time Support Functions
 *#+	Copyright (c) 2001, 2002, 2003, 2004, 2012 by Kevin C. O'Kane
 *#+	kc.okane@gmail.com
 *#+
 *#+	This library is free software; you can redistribute it and/or
 *#+	modify it under the terms of the GNU Lesser General Public
 *#+	License as published by the Free Software Foundation; either
 *#+	version 2.1 of the License, or (at your option) any later version.
 *#+
 *#+	This library is distributed in the hope that it will be useful,
 *#+	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *#+	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *#+	Lesser General Public License for more details.
 *#+
 *#+   You should have received a copy of the GNU Lesser General Public
 *#+	License along with this library; if not, write to the Free Software
 *#+	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *#+
 *#+	http://www.cs.uni.edu/~okane
 *#+	http:omahadave.com
 *#+
 *#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *#+
 *#+	Some of this code was originally written in Fortran
 *#+	which will explain the odd array and label usage,
 *#+	especially arrays beginning at index 1.
 *#+
 *#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *#+
 *#+	This is the native btree global array handler from the
 *#+	Mumps Compiler.
 *#+
 *#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


#include <mumpsc/libmpscpp.h>

int main() {

      long i,j;
      unsigned char key[1024],data[1024];

      printf("store sequentially ascending keys");
      for (i=0; i<NBR_ITERATIONS; i++) {
	    sprintf( (char *) key,"key %ld",i);
	    sprintf( (char *) data,"%ld%c",i,0);
	    if (!BTREE(STORE,key,data)) {
		  printf("error\n");
		  return 1;
		  }
	    if (i%60000L==0)  { printf("\n %ld ",i); fflush(stdout); }
	    if (i%1000==0) { putchar('.'); fflush(stdout); }
	    }
      printf("\nretrieve");
      for (i=0; i<NBR_ITERATIONS; i++) {
	    sprintf( (char *) key,"key %ld",i);
	    if (!BTREE(RETRIEVE,key,data)) {
		  printf("error 1\n");
		  return 1;
		  }
	    sscanf( (char *) data,"%ld",&j);
	    if (j!=i) {
		  printf("error 2\n");
		  printf("%d != %d\n",i,j);
		  return 1;
		  }
	    if (i%60000L==0)  { printf("\n %ld ",i); fflush(stdout); }
	    if (i%1000==0) { putchar('.'); fflush(stdout); }
	    }
      printf("\nlooks good!\n");
      strcpy( (char *) key,"");
      strcpy( (char *) data,"");
      BTREE(CLOSE,key,data);
      return 0;
      }

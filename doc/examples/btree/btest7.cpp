/*#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *#+    Mumps Compiler Run-Time Support Functions
 *#+    Copyright (c) 2001, 2002, 2003, 2004, 2012 by Kevin C. O'Kane
 *#+    kc.okane@Gmail.com
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
 *#+    http://omahadave.com
 *#+
 *#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *#+
 *#+    Some of this code was originally written in Fortran
 *#+    which will explain the odd array and label usage,
 *#+    especially arrays beginning at index 1.
 *#+
 *#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *#+
 *#+    This is the native btree global array handler from the
 *#+    Mumps Compiler.
 *#+
 *#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <mumpsc/libmpscpp.h>

int main() {

      long i,j;
      unsigned char key[1024],data[1024];

	printf("store %ld keys and XNEXT thru them\n",NBR_ITERATIONS);
      printf("begin store");
      for (i=0; i<NBR_ITERATIONS; i++) {
            if (i%60000L==0)  { putchar('\n'); fflush(stdout); }
            if (i%1000==0) { putchar('.'); fflush(stdout); }
            sprintf( (char *) key,"%ld",i);
            sprintf( (char *) data,"%ld",i);
            if (!BTREE(STORE,key,data)) {
                  printf("error\n");
                  return 1;
                  }
            }

      printf("\nbegin retrieve\n");
      strcpy( (char *) key," ");
      j=0;
      while(1) {
            i=BTREE(XNEXT,key,data);
            if (strlen( (char *) data)==0) break;
            j++;
		if (j%60000L==0)  { putchar('\n'); fflush(stdout); }
            if (j%1000==0) { putchar('.'); fflush(stdout); }
            }
      *key=0; *data=0;
      BTREE(CLOSE,key,data);
      if (j==NBR_ITERATIONS) { printf("\nlooks good!  \n"); return 0; }
      else printf("Interation mismatch: %d %d\n",NBR_ITERATIONS,j);
      return 1;
      }

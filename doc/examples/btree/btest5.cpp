/*#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *#+    Mumps Compiler Run-Time Support Functions
 *#+    Copyright (c) 2001, 2002, 2003, 2004, 2012 by Kevin C. O'Kane
 *#+    kc.okane@gmail.com
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

      srand(SEED);

      printf("Random key tests. %d iterations.\n",NBR_ITERATIONS);
      printf("Speed will vary depending on memory and I/O traffic.\n");
      printf("Each dot represents 1,000 stores or retrieves.\n");
	  printf("nbr keys retrieved may not match stores due to repeats\n");
      printf("begin store");
      for (i=0; i<NBR_ITERATIONS; i++) {
            if (i%60000L==0)  { putchar('\n'); fflush(stdout); }
            if (i%1000==0) { putchar('.'); fflush(stdout); }
            j=rand();
            sprintf( (char *) key,"%ld",j);
            sprintf( (char *) data,"%ld",j);
            if (!BTREE(STORE,key,data)) {
                  printf("error\n");
                  return 1;
                  }
            }

      printf("\nbegin retrieve");
      strcpy( (char *) key,"9999999999999");
	  j=0;
      while(1) {
            i=BTREE(PREVIOUS,key,data);
            if (strlen( (char *) data)==0) break;
            strcpy( (char *) key, (char *) data);
            if (j%60000L==0)  { putchar('\n'); fflush(stdout); }
            if (j%1000==0) { putchar('.'); fflush(stdout); }
			j++;
            }
      printf("\nlooks good!\n");
      *key=0; *data=0;
      BTREE(CLOSE,key,data);
	  return 0;
      }

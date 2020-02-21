#ifndef COMPILER_H
#define COMPILER_H

/*#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *#+    Mumps Compiler Run-Time Support Functions
 *#+    Copyright (c) A.D. 2013 by Kevin C. O'Kane
 *#+    kc.okane@gmail.com
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
 *#+    http://omahadave.com
 *#+
 *#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

// compiler runtime service functions

void _Column (int *hor, int *ver, char * to, FILE * fp) {

	int i=atoi(to),j,k;
	if (i<0) return;

	if ( *hor > i ) {
		fprintf(fp,"\n");
		for (j=0; j<i; j++) fprintf(fp, " ");
		*hor = i;
		*ver = *ver +1;
		return;
		}

	for (j=*hor; j<i; j++) fprintf(fp," ");

	*hor = i;
	*ver = *ver +1;
	return;
	}
#endif

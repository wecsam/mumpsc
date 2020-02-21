//#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//#+    Mumps Compiler Run-Time Support Functions
//#+    Copyright (c) A.D. 2001, 2002 by Kevin C. O'Kane
//#+    kc.okane@gmail.com
//#+    http://threadsafebooks.com/
//#+
//#+    This library is free software; you can redistribute it and/or
//#+    modify it under the terms of the GNU Lesser General Public
//#+    License as published by the Free Software Foundation; either
//#+    version 2.1 of the License, or (at your option) any later version.
//#+
//#+    This library is distributed in the hope that it will be useful,
//#+    but WITHOUT ANY WARRANTY; without even the implied warranty of
//#+    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//#+    Lesser General Public License for more details.
//#+
//#+   You should have received a copy of the GNU Lesser General Public
//#+    License along with this library; if not, write to the Free Software
//#+    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//#+
//#+    http://www.cs.uni.edu/~okane
//#+
//#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/* strmanip.c - Mumps runtime library
 *
 * These routines provide a few slight extensions to the standard C string
 * handling library, used by many other parts of the runtime and
 * in the Mumps to C translations.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <mumpsc/fcns.h>

void sigint(int);

#ifdef MSVC
char *rindex(char *s, int c) {
    int i, j;

    i = strlen(s);
    for (j = i; j >= 0; j--) {
        if (c == s[j]) {
            return &s[j];
        }
    }
    return NULL;
}
#endif

/*===========================================================================*
 *                                  substr                                   *
 *===========================================================================*/
void substr(unsigned char in[], unsigned char out[], int start, int len)
{

    short i;

    if (len == 0) {
        out[0] = 0;
        return;
    }

    if (len < 0)
        len = 255;
    else if (len-start+1 > STR_MAX) {
	out= (unsigned char *) realloc(out,len-start<<1);
//      len = STR_MAX-1;
	}

    start--;
    len--;
    for (i = 0; i <= len; i++)
        out[i] = in[start++];
    out[len + 1] = 0;
    return;
}

/*===========================================================================*
 *                                  xindex                                   *
 *===========================================================================*/
int xindex(const unsigned char source[], const unsigned char ptrn[], short strt)
{

    short int flg = 0, i, j, k, l, istrt;

    for (i = 0; ptrn[i] != 0; i++);
    --i;
    for (j = 0; source[j] != 0; j++);
    --j;
    istrt = strt - 1;
    if (strt <= 1)
        istrt = 0;

    for (k = istrt; k <= j; k++) {

        for (l = 0; l <= i; l++) {
            if (ptrn[l] != source[k + l]) {
                flg = 1;
                break;
                }
            }

        if (flg) {
            flg = 0;
            continue;
            }

        return (k + 1);
    }
    return (0);
}

/*===========================================================================*
 *                                  strcatx                                  *
 *===========================================================================*/
void strcatx(unsigned char * out, unsigned char * in)
{
//    strcat((char *) out, (char *) in);
//    strcat((char *) out, "\x01");
	for (; *out!=0; out++);
	for (; *in!=0; in++) *(out++)=*in;
	*(out++)='\x01';
	*out='\0';
    return;
}

/*===========================================================================*
 *                                   lpad                                    *
 *===========================================================================*/
void lpad(unsigned char strin[], unsigned char strout[], short l)
{

    short int j, i, k;
    j = strlen((char *) strin) - 1;
    k = (l - j - 1);
    if (k <= 0)
        return;
    for (i = j; i >= 0; i--)
        strout[i + k] = strin[i];
    strout[j + k + 1] = 0;
    for (i = 0; i < k; i++)
        strout[i] = ' ';
    return;
}


/*#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *#+    Mumps Compiler Run-Time Support Functions
 *#+    Copyright (c) A.D. 2001, 2002 by Kevin C. O'Kane
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

/* stem.h - Mumps Runtime Library
 *
 * These functions provide support for word stemming, used as helper
 * functions for implementing $ZALTER and $ZNORMAL.  These may be
 * commonly used in text processing applications.
 */

struct ends {
    const char *ending;               /*ending string */
    int offset;                 /*length */
    const char *replace;              /*replacement */
    int replen;                 /*length */
    int next;                   /*goto */
};

/* Stem word, which has length wl; destructive modification of word. */
int stem(char *word, int wl);

/* Helper to stem(). */
int escan(char word[], int wl, const struct ends endings[]);

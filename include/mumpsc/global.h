/*====================================================================
 *   Mumps Compiler Global Array Handler - Berkeley DB Interface
 *   Copyright (c) 2002 by Matthew Lockner
 *   lockner@cns.uni.edu
 * 
 *   This library is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU Lesser General Public
 *   License as published by the Free Software Foundation; either
 *   version 2.1 of the License, or (at your option) any later version.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *   Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public
 *   License along with this library; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *            
 *=====================================================================
 *   This file contains the Mumps global array handling code.
 *   All references to global arrays inside Mumps source turn into calls
 *   to global(), where the requests are transliterated into requests
 *   upon the underlying Berkeley DB B-tree database on disk.
 *====================================================================*/

/* November 24, 2002 */
/* Modified May 12, 2003, kok */

/* cache sizes for BDB */
/* GIGS is number if giabytes to use (1,2,3,4) */
/* BYTES is actual number of bytes. */
/* values are added together to produce final number */
/* too large a cache size will cause seg faults */
/* PAGE_SIZE ranges from 512 to 65536 and sets the BDB page size */

#include <mumpsc/stateVector.h> /* kok May 11, 2003 */

#define CACHE_GIGS 0
#define CACHE_BYTES 1000000
#define PAGE_SIZE 1024

/* Legal request types to global(). */

#ifndef EMPTY
#define EMPTY 5
#endif

// #ifndef GCLOSE
// #define GCLOSE 4
// #endif

/*---------------------------------------------------------------------
 * global() - Request global array service.
 *
 * g: Specifies the operation requested.
 *    Valid operations are:
 *       EMPTY
 *       GCLOSE
 *       PCLOSE
 *       INIT
 *       KILL
 *       LOCK
 *       NEXT
 *       OPEN
 *       ORDERNEXT
 *       ORDERPREV
 *       PREVIOUS
 *       RETRIEVE
 *       STORE
 *       XNEXT
 *
 * key: Key sought or stored.
 * bd:  Value returned or stored.
 *
 * Returns: 1 on operation success, 0 on failure.
 */

int Mglobal (const int g, unsigned char key[], unsigned char bd[], /* kok */
      struct MSV *); /* kok may 11, 2003 */
            
            
/*---------------------------------------------------------------------
 * keyfix() - transform vxd to prepare it for a global array operation.
 *            
 * vxd: String containing the key to 'fix'. 
 */
#if !defined(_INTERP_)  /* kok */
// void keyfix (unsigned char *vxd, struct MSV * svPtr);
#else
// void keyfix (unsigned char *, struct MSV *);
#endif


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

/* fcns.h - Mumps Runtime Library */

/* Gives us a few constant defines, among others */
#include <mumpsc/sysparms.h>

/* Arithmetic operations on operands stored as strings. */
// #include <mumpsc/arith.h>

/* Fixed-length-buffer string handling routines */
#include <mumpsc/bstring.h>

/* String manipulation routines */
#include <mumpsc/strmanip.h>

/* Pattern matching routines */
#include <mumpsc/pm.h>

/* Mumps built-in function implementations */
#include <mumpsc/bifs.h>

/* Symbol table management */
// #include <mumpsc/symbasic.h>

/* Word stemming support */
#include <mumpsc/stem.h>

/* Run-time interpreter routines */
#include <mumpsc/interp.h>

/* Database interfacing */
// #include <mumpsc/rdbms-if.h>

/* Operating-system specific functionality */
#include <mumpsc/sysfunc.h>

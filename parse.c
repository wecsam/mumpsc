/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#+   
#+     Mumps Bioinformatics Software Library
#+     Copyright (C) 2003, 2004, 2008, 2015 by Kevin C. O'Kane  
#+
#+     Kevin C. O'Kane
#+     kc.okane@gmail.com
#+     okane@cs.uni.edu
#+     http://www.cs.uni.edu/~okane
#+     http://threadsafebooks.com/
#+
#+ This program is free software; you can redistribute it and/or modify
#+ it under the terms of the GNU General Public License as published by
#+ the Free Software Foundation; either version 2 of the License, or
#+ (at your option) any later version.
#+ 
#+ This program is distributed in the hope that it will be useful,
#+ but WITHOUT ANY WARRANTY; without even the implied warranty of
#+ MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#+ GNU General Public License for more details.
#+ 
#+ You should have received a copy of the GNU General Public License
#+ along with this program; if not, write to the Free Software
#+ Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#+
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//#+
//#+    Some of this code was originally written in Fortran
//#+    which will explain the odd array and label usage,
//#+    especially arrays beginning at index 1.
//#+
//#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Modified A.D. January 7, 2002

#include <mumpsc/memsize.h>

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#if UNIX==0
#include <conio.h>
#include <io.h>
#include <dos.h>
#include <errno.h>
#endif

#define SymStore 0
#define SymRetrieve 1
#define SymDeleteExplicit 2
#define SymNext 3
#define SymOrder 33
#define SymDeleteAll 4
#define SymDeleteAllExcept 5
#define SymData 6
#define SymName 10

#define RETRIEVE 0
#define STORE 1
#define NEXT 2
#define XNEXT 8
#define NEXTX 20
#define KILL1 30
#define PREVIOUS 9

#define JOB 0
#define SET 1
#define GOTO 2
#define WRITE 3
#define IF 4
#define ZCMDS 6
#define READ 7
#define QUIT 8
#define XECUTE 9
#define TAB 9
#define FOR 10
#define HALT 11
#define ELSE 12
#define ORDERNEXT 12
#define ORDERPREV 13
#define DO 13
#define KILL 14
#define CLOSE 15
#define USE 16
#define LOCK 17
#define COMMENT 18
#define BREAK 19
#define BADCMD 21
#define KILL2 20
#define FCN 20
#define LBL 21
#define QUOTE '\''
#define OPEN 0
#define DIVIDE 1
#define MULTIPLY 2
#define MINUS 3
#define PLUS 4
#define OPERAND 5
#define OPENC 6
#define CONCAT 7
#define EQUALS 8
#define GREATER 9
#define EMPTY 10
#define LESSTHAN 11
#define NOT 12
#define INTDIVIDE 13
#define MODULO 14
#define CONTAINS 15
#define FOLLOWS 16
#define PATTERN 17
#define NOTEQ 18
#define NOTGREATER 19
#define NOTLESS 20
#define NOTCONTAINS 21
#define NOTFOLLOWS 22
#define NOTPATTERN 23
#define AND 24
#define OR 25
#define NOTAND 26
#define NOTOR 27
#define INDIRECT 28
#define EXPONEN 29
#define PREDICATEVAR '~'
#define CodedOpen 206
#define CodedClose 207
#define CodedComma 208
#define CodedColon 209
#define GBLDEFERED 100
#define LCLDEFERED 101
#define NAME 102
#define GET 103
#define ORDER 104

#include <mumpsc/externs.h>

extern short MaxTmp; /* max temp strings used so far this function */
extern int iiitmp; /* nbr temp strings used so far this statement */
extern char ErrChar;

/*--------------*/

void ExpandQS(unsigned char * , int , unsigned char * );
void patrn (unsigned char *);
int cvar(char *);
void patrn1 (short *, short *);
int xindex (unsigned char *, unsigned char *, short);
void errmod_ (short msgnbr, unsigned char text[], FILE * opnfile[]);
void memcheck (int);
void add (char *a, char *b, char *c);
void sub (char *a, char *b, char *c);
void mult (char *a, char *b, char *c);
void divx (char *a, char *b, char *c);
int numcomp (char aa[], char bb[]);
void cannon (char a[]);
int MyFunc(unsigned char *, short);
int sym_ (int, unsigned char a[], unsigned char b[]);
short keyfix (unsigned char *);
void fixstr (unsigned char[]);
extern FILE *Out;
char * Extract2(char *);
char * Extract1(char *);
char * Extract2a(char *);
void ExpandOrder(unsigned char * v1d, int i, unsigned char * bp);
void ExpandData(unsigned char * v1d, int i, unsigned char * bp);
void ExpandQlength(unsigned char * v1d, int i, unsigned char * bp);
void ExpandNext(unsigned char * v1d, int i, unsigned char * bp);
void ExpandGet(unsigned char * v1d, int i, unsigned char * bp);
void ExpandName(unsigned char * v1d, int i, unsigned char * bp);
void ExpandText(unsigned char * v1d, int i, unsigned char * bp);
int Extract(unsigned char * v1d, unsigned char * bp);
void ExpandQsub(unsigned char * v1d, int i, unsigned char * bp);

unsigned char * SSS,*TTT;

#define CVARMAX 100

extern struct dcls {
      char name[32];
      int type;
      } cvars[CVARMAX];

extern int cvarx;

/*--------------*/

int ConCheck(char * b) {
      int i;
      if (b[0]!='\"') return 0;
      if (b[strlen(b)-1]!='\"') return 0;
      for (i=1; b[i]!='\"'; i++) if (!isdigit(b[i])) return 0;
//      strcpy(b,&b[1]);  STRCPY
	for (SSS=b; *SSS !=0; SSS++) *SSS = *(SSS+1);
      b[strlen(b)-1]='\0';
      return 1;
      }

parse_ ()
  /* 206 = open; 207 = close; 208 = comma; 209 = colon; */
{
  short xpxOrg,symflg, ernbr, f, spx, adx, jpx, j, i, g;
int kkk;
  static unsigned char cod209[2] = { 209, 0 };
  static unsigned char s1p[40];
  unsigned char bbtyp, nxtchr;
  unsigned char *bp = &bd[1];
  unsigned char *v1dp = &v1d[1];
  unsigned char Order[128]="";
  unsigned char deferedRef[2048]="";
  int deferedRslt;
  int deferedType=0;
  int OrderArg=1;

  static unsigned char code[26] = {
      /*0*/ 99, 99, 99, 99, 99, 99, 99, 99, 18, 19,
      /*10*/ 99, 20, 18, 99, 99, 21, 22, 23, 99, 99,
      /*20*/ 99, 99, 99, 99, 26, 27
      };

  static unsigned char opcode[256] = {
      /*0*/ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
      /*10*/ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
      /*20*/ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
      /*30*/ 99, 99, 99, 25, 99, 14, 99, 99, 24, 12,
      /*40*/ 0, 99, 2, 4, 99, 3, 99, 1, 99, 99,
      /*50*/ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
      /*60*/ 11, 8, 9, 17, 28, 99, 99, 99, 99, 99,
      /*70*/ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
      /*80*/ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
      /*90*/ 99, 15, 13, 16, 99, 7, 99, 99, 99, 99,
      /*100*/ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
      /*110*/ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
      /*120*/ 99, 99, 99, 99, 99, 99, 99, 99
      };

  static unsigned char ncode[256] = {
      /*0*/ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
      /*10*/ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
      /*20*/ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
      /*30*/ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
      /*40*/ 99, 99, 99, 99, 99, 99, 10, 99, 10, 10,
      /*50*/ 10, 10, 10, 10, 10, 10, 10, 10, 99, 99,
      /*60*/ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, // E
      /*70*/ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
      /*80*/ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
      /*90*/ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
      /*100*/ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, // e
      /*110*/ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
      /*120*/ 99, 99, 99, 99, 99, 99, 99, 99
      };


  static unsigned char dcode[256] = {
      /*0*/ 10, 99, 99, 99, 99, 99, 99, 99, 99, 99,
      /*10*/ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
      /*20*/ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
      /*30*/ 99, 99, 10, 10, 99, 10, 99, 99, 10, 10,
      /*40*/ 99, 10, 10, 10, 10, 10, 99, 10, 99, 99,
      /*50*/ 99, 99, 99, 99, 99, 99, 99, 99, 10, 99,
      /*60*/ 10, 10, 10, 10, 10, 99, 99, 99, 99, 99,
      /*70*/ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
      /*80*/ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
      /*90*/ 99, 10, 10, 10, 99, 10, 99, 99, 99, 99,
      /*100*/ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
      /*110*/ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
      /*120*/ 99, 99, 99, 99, 99, 99, 99, 99
      };

  static unsigned char operand[256] = {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 0, 1, 1, 2, 0,
      0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
      2, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 0, 2, 1, 0, 0, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 0, 0, 0, 0, 0
      };

//*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+                                                               +
//+       initialization                                          +
//+                                                               +
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  ierr=0;
  xpxOrg=xpx;
  xpx--;
  spx = 0;
  pd1[pd1len + 2] = 0;
  pd1[pd1len + 3] = 0;
  sdlim = pd1len + 3;

//*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+                                                               +
//+       main recursive internal entry point                     +
//+                                                               +
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

start:

      spx++;
      s1p[spx] = EMPTY; /*stack foundation */

nchar:

      if ((nxtchr = xd[++xpx]) == 0) goto finish;

      if (operand[nxtchr] == 1) goto scan_operand;

      if (nxtchr == CodedOpen) {

            unsigned char *p1, *p2;

            spx++;
            while (pd1[sdlim++]);
            if (sdlim >= symlen) return (31);
            p1 = &v1d[1];
            p2 = &pd1[sdlim];
            while (*p2++ = *p1++);
            *p2 = 0;
            p2--;
            *p2 = CodedOpen;
            s1p[spx] = OPENC;
            goto nchar;
            }

      if (nxtchr == ',') {

if (xd[xpx+1]==',' && xd[xpxOrg]=='$' && xd[xpxOrg+1]=='$') { 
/* $$^a(a,,b) case -> insert zero arg */
char tmp[2048];
strcpy(tmp,&xd[xpx+1]);
xd[xpx+1]='0';
strcpy(&xd[xpx+2],tmp);
}

            if (s1p[spx - 1] != OPENC) {
                  if (t2 > 0) goto finish;
                  return (16);
            	}

            //*===========================================
            //* concatenate stack tops and add coded comma    
            //*===========================================

            for (i = --sdlim; (pd1[i] = pd1[i + 1]); i++);	//* join tops 

            pd1[i] = CodedComma;
            pd1[i + 1] = 0;		                        //* coded comma 
            sdlim--;
            while (pd1[sdlim--]);                     	//* find new stack top start 
            sdlim += 2;
            spx--;			                        //* stack pointer 
            goto nchar;
            }

      if (nxtchr == ')') {

            if (s1p[spx - 1] != OPEN) {
                  if (s1p[spx - 1] != OPENC) {
                        if (s1p[spx] == OPENC) { /* fcn() type ref */
                              goto un_nest;
                              }
                        else return (16);
                        }

                  //*===========================================
                  //* fcn/array return section
                  //*===========================================

                  sdlim--;
                  for (i = sdlim; (pd1[i] = pd1[i + 1]); i++);    	//*join tops 
                  pd1[i] = CodedClose;
                  pd1[i + 1] = 0;	                                    //* coded close 
                  sdlim--;
                  while (pd1[sdlim--]);	                              //* find new stack top start 
                  sdlim += 2;
                  spx--;		/* stack pointer */
                  goto un_nest;
                  }

      //*===========================================
      //* precedence close paren 
      //*===========================================

      if (s1p[spx] != OPERAND)
	return (12);

      //*===========================================
      //* extract value from stack top 
      //*===========================================

      strcpy (bp, &pd1[sdlim]);

      do sdlim--; while (pd1[sdlim - 1]);	      //*compress stack 

      goto dec_stk;
      }

  if (nxtchr == ':') {

      i = sdlim;

      do i--; while (pd1[i - 1]);

      if (pd1[i] != '$' || tolower (pd1[i + 1]) != 's') goto finish;

      sdlim--;


	SSS=&pd1[sdlim]; 

	do {  // shift string down one and unify with $select(
		*SSS = *(SSS+1); 
		SSS++; 
		} while (*SSS);

      while (pd1[sdlim--]);

      sdlim += 2;
      strcat (&pd1[sdlim], cod209);

      spx--;
      goto nchar;
      }

  if (nxtchr == ' ' || nxtchr == '\t') goto finish;

  if (nxtchr == '^' && t2 == 2 && s1p[spx] == OPERAND) goto finish;

///*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+                                                               
//+       check for delimiters in list                            
//+                                                               
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  spx++;

      if (nxtchr == ']') {
            if (xd[xpx+1]==']') {
                  xpx++;
                  s1p[spx] = FOLLOWS; /* ] and ]] do the same for this version */                  
                  goto nchar;
                  }
            }

      if (nxtchr == QUOTE) {      //* insert not based operator code 
            xpx++;
            s1p[spx] = opcode[xd[xpx]];

            if (s1p[spx]!=99) {
                  s1p[spx] = code[opcode[xd[xpx]]];
                  if (xd[xpx+1]==']') xpx++; /* by pass second ] in `]] */
                  if (s1p[spx] != 99) goto nchar;
                  }

            xpx--;
            }

      if (nxtchr == '*' && xd[xpx + 1] == '*') { //* exponentiation code 
            xpx++;
            s1p[spx] = EXPONEN;
            goto nchar;
            }

//*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+                                                               
//+       insert code                                             
//+                                                               
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

      s1p[spx] = opcode[nxtchr];
      if (s1p[spx] != 99) goto nchar;
      ErrChar=nxtchr; return (12);

//*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+                                                               
//+       scan for operand                                        
//+                                                               
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

scan_operand:

      jpx = xpx;

      if (s1p[spx] == NOTPATTERN || s1p[spx] == PATTERN) {
            bd[1] = 0;
            patrn1 (&jpx, &ernbr);
            if (ernbr)
            return (ernbr);
            goto exec;
            }

//*==========================
// numeric operand
//*==========================

  if (ncode[xd[xpx]] == 10) {
      double temp;
      char Rargs[32]="";

      if (isalpha(xd[xpx+1])||xd[xpx+1]=='%') { /* call by ref argument */
            int i,j=0;
            for (i=xpx+1; xd[i]!=','&&xd[i]!='\0'&&xd[i]!=')'; i++) 
                  Rargs[j++]=xd[i];
            Rargs[j]='\0';
            fprintf(Out,"\t strcpy((char *) svPtr->Rargs[svPtr->Rargsx],(const char *) \"%s\");\n",Rargs);
            fprintf(Out,"\t svPtr->Rargsx++;\n");
            xpx++;
            goto skip_numeric;
            }

      for (i = 1; (bd[i] = xd[xpx]) && ncode[bd[i]] == 10; (i++, xpx++) );

      if (i == 1 && bd[1] == '.') return (9);

      if (tolower(bd[i])=='e') {
            i++; xpx++;
            if (xd[xpx]!='+' && xd[xpx]!='-' 
                  && !isdigit(xd[xpx])) return 9; // e type requires +/- or digit
            bd[i]=xd[xpx];
            i++; xpx++;
            if (!isdigit(xd[xpx-1]) && !isdigit(xd[xpx])) return 9;  // e type requires an exponent
            while (1) {  // scan rest or exponent, if any
                  if (!isdigit(xd[xpx])) break;
                  bd[i]=xd[xpx];
                  i++; xpx++;
                  }
            }
             
      bd[i] = 0;
      if (sscanf(&bd[1],"%lf",&temp)==0) return(12);
      sprintf(&bd[1],"%.15g",temp);
      cannon (bp);

            {
            char t[512];
            t[0] = '\"';
            strcpy (&t[1], &bd[1]);
            strcat (t, "\"");
            strcpy (&bd[1], t);
            }

      xpx--;
      goto exec;
    }

skip_numeric:

//*==========================
// literal operand
//*==========================

  if (xd[xpx] == '"') {

      j = 0;
      bd[++j] = '\"';

      while (1) {

            while (xd[++xpx] != '"') {

                  if (xd[xpx] == '\\') {
                        bd[++j] = '\\';
                        bd[++j] = '\\';
                        continue;
                        }

	            if (xd[xpx] == '\'') {
                        bd[++j] = '\\';
                        bd[++j] = '\'';
                        continue;
                        }

	            if ((bd[++j] = xd[xpx]) == 0)
		      return (2);
	            }

            if (xd[xpx + 1] != '"') {
                  bd[++j] = '\"';
                  bd[++j] = 0;
                  goto exec;
                  }

            xpx++;
            bd[++j] = '\\';
            bd[++j] = '\"';
            }
      }

//*==========================
// variable name
//*==========================

  v1d[1] = xd[xpx++];
  j = 2;

  while (1) {

      if (dcode[xd[xpx]] == 10) {
            v1d[j] = 0;
            xpx--;
            goto var1;
            }

      v1d[j++] = xd[xpx];

      if (xd[xpx] == '(') {
            v1d[--j] = 0;
            xd[xpx--] = CodedOpen;
            goto start;		            //* recurse 
            }
      xpx++;
    }

un_nest:			                  //* copy answer from stack 

      while (pd1[--sdlim]);
      strcpy (v1dp, &pd1[sdlim + 1]);
      while (pd1[--sdlim]);
      sdlim++;
      spx -= 2;

var1:

      if (t0px == 1 && spx == 1) {
            spx--;
            t0px = 0;
            return (0);
            }

  if (v1d[1] == '^') {  /* global var */

      if (!isalpha(v1d[2]) && ( v1d[2] == '(' /* naked case */) )
            return 9001; /* not valid array reference */

      g = RETRIEVE;


//*=============================
//  build global array reference
//*=============================

            {
	      char t[1024];
	      int i, j = 0;

	      for (i = 1; v1d[i] != 0; i++) {
	            if (v1d[i] >= 32 && v1d[i] <= 127) t[j++] = v1d[i];
	            else break;
	            }

	      t[j++] = '\\'; t[j++] = 'x'; t[j++] = '0';
	      t[j++] = v1d[i] == 0 ? 0 : '1'; 
              t[j] = 0;

	      fprintf (Out, "\t strmove((unsigned char *) gtmp,(unsigned char *) \"%s\");\n", t);


            if (v1d[i]!='\0') {
	            i++;

	            while (1) {
	                  j = 0;
	                  while (v1d[i] <= 127 && v1d[i] >= 32) t[j++] = v1d[i++];
	                  t[j] = 0;
			      if (strlen(t)==0) strcpy(t,"\"\"");
                        if (strncmp(t,"#G#",3)==0 || strncmp(t,"#S#",3)==0) 
      	                  fprintf (Out, "\t strcatx((unsigned char *) gtmp,(unsigned char *) %s);\n", Extract2(t));
	                  else fprintf (Out, "\t strcatx((unsigned char *) gtmp,(unsigned char *) %s);\n", t);
	                  if (v1d[++i] != 0) continue;
	                  else break;
	                  }
                  }

            memcheck (iiitmp);

            if (toupper (pd1[sdlim + 1]) == 'Z' &&
                toupper (pd1[sdlim + 2]) == 'Z') { // NO EVAL GLOBAL ZZ INTERFACE
                fprintf (Out, "\t strmove((unsigned char *) tmp%d,(unsigned char *) \"\");\n", iiitmp);
                fprintf (Out, "\t strcat((char *) tmp%d,(char *) gtmp);\n", iiitmp, t);
                fprintf (Out, "\t strcat((char *) tmp%d,(char *) \"\");\n", iiitmp);
                }

            else fprintf (Out, "\t strmove((unsigned char *) tmp%d,(unsigned char *) gtmp);\n", iiitmp, t);
            }

      iiitmp++;
      memcheck (iiitmp);
      sprintf(setname,"tmp%d",iiitmp-1);
      sprintf (bp, "#G#tmp%d#tmp%d#", iiitmp - 1, iiitmp, iiitmp); 

      if (toupper (pd1[sdlim + 1]) == 'Z' &&
          toupper (pd1[sdlim + 2]) == 'Z') // NO EVAL GLOBAL ZZ INTERFACE
          sprintf (bp, "tmp%d", iiitmp - 1 ); 
	
      iiitmp++; memcheck (iiitmp);
      f = 1;
      tpx = f;
      goto exec;
      }                 //* normal global 

//*==============================================================
//*                                                               
//*       built-in variables/fcns                                 
//*                                                               
//*==============================================================

  if (v1d[1] == '$') {

      v1d[2]=tolower(v1d[2]);

      if (v1d[2] == '$') goto no_arg;

//*==========
//* $1 -> $99 
//*==========

      if ((isdigit(v1d[2]) && v1d[3]=='\0') ||
           (isdigit(v1d[3]) && isdigit(v1d[4]) && v1d[5]=='\0')) {
                  v1d[1]='_'; /* change $ to _ and revist */
                  goto var1;  /* revisit */
                  }

//*========
//* $test 
//*========

      if (strcasecmp (&v1d[1], "$test") == 0 ||
          strcasecmp (&v1d[1], "$t") == 0) {

	  memcheck (iiitmp);
	  fprintf (Out, "\t if (svPtr->tpx) tmp%d[0]=\'1\'; " "/* $test */\n", iiitmp);
	  fprintf (Out, "\t else tmp%d[0]=\'0\';\n", iiitmp);
	  fprintf (Out, "\t tmp%d[1]=\'\\0\';\n", iiitmp);
	  sprintf (bp, "tmp%d", iiitmp);
	  iiitmp++;
        memcheck (iiitmp);
	  goto exec;
	  }

//*========
//* $io   
//*========

      if (strcasecmp (&v1d[1], "$io") == 0 || strcasecmp (&v1d[1], "$i") == 0) {
            memcheck (iiitmp);
            fprintf (Out, "\t sprintf((char *) tmp%d,\"%%d\",svPtr->io);" " /* $io */\n", iiitmp);
            sprintf (bp, "tmp%d", iiitmp);
            iiitmp++;
            memcheck (iiitmp);
            goto exec;
            }

//*===========
//* $principal
//*===========

      if (strcasecmp (&v1d[1], "$principal") == 0 || strcasecmp (&v1d[1], "$p") == 0) {
            memcheck (iiitmp);
            fprintf (Out, "\t sprintf((char *) tmp%d,\"%%d\",5);" " /* $principal */\n", iiitmp);
            sprintf (bp, "tmp%d", iiitmp);
            iiitmp++;
            memcheck (iiitmp);
            goto exec;
            }

//*========
//* $x    
//*========

      if (strcasecmp (&v1d[1], "$x") == 0 || strcasecmp (&v1d[1], "$x") == 0) {

	  memcheck (iiitmp);
	  fprintf (Out, "\t sprintf((char *) tmp%d,\"%%d\",svPtr->hor[svPtr->io]);" " /* $x */\n", iiitmp);
	  sprintf (bp, "tmp%d", iiitmp);
	  iiitmp++;
        memcheck (iiitmp);
	  goto exec;
	  }

//*=========
//* $y   
//*=========

      if (strcasecmp (&v1d[1], "$y") == 0 || strcasecmp (&v1d[1], "$y") == 0) {

	  memcheck (iiitmp);
	  fprintf (Out, "\t sprintf((char *) tmp%d,\"%%d\",svPtr->ver[svPtr->io]);" " /* $y */\n", iiitmp);
	  sprintf (bp, "tmp%d", iiitmp);
	  iiitmp++;
        memcheck (iiitmp);
	  goto exec;
	  }

//*=========
//* $h    
//*=========

      if (strcasecmp (&v1d[1], "$horolog") == 0 ||
          strcasecmp (&v1d[1], "$h") == 0) {

	  memcheck (iiitmp);
	  fprintf (Out, "\t _horolog(tmp%d);" " /* $h */\n", iiitmp);
	  sprintf (bp, "tmp%d", iiitmp);
	  iiitmp++;
        memcheck (iiitmp);
	  goto exec;
	  }

//*=========
//* $char 
//*=========

      if (strncasecmp (&v1d[1], "$char", 5) == 0 ||
          strncasecmp (&v1d[1], "$c", 2) == 0) {

	  int i, j;
	  char tmp[1024];

	  for (i = 1; v1d[i] >= 32 && v1d[i] <= 127; i++);	//* fcn nme 
//	  strcpy (v1d, &v1d[i + 1]);	                        //* remove function name STRCPY
	for (SSS=v1d,TTT=&v1d[i+1]; *TTT != 0; SSS++,TTT++) *SSS = *TTT;
        *SSS=0;
	  fprintf (Out, "\t _j=0;\n");
	  i = 0;

      while (1) {
            j = i;
            for (; v1d[i] >= 32 && v1d[i] <= 127; i++);

            if (v1d[i] == 0) {
                  memcheck (iiitmp);
                  fprintf (Out, "\t tmp%d[_j]=0;\n", iiitmp + 1);
                  sprintf (bp, "tmp%d", iiitmp + 1);
                  iiitmp++;
                  memcheck (iiitmp);
                  iiitmp++;
                  memcheck (iiitmp);
                  goto exec;
                  }

            v1d[i++] = 0;

            fprintf (Out, "\t strmove((unsigned char *) tmp%d,(unsigned char *) %s);\n", iiitmp, Extract2(&v1d[j]));
            fprintf (Out, "\t _i=atol((char *) tmp%d);\n", iiitmp);
            fprintf (Out, "\t if (_i>0) ");
            fprintf (Out, "\t tmp%d[_j++]=_i;\n", iiitmp + 1);
            }
      }

//*============
//* $FNumber 
//*============

      if (strncasecmp (&v1d[1], "$fnumber", 5) == 0 ||
          strncasecmp (&v1d[1], "$fn", 3) == 0) {

            int i, j, r, a;
            char tmp[1024];

            for (i = 1; v1d[i] >= 32 && v1d[i] <= 127; i++);	//* fcn nme 

//            strcpy (v1d, &v1d[i + 1]);	                        //* remove function name  STRCPY

	for (SSS=v1d,TTT=&v1d[i+1]; *TTT != 0; SSS++,TTT++) *SSS = *TTT;
        *SSS=0;

            i = 0;
            a = 0;
            strcpy (tmp, "");

            while (1) {
                  j = i;
                  for (; v1d[i] >= 32 && v1d[i] <= 127; i++);
                  if (v1d[i] == 0) {
                        if (a == 0 || a > 3) return (a);
                        memcheck (iiitmp);
                        fprintf (Out, "\t _fnumber(" " (unsigned char *)tmp%d, (unsigned char *)%s, svPtr);\n", iiitmp, tmp);
                        sprintf (bp, "tmp%d", iiitmp);
                        iiitmp++;
                        memcheck (iiitmp);
                        goto exec;
                        }

	      v1d[i++] = 0;
	      if (a++)
		strcat (tmp, ", (unsigned char *)");
	      strcat (tmp, Extract2(&v1d[j]));
            }
      }

//*============
//* $extract 
//*============

      if (strncasecmp (&v1d[1], "$extract", 5) == 0 ||
          strncasecmp (&v1d[1], "$e", 2) == 0) {
            if (Extract(v1d,bp)) return 9003;;
            goto exec;
            }

//*============
//* $length  
//*============

      if (strncasecmp (&v1d[1], "$length", 5) == 0 ||
          strncasecmp (&v1d[1], "$l", 2) == 0) {

	  int i, j, r, a;
	  char tmp[1024];

	  for (i = 1; v1d[i] >= 32 && v1d[i] <= 127; i++);	//* fcn nme 
//	  strcpy (v1d, &v1d[i + 1]);	                        //* remove function name 
	for (SSS=v1d,TTT=&v1d[i+1]; *TTT != 0; SSS++,TTT++) *SSS = *TTT;
        *SSS=0;
	  i = 0;
	  a = 0;
	  strcpy (tmp, "");

	  while (1) {

	      j = i;
	      for (; v1d[i] >= 32 && v1d[i] <= 127; i++);

	      if (v1d[i] == 0) {
                  if (a == 0 || a > 3) return (a);
                  if (a == 1) strcat (tmp, ",(unsigned char *) \"\"");
                  memcheck (iiitmp);
                  fprintf (Out, "\t _length(" "(unsigned char *) tmp%d, (unsigned char *)%s);\n", iiitmp, tmp);
                  sprintf (bp, "tmp%d", iiitmp);
                  iiitmp++;
                  memcheck (iiitmp);
                  goto exec;
                  }

	      v1d[i++] = 0;
	      if (a++)
		strcat (tmp, ",(unsigned char *) ");
	      strcat (tmp, Extract2(&v1d[j]));
            }
	}

//*============
//* $find    
//*============

      if (strncasecmp (&v1d[1], "$find", 5) == 0 ||
          strncasecmp (&v1d[1], "$f", 2) == 0) {

	  int i, j, r, a;
	  char tmp[1024];

	  for (i = 1; v1d[i] >= 32 && v1d[i] <= 127; i++);	//* fcn name
//	  strcpy (v1d, &v1d[i + 1]);	                        //* remove function name 
	for (SSS=v1d,TTT=&v1d[i+1]; *TTT != 0; SSS++,TTT++) *SSS = *TTT;
        *SSS=0;
	  i = 0;
	  a = 0;
	  strcpy (tmp, "");

	  while (1) {
	      j = i;
	      for (; v1d[i] >= 32 && v1d[i] <= 127; i++);
	      if (v1d[i] == 0) {
                  if (a == 0 || a > 3) return (a);
                  if (a == 2) strcat (tmp, ", (unsigned char *)\"-1\"");
                  memcheck (iiitmp);
                  fprintf (Out, "\t _find(" " (unsigned char *)tmp%d, (unsigned char *)%s);\n", iiitmp, tmp);
                  sprintf (bp, "tmp%d", iiitmp);
                  iiitmp++;
                  memcheck (iiitmp);
                  goto exec;
                  }

	      v1d[i++] = 0;
	      if (a++)
		strcat (tmp, ", (unsigned char *)");
	      strcat (tmp, Extract2(&v1d[j]));
            }
	}


//*============
//* $ascii   
//*============

      if (strncasecmp (&v1d[1], "$ascii", 5) == 0 ||
          strncasecmp (&v1d[1], "$a", 2) == 0) {

	  int i, j, r, a;
	  char tmp[1024];

	  for (i = 1; v1d[i] >= 32 && v1d[i] <= 127; i++);	//* fcn nme 
//	  strcpy (v1d, &v1d[i + 1]);	                        //* remove function name 
	for (SSS=v1d,TTT=&v1d[i+1]; *TTT != 0; SSS++,TTT++) *SSS = *TTT;
        *SSS=0;
	  i = 0;
	  a = 0;
	  strcpy (tmp, "");

	  while (1) {
	      j = i;
	      for (; v1d[i] >= 32 && v1d[i] <= 127; i++);

	      if (v1d[i] == 0) {
                  if (a == 0 || a > 2) return (a);
                  if (a == 1) strcat (tmp, ", (unsigned char *)\"-1\"");
                  memcheck (iiitmp);
                  fprintf (Out, "\t _ascii(" " (unsigned char *)tmp%d, (unsigned char *)%s);\n", iiitmp, tmp);
                  sprintf (bp, "tmp%d", iiitmp);
                  iiitmp++;
                  memcheck (iiitmp);
                  goto exec;
                  }
	      v1d[i++] = 0;
	      if (a++)
		strcat (tmp, ", (unsigned char *)");
	      strcat (tmp, Extract2(&v1d[j]));
            }
      }

//*============
//* $justify 
//*============

      if (strncasecmp (&v1d[1], "$justify", 5) == 0 ||
          strncasecmp (&v1d[1], "$job", 4) == 0 ||
          strncasecmp (&v1d[1], "$j", 2) == 0) {

	  int i, j, r, a;
	  char tmp[1024];

	  for (i = 1; v1d[i] >= 32 && v1d[i] <= 127; i++);	//* fcn name 

	  if (v1d[i] == 0) strcpy (v1d, "");
//	  else strcpy (v1d, &v1d[i + 1]);	                  //* remove function name 
else {
	for (SSS=v1d,TTT=&v1d[i+1]; *TTT != 0; SSS++,TTT++) *SSS = *TTT;
        *SSS=0;
}

	  i = 0;
	  a = 0;
	  strcpy (tmp, "");

	  while (1) {
	      j = i;
	      for (; v1d[i] >= 32 && v1d[i] <= 127; i++);

	      if (v1d[i] == 0) {
                  if (a == 0) { //* $job 
                        #ifdef _MSC_VER
                        fprintf (Out, "\t sprintf((char *) tmp%d,\"%%d\",_getpid()); // $job DOS\n", iiitmp);
                        #else
                        fprintf (Out, "\t sprintf((char *) tmp%d,\"%%d\",getpid()); //$job linux\n", iiitmp);
                        #endif
                        }

                  else {
                        if (a == 1 || a > 3) return (a);
                        if (a == 2) strcat (tmp, ",(unsigned char *) \"-1\"");
                        fprintf (Out, "\t _justify(" " (unsigned char *)tmp%d, (unsigned char *)%s);\n", iiitmp, tmp);
                        }

                  memcheck (iiitmp);
                  sprintf (bp, "tmp%d", iiitmp);
                  iiitmp++;
                  memcheck (iiitmp);
                  goto exec;
                  }

	      v1d[i++] = 0;
	      if (a++)
		strcat (tmp, ", (unsigned char *)");
	      strcat (tmp, Extract2(&v1d[j]));
            }
	}

//*============
//* $piece 
//*============

      if (strncasecmp (&v1d[1], "$piece", 6) == 0 ||
          strncasecmp (&v1d[1], "$p", 2) == 0) {

	  int i, j, r, a;
	  char tmp[1024];

	  for (i = 1; v1d[i] >= 32 && v1d[i] <= 127; i++);	//* fcn name 

	  if (v1d[i] == 0) strcpy (v1d, "");
//	  else strcpy (v1d, &v1d[i + 1]);	                  //* remove function name 
else {
	for (SSS=v1d,TTT=&v1d[i+1]; *TTT != 0; SSS++,TTT++) *SSS = *TTT;
        *SSS=0;
}

	  i = 0;
	  a = 0;
	  strcpy (tmp, "");

	  while (1) {
	      j = i;
	      for (; v1d[i] >= 32 && v1d[i] <= 127; i++);

	      if (v1d[i] == 0) {
                  if (a == 1 || a > 4) return (a);
                  if (a == 2) strcat (tmp, ",(unsigned char *) \"-1\"");
                  if (a < 4) strcat (tmp, ",(unsigned char *) \"-1\"");
                  memcheck (iiitmp);
                  fprintf (Out, 
                  "\t _piece((unsigned char *) tmp%d,(unsigned char *) %s,0,(unsigned char *) \"\",svPtr);\n", iiitmp, Extract2(tmp));
                  sprintf (bp, "tmp%d", iiitmp);
                  iiitmp++;
                  memcheck (iiitmp);
                  goto exec;
                  }

	      v1d[i++] = 0;
	      if (a++)
		strcat (tmp, ",(unsigned char *) ");
	      strcat (tmp, Extract2(&v1d[j]));
            }
	}

//*============
//* $select  
//*============

      if (strncasecmp (&v1d[1], "$select", 5) == 0 ||
          strncasecmp (&v1d[1], "$storage", 4) == 0 ||
          strncasecmp (&v1d[1], "$s", 2) == 0) {

            int i, j, k = 0, r, a;
            char tmp[1024];

            for (i = 1; v1d[i] >= 32 && v1d[i] <= 127; i++);	//* fcn name 

            if (v1d[i] == 0) strcpy (v1d, "");
//            else strcpy (v1d, &v1d[i + 1]);	                  //* remove function name 

	else {
		for (SSS=v1d,TTT=&v1d[i+1]; *TTT != 0; SSS++,TTT++) *SSS = *TTT;
        	*SSS=0;
		}

            i = 0;
            a = 0;
            strcpy (tmp, "");

            while (1) {
                  k++;
                  j = i;
                  memcheck (iiitmp);
	            for (; v1d[i] >= 32 && v1d[i] <= 127; i++);
	            if (v1d[i] == 0) {
                        if (a == 0) {		/* $storage */
                              fprintf (Out, "\t strmove((unsigned char *) tmp%d,(unsigned char *) " "\"999\");\n", iiitmp);
                              }

                  else {
                        if (k > 20)
                        return (99);

                        while (k < 21) {
                              strcat (tmp, ",");
                              strcat (tmp, "NULL");
                              k++;
                              }

		            fprintf (Out, "\t _select((unsigned char *) tmp%d, (unsigned char *) %s,svPtr);\n", iiitmp, tmp);
                        }

                  sprintf (bp, "tmp%d", iiitmp);
                  iiitmp++;
                  memcheck (iiitmp);
                  goto exec;
                  }

            v1d[i++] = 0;
	      if (a++)
		strcat (tmp, ",(unsigned char *)");
		strcat (tmp, Extract2(&v1d[j]));
            }
	}

//*============
//* $random  
//*============

      if (strncasecmp (&v1d[1], "$random", 5) == 0 ||
          strncasecmp (&v1d[1], "$r", 2) == 0 &&
          strncasecmp (&v1d[1], "$re", 3) !=0) {

	  int i, j, r, a;
	  char tmp[1024];

	  for (i = 1; v1d[i] >= 32 && v1d[i] <= 127; i++);	      //* fcn nme 

	  if (v1d[i] == 0) strcpy (v1d, "");
//	  else strcpy (v1d, &v1d[i + 1]);	                        //* remove function name 
else {
	for (SSS=v1d,TTT=&v1d[i+1]; *TTT != 0; SSS++,TTT++) *SSS = *TTT;
        *SSS=0;
}

	  i = 0;
	  a = 0;
	  strcpy (tmp, "");

	  while (1) {
	      j = i;
	      for (; v1d[i] >= 32 && v1d[i] <= 127; i++);

	      if (v1d[i] == 0) {
                  memcheck (iiitmp);
                  fprintf (Out, "\t _random((unsigned char *) tmp%d,(unsigned char *) %s);\n", iiitmp, tmp);
                  sprintf (bp, "tmp%d", iiitmp);
                  iiitmp++;
                  memcheck (iiitmp);
                  goto exec;
                  }

	      v1d[i++] = 0;
	      if (a++)
		strcat (tmp, ",");
	      strcat (tmp, Extract2(&v1d[j]));
            }
	}

//*===============================
//* other functions: build parameter list string */
//*===============================

      {
      	char t[1024], h[6];
	      int i, j = 0;
            int flg=0;

	      for (i = 1; v1d[i] != 0; i++) {
                  if (v1d[i] >= 32 && v1d[i] <= 127) t[j++] = v1d[i];
                  else break;
                  }

	      if (v1d[i] == 0) {
                  t[j] = 0;
                  fprintf (Out, "\t strcpy((char *) &gtmp[1],(const char *) \"%s\");\n", t);
                  goto no_arg;
                  }

            t[j] = 0;

            if (strncasecmp(&t[1],"text",4) ==  0) { /* $text() function */
                  ExpandText(v1d,i,bp);
                  goto fcn_proc_done;
                  }

//            if (strncasecmp(&t[1],"ql",2) == 0 ||
//                strncasecmp(&t[1],"qlength",7) == 0) { /* $qlength() function */
//printf("xxxx %s\n",&v1d[1]);
//                  ExpandQlength(v1d,i,bp);
//                  goto fcn_proc_done;
//                  }

            if (tolower(t[1]) ==  'o') { /* $order() function */
                  ExpandOrder(v1d,i,bp);
                  goto fcn_proc_done;
                  }

            if (tolower(t[1]) ==  'd') { /* $data() function */
                  ExpandData(v1d,i,bp);
                  goto fcn_proc_done;
                  }

            if (tolower(t[1]) ==  'n' && tolower(t[2]) == 'a') { /* $name() function */
                  ExpandName(v1d,i,bp);
                  goto fcn_proc_done;
                  }

		if (tolower(t[1]) ==  'q' && tolower(t[2]) == 's') { /* $qsubscript() function */
				ExpandQS(v1d,i,bp);
                  		goto fcn_proc_done;
                  		}

            if (tolower(t[1]) ==  'n') { /* $next() function */
                  ExpandNext(v1d,i,bp);
                  goto fcn_proc_done;
                  }

            if (tolower(t[1]) ==  'g') { /* $get() function */
                  ExpandGet(v1d,i,bp);
                  goto fcn_proc_done;
                  }

            fprintf (Out, "\t strmove((unsigned char *)  &gtmp[1],(unsigned char *) \"\");\n");

	      sprintf (h, "%2x", v1d[i]);
	      t[j++] = '\\';
	      t[j++] = 'x';
	      t[j++] = h[0];
	      t[j++] = h[1];
	      t[j] = 0;
	      fprintf (Out, "\t strcat((char *) &gtmp[1],\"%s\");\n", t);
	      i++;

	      while (1) {
                  j = 0;
                  while (v1d[i] <= 127 && v1d[i] >= 32) t[j++] = v1d[i++];
                  t[j] = 0;
                  fprintf (Out, "\t strcat((char *) &gtmp[1],(char *) %s);\n", Extract2(t));
                  j = 0;
                  sprintf (h, "%2x", v1d[i]);
                  t[j++]='\\'; t[j++]='x'; t[j++]=h[0]; t[j++]=h[1]; t[j]=0;
                  fprintf (Out, "\t strcat((char *) &gtmp[1],\"%s\");\n", t);
                  if (v1d[++i] != 0) continue;
                  else break;
                  }

no_arg:

            if (v1d[2] == 'Z' || v1d[2] == 'z') {
                  memcheck (iiitmp);
                  fprintf (Out, "\t zfcn(gtmp,tmp%d,svPtr);\n", iiitmp);
                  sprintf (bp, "tmp%d", iiitmp);
                  iiitmp++;
                  memcheck (iiitmp);
                  }

	      else if (v1d[2] == '$') {
                  memcheck (iiitmp);
                  if (MyFunc (&v1d[3], iiitmp)!=0) return 9002;
                  sprintf (bp, "tmp%d", iiitmp);
                  iiitmp++;
                  memcheck (iiitmp);
                  }
      
	      else {
                  fprintf (Out, "\t strmove((unsigned char *) &svPtr->v1d[1],(unsigned char *) &gtmp[1]);\n");
                  memcheck (iiitmp);
                  fprintf (Out, "\t fcn(svPtr);\n");
                  fprintf (Out, "\t strmove((unsigned char *) tmp%d,(unsigned char *) &svPtr->bd[1]);\n",iiitmp);
                  sprintf (bp, "tmp%d", iiitmp);
                  iiitmp++;
                  memcheck (iiitmp);
                  }
            }

fcn_proc_done:

            if (ierr == 0) goto exec;
            return (ierr);
    }


//*===============================================================
//+       retrieve look-up                                        
//+===============================================================

  if (v1d[1] == PREDICATEVAR) {
      strcpy (bp, v1dp);
      goto exec;
      }

  {
      int i, k, j;		//* array references - insert brackets
      char tmp[1024];
      for (i = 0; v1dp[i] != 0; i++) if (v1dp[i] > 127) goto has_array;
      goto no_array;

has_array:

    fprintf (Out, "{\t // local array setup\n\t int i;\n");

    for (i = 0; v1dp[i] != 0; i++)
      if (v1dp[i] == 206) { // Open
            v1dp[i] = 0;
            fprintf (Out, "\t strmove((unsigned char *) tmp%d,(unsigned char *) \"%s\");\n",iiitmp, v1dp);
            fprintf (Out, "\t i=strlen((const char *) tmp%d);\n",iiitmp);
            fprintf (Out, "\t tmp%d[i]=206;\n",iiitmp);
            fprintf (Out, "\t tmp%d[i+1]=0;\n",iiitmp);
            v1dp[i] = 206;
            for (j = i + 1; v1dp[j] != 0; j++)
                  if (v1dp[j] == 207 || v1dp[j] == 208) break;
            k = v1dp[j];
            v1dp[j] = 0;
            if (strncmp(&v1dp[i+1],"#S#",3)==0 || strncmp(&v1dp[i+1],"#G#",3)==0) 
                  fprintf (Out, "\t strcat((char *) tmp%d,(char *) %s);\n", iiitmp, Extract2(&v1dp[i+1])  );
            else fprintf (Out, "\t strcat((char *) tmp%d,(char *) %s);\n",iiitmp, &v1dp[i + 1]);
            fprintf (Out, "\t i=strlen((const char *) tmp%d);\n",iiitmp);
            fprintf (Out, "\t tmp%d[i]=%d;\n",iiitmp, k);
            fprintf (Out, "\t tmp%d[i+1]=0;\n",iiitmp);
            v1dp[j] = k;
            i = j - 1;
            }

      else if (v1dp[i] == 207) { // Close

      memcheck (iiitmp);

      sprintf(setname,"tmp%d",iiitmp);
      sprintf (bp, "#S#tmp%d#tmp%d#", iiitmp , iiitmp+1); 
      iiitmp=iiitmp+2; memcheck (iiitmp);

      fprintf (Out, "\t }\n");
      break;
      }

      else if (v1dp[i] == 208) { //* comma 
            for (j = i + 1; v1dp[j] != 0; j++)
            if (v1dp[j] == 207 || v1dp[j] == 208) break;
            k = v1dp[j];
            v1dp[j] = 0;
            if (strncmp(&v1dp[i+1],"#S#",3)==0) 
                  fprintf (Out, "\t strcat((char *) tmp%d,(char *) %s);\n", iiitmp, Extract2(&v1dp[i+1])  );
            else fprintf (Out, "\t strcat((char *) tmp%d,(char *) %s);\n",iiitmp, &v1dp[i + 1]);
            fprintf (Out, "\t i=strlen((const char *) tmp%d);\n",iiitmp);
            fprintf (Out, "\t tmp%d[i]=%d;\n",iiitmp, k);
            fprintf (Out, "\t tmp%d[i+1]=0;\n",iiitmp);
            v1dp[j] = k;
            i = j - 1;
            }
      }

  goto no_array1;

no_array:

      symflg=11;

      memcheck (iiitmp);
      if (!cvar(v1dp))  {
//            fprintf (Out, "\t if (sym_(%d,\"%s\",tmp%d,svPtr)==NULL) ", symflg, v1dp, iiitmp);
            strcpy(setname,"\""); // ???
            strcat(setname,v1dp);
            strcat(setname,"\"");
//            fprintf (Out, "VariableNotFound(svPtr->LineNumber);\n");
            memcheck (iiitmp);
//nnnn            sprintf (&bd[1], "tmp%d", iiitmp);
            sprintf (bp, "#S#%s#tmp%d#", setname, iiitmp); 
            iiitmp++;
            memcheck (iiitmp);
            }

no_array1:

  if (cvar(v1dp)) {
      strcpy(&bd[1], v1dp);
      }

  if (pd1[sdlim] != '$') goto exec;

//*===============================================================
//*       process value in bb or bd                               
//*===============================================================

exec:

  if (s1p[spx] != EMPTY && s1p[spx] != OPEN && s1p[spx] != OPENC) goto nxt_expr;

  spx++;
  while (pd1[sdlim++]);
  if (sdlim >= symlen) return (31);

  strcpy (&pd1[sdlim], bp);

  s1p[spx] = OPERAND;
  goto nchar;

//*===============================================================
//*       process expression - check  for operator on stack top   
//*==============================================================

nxt_expr:

  if (s1p[spx] == OPEN || s1p[spx] == OPERAND) return (11);

//*=============================================================
//*       check for number under operator                       
//*=============================================================

  if (s1p[spx - 1] != OPERAND) {
      switch (s1p[spx]) {

default:

	  return (1);

case INDIRECT:

//	  if (kflg) {
//	      strcpy (&v1d[1], bp);
//	      return (0);
//	      }

	  fprintf (Out, "\t strmove((unsigned char *) xd,(unsigned char *) %s);\n", Extract2(bp));
	  fprintf (Out, "\t svPtr->xpx=0;\n");
	  fprintf (Out, "\t svPtr->t0px=0;\n");
	  fprintf (Out, "\t _i=parse_(); \n");
	  fprintf (Out, "\t if (_i!=0) ErrorMessage(\"Indirect expression error\",svPtr->LineNumber);\n");
	  memcheck (iiitmp);
	  fprintf (Out, "\t strmove((unsigned char *) tmp%d,(unsigned char *) &pd1[sdlim]);\n", iiitmp);
	  sprintf (bp, "tmp%d", iiitmp);
	  iiitmp++;
        memcheck (iiitmp);
	  break;
	  spx--;
	  strcat (bp, &xd[xpx + 1]);
	  break;
	  strcpy (&xd[1], bp);
	  xpx = 0;
	  goto nchar;
	  break;

case MINUS:		//* unary minus 

      memcheck (iiitmp);
      fprintf (Out, "\t mult((char *) %s,\"-1\",(char *) tmp%d);\n", Extract2(bp), iiitmp);
      sprintf (bp, "tmp%d", iiitmp);
      iiitmp++;
      memcheck (iiitmp);
      break;

case 18: // not not

      memcheck (iiitmp);
      fprintf (Out,
            "\t if (numcomp1((unsigned char *) %s,0)==0) strmove((unsigned char *) tmp%d,(unsigned char *) \"1\");\n"
            "\t    else strmove((unsigned char *) tmp%d,(unsigned char *) \"0\");\n", Extract2(bp), iiitmp, iiitmp);
      sprintf (bp, "tmp%d", iiitmp);
      iiitmp++;
      memcheck (iiitmp);

case NOT: //* unary not 

      memcheck (iiitmp);
      fprintf (Out,
            "\t if (numcomp1((unsigned char *) %s,0)==0) strmove((unsigned char *) tmp%d,(unsigned char *) \"1\");\n"
            "\t    else strmove((unsigned char *) tmp%d,(unsigned char *) \"0\");\n", Extract2(bp), iiitmp, iiitmp);
      sprintf (bp, "tmp%d", iiitmp);
      iiitmp++;
      memcheck (iiitmp);
      break;

case PLUS: //* unary plus 

      memcheck (iiitmp);
      fprintf (Out, "\t add((char *) %s,(char *) \"0\",(char *) tmp%d);\n", Extract2(bp), iiitmp);
      sprintf (bp, "tmp%d", iiitmp);
      iiitmp++;
      memcheck (iiitmp);
      break;

  } //* switch 

      spx--;
      goto nxt_operator;
}

//*=============================
//* extract value under operator 
//*=============================

  for (adx = sdlim--; pd1[sdlim - 1]; sdlim--);

  if (strncmp(&pd1[adx],"#G#",3)==0) strcpy(&pd1[adx],Extract2(&pd1[adx]));
  if (strncmp(bp,"#G#",3)==0) strcpy(bp,Extract2(bp));

  if (strncmp(&pd1[adx],"#S#",3)==0) strcpy(&pd1[adx],Extract2(&pd1[adx]));
  if (strncmp(bp,"#S#",3)==0) strcpy(bp,Extract2(bp));

//* branch depending upon operator 

  switch (s1p[spx]) {

case OPERAND:
case EMPTY:
case NOT:
default:
      return (12);

case DIVIDE:

      memcheck (iiitmp);
      fprintf (Out, "\t divx((char *) %s,(char *) %s,(char *) tmp%d);\n", &pd1[adx], bp, iiitmp);
      sprintf (bp, "tmp%d", iiitmp);
      iiitmp++;
      memcheck (iiitmp);
      break;

case EXPONEN:

      memcheck (iiitmp);
      fprintf (Out, "\t expx((const char *) %s,(const char *) %s,(char *) tmp%d);\n", &pd1[adx], bp, iiitmp);
      sprintf (bp, "tmp%d", iiitmp);
      iiitmp++;
      memcheck (iiitmp);
      break;

case MULTIPLY:

      memcheck (iiitmp);
      if (ConCheck(bp)) fprintf (Out, "\t mult( (const char *) %s, \"%s\", (char *) tmp%d);\n", &pd1[adx], bp, iiitmp);
      else fprintf (Out, "\t mult((char *) %s,(char *) %s,(char *) tmp%d);\n", &pd1[adx], bp, iiitmp);
      sprintf (bp, "tmp%d", iiitmp);
      iiitmp++;
      memcheck (iiitmp);
      break;

case MINUS:

      memcheck (iiitmp);
      fprintf (Out, "\t sub((char *) %s,(char *) %s,(char *) tmp%d);\n", &pd1[adx], bp, iiitmp);
      sprintf (bp, "tmp%d", iiitmp);
      iiitmp++;
      memcheck (iiitmp);
      break;

case PLUS:

//??????
      memcheck (iiitmp);
      if (ConCheck(bp)) fprintf (Out, "\t add( (char *) %s, \"%s\", (char *) tmp%d ); \n", &pd1[adx], bp, iiitmp);
      else fprintf (Out, "\t add((char *) %s, (char *) %s, (char *) tmp%d); \n", &pd1[adx], bp, iiitmp);
      sprintf (bp, "tmp%d", iiitmp);
      iiitmp++;
      memcheck (iiitmp);
      break;

case CONCAT:

      memcheck (iiitmp);
      fprintf(Out, "\t if (strlen((const char *) %s)+strlen((const char *) %s)+1>STR_MAX) ",&pd1[adx],bp);
      fprintf (Out, "ErrorMessage(\"String too long\",svPtr->LineNumber);\n");
      fprintf (Out, "\t strmove((unsigned char *) tmp%d,(unsigned char *) %s);\n", iiitmp, &pd1[adx]);
      fprintf (Out, "\t strcat((char *) tmp%d,(char *) %s);\n", iiitmp, bp);
      sprintf (bp, "tmp%d", iiitmp);
      iiitmp++;
      memcheck (iiitmp);
      break;

case EQUALS:
case NOTEQ:

      if (s1p[spx] != NOTEQ) { //* EQUALS 
            memcheck (iiitmp);
            fprintf (Out,
                  "\t if (strcmp((const char *) %s,(const char *) %s)==0) strmove((unsigned char *) tmp%d,(unsigned char *) \"1\");\n"
                  "\t    else strmove((unsigned char *) tmp%d,(unsigned char *) \"0\");\n",
                  &pd1[adx], bp, iiitmp, iiitmp);
            sprintf (bp, "tmp%d", iiitmp);
            iiitmp++;
            memcheck (iiitmp);
            break;
            }

      memcheck (iiitmp);
      fprintf (Out, //* NOTEQ 
            "\t if (strcmp((const char *) %s,(const char *) %s)!=0)\n\t\t strmove((unsigned char *) tmp%d,(unsigned char *) \"1\");\n"
            "\t    else strmove((unsigned char *) tmp%d,(unsigned char *) \"0\");\n",
            &pd1[adx], bp, iiitmp, iiitmp);

      sprintf (bp, "tmp%d", iiitmp);
      iiitmp++;
      memcheck (iiitmp);
      break;

case GREATER:

      memcheck (iiitmp);
      if (ConCheck(bp)) 
            fprintf (Out,
	       "\t if (numcomp1((unsigned char *) %s,%s)>0) strmove((unsigned char *) tmp%d,(unsigned char *) \"1\");\n"
	       "\t    else strmove((unsigned char *) tmp%d,(unsigned char *) \"0\");\n", &pd1[adx], bp, iiitmp, iiitmp);
            else fprintf (Out,
	       "\t if (numcomp((unsigned char *) %s,(unsigned char *) %s)>0) strmove((unsigned char *) tmp%d,(unsigned char *) \"1\");\n"
	       "\t    else strmove((unsigned char *) tmp%d,(unsigned char *) \"0\");\n", &pd1[adx], bp, iiitmp, iiitmp);
      sprintf (bp, "tmp%d", iiitmp);
      iiitmp++;
      memcheck (iiitmp);
      break;

case LESSTHAN:

      memcheck (iiitmp);
      if (ConCheck(bp)) 
            fprintf (Out,
	       "\t if (numcomp1((unsigned char *) %s,%s)<0) strmove((unsigned char *) tmp%d,(unsigned char *) \"1\");\n"
	       "\t     else strmove((unsigned char *) tmp%d,(unsigned char *) \"0\");\n", &pd1[adx], bp, iiitmp, iiitmp);
            else fprintf (Out,
	       "\t if (numcomp((unsigned char *) %s,(unsigned char *) %s)<0) strmove((unsigned char *) tmp%d,(unsigned char *) \"1\");\n"
	       "\t     else strmove((unsigned char *) tmp%d,(unsigned char *) \"0\");\n", &pd1[adx], bp, iiitmp, iiitmp);
      sprintf (bp, "tmp%d", iiitmp);
      iiitmp++;
      memcheck (iiitmp);
      break;

case INTDIVIDE:

      memcheck (iiitmp);
      fprintf (Out, "\t divi((const char *) %s,(const char *) %s,(char *) tmp%d);\n", &pd1[adx], bp, iiitmp);
      sprintf (bp, "tmp%d", iiitmp);
      iiitmp++;
      memcheck (iiitmp);
      break;

case MODULO:

      memcheck (iiitmp);
      fprintf (Out, "\t _i=atoi((char *) %s);\n", bp);
      fprintf (Out, "\t _j=atoi((char *) %s);\n", &pd1[adx]);
      fprintf (Out, "\t _i=_j%%_i;\n");
//      fprintf (Out, "\t Mltoa(i,tmp%d,10);\n", iiitmp);
      fprintf (Out, "\t Mltoa(_i,tmp%d);\n", iiitmp);
      sprintf (bp, "tmp%d", iiitmp);
      iiitmp++;
      memcheck (iiitmp);
      break;

case CONTAINS:

      memcheck (iiitmp);
      fprintf (Out,
	       "\t if (strstr((const char *)%s,(const char *)%s)) strmove((unsigned char *) tmp%d,(unsigned char *) \"1\");"
	       " else strmove((unsigned char *) tmp%d,(unsigned char *) \"0\");\n", &pd1[adx], bp, iiitmp, iiitmp);
      sprintf (bp, "tmp%d", iiitmp);
      iiitmp++;
      memcheck (iiitmp);
      break;

case FOLLOWS:

      memcheck (iiitmp);
      fprintf (Out,
	       "\t if (strcmp((const char *) %s,(const char *) %s)>0) strmove((unsigned char *) tmp%d,(unsigned char *) \"1\");"
	       " else strmove((unsigned char *) tmp%d,(unsigned char *) \"0\");\n", &pd1[adx], bp, iiitmp, iiitmp);
      sprintf (bp, "tmp%d", iiitmp);
      iiitmp++;
      memcheck (iiitmp);
      break;

case PATTERN:

      fixstr (&bd[1]);
      memcheck (iiitmp);
      fprintf (Out,
	       "\t if (pm((const unsigned char *) %s,(const unsigned char *) \"%s\",svPtr)) strmove((unsigned char *) tmp%d,(unsigned char *) \"1\");"
	       " else strmove((unsigned char *) tmp%d,(unsigned char *) \"0\");\n",
	       &pd1[adx], &bd[1], iiitmp, iiitmp);
      sprintf (&bd[1], "tmp%d", iiitmp);
      iiitmp++;
      memcheck (iiitmp);
      break;

case NOTGREATER:

      memcheck (iiitmp);
      fprintf (Out,
	       "\t if (numcomp((unsigned char *) %s,(unsigned char *) %s)<=0) strmove((unsigned char *) tmp%d,(unsigned char *) \"1\");\n"
	       "\t     else strmove((unsigned char *) tmp%d,(unsigned char *) \"0\");\n", &pd1[adx], bp, iiitmp, iiitmp);
      sprintf (bp, "tmp%d", iiitmp);
      iiitmp++;
      memcheck (iiitmp);
      break;

case NOTLESS:

      memcheck (iiitmp);
      fprintf (Out,
	       "\t if (numcomp((unsigned char *) %s,(unsigned char *) %s)>=0) strmove((unsigned char *) tmp%d,(unsigned char *) \"1\");\n"
	       "      else strmove((unsigned char *) tmp%d,(unsigned char *) \"0\");\n", &pd1[adx], bp, iiitmp, iiitmp);
      sprintf (bp, "tmp%d", iiitmp);
      iiitmp++;
      memcheck (iiitmp);
      break;

case NOTCONTAINS:

      memcheck (iiitmp);
      fprintf (Out,
	       "\t if (!strstr((const char *)%s,(const char *)%s)) strmove((unsigned char *) tmp%d,(unsigned char *) \"1\");"
	       " else strmove((unsigned char *) tmp%d,(unsigned char *) \"0\");\n", &pd1[adx], bp, iiitmp, iiitmp);
      sprintf (bp, "tmp%d", iiitmp);
      iiitmp++;
      memcheck (iiitmp);
      break;

case NOTFOLLOWS:

      memcheck (iiitmp);
      fprintf (Out,
	       "\t if (strcmp((const char *) %s,(const char *) %s)<=0) strmove((unsigned char *) tmp%d,(unsigned char *) \"1\");"
	       " else strmove((unsigned char *) tmp%d,(unsigned char *) \"0\");\n", &pd1[adx], bp, iiitmp, iiitmp);
      sprintf (bp, "tmp%d", iiitmp);
      iiitmp++;
      memcheck (iiitmp);
      break;

case NOTPATTERN:

      memcheck (iiitmp);
      fixstr (&bd[1]);
      fprintf (Out,
	       "\t if (pm((const unsigned char *) %s,(const unsigned char *) \"%s\",svPtr)) strmove((unsigned char *) tmp%d,(unsigned char *) \"0\");"
	       " else strmove((unsigned char *) tmp%d,(unsigned char *) \"1\");\n",
	       &pd1[adx], &bd[0], iiitmp, iiitmp);
      sprintf (&bd[1], "tmp%d", iiitmp);
      iiitmp++;
      memcheck (iiitmp);
      break;


case AND:

      memcheck (iiitmp);
      fprintf (Out,
	       "\t if (numcomp((unsigned char *) %s,(unsigned char *) \"0\")&&numcomp((unsigned char *) %s,(unsigned char *) \"0\"))"
	       " strmove((unsigned char *) tmp%d,(unsigned char *) \"1\"); else strmove((unsigned char *) tmp%d,(unsigned char *) \"0\");\n",
	       &pd1[adx], bp, iiitmp, iiitmp);
      sprintf (bp, "tmp%d", iiitmp);
      iiitmp++;
      memcheck (iiitmp);
      break;

case OR:

      memcheck (iiitmp);
      fprintf (Out,
	       "\t if (numcomp1((unsigned char *) %s,0)||numcomp1((unsigned char *) %s,0))"
	       " strmove((unsigned char *) tmp%d,(unsigned char *) \"1\"); else strmove((unsigned char *) tmp%d,(unsigned char *) \"0\");\n",
	       &pd1[adx], bp, iiitmp, iiitmp);
      sprintf (bp, "tmp%d", iiitmp);
      iiitmp++;
      memcheck (iiitmp);
      break;

case NOTAND:

      memcheck (iiitmp);
      fprintf (Out,
	       "\t if (numcomp1((unsigned char *) %s,0)&&numcomp1((unsigned char *) %s,0))"
	       " strmove((unsigned char *) tmp%d,(unsigned char *) \"0\"); else strmove((unsigned char *) tmp%d,(unsigned char *) \"1\");\n",
	       &pd1[adx], bp, iiitmp, iiitmp);
      sprintf (bp, "tmp%d", iiitmp);
      iiitmp++;
      memcheck (iiitmp);
      break;

case NOTOR:

      memcheck (iiitmp);
      fprintf (Out,
	       "\t if (numcomp1((unsigned char *) %s,0)||numcomp1((unsigned char *) %s,0))"
	       " strmove((unsigned char *) tmp%d,(unsigned char *) \"0\"); else strmove((unsigned char *) tmp%d,(unsigned char *) \"1\");\n",
	       &pd1[adx], bp, iiitmp, iiitmp);
      sprintf (bp, "tmp%d", iiitmp);
      iiitmp++;
      memcheck (iiitmp);
      break;

    } //* switch 

dec_stk:

  spx -= 2;

nxt_operator:

  if (s1p[spx] != OPEN && 
      s1p[spx] != OPENC && 
      s1p[spx] != EMPTY) goto nxt_expr;

//*===============================================================
//*       push answer                                             
//*===============================================================

  spx++;
  sdlim += strlen (&pd1[sdlim]) + 1;
  if (sdlim >= symlen) return (31);
  strcpy (&pd1[sdlim], bp);
  s1p[spx] = OPERAND;
  goto nchar;

//*===============================================================
//*       exit sequence                                          
//*===============================================================

finish:

  if (s1p[spx - 1] != EMPTY || s1p[spx] != OPERAND) return (16);
  else return (0);
}


//*===============================================================
//*===============================================================
//*===============================================================


void fixstr (unsigned char a[]) {

  char tmp[1024];
  int i, j;

  for (i = 0, j = 0; a[i] != 0; i++) {

      if (a[i] == '\"') {
            tmp[j++] = '\\';
            tmp[j++] = '\"';
            continue;
            }

      if (a[i] == '\'') {
            tmp[j++] = '\\';
            tmp[j++] = '\'';
            continue;
            }

      if (a[i] == '\\') {
            tmp[j++] = '\\';
            tmp[j++] = '\\';
            continue;
            }

      tmp[j++] = a[i];
    }

  tmp[j] = 0;
  strcpy (a, tmp);
  return;
}

#if SYSTEM==DOS

int strcasecmp (char *a, char *b) {

  while (toupper (*a) == toupper (*b) && *a != 0) {
      a++;
      b++;
      }

  if (*a == 0) return 0;
  else return 1;

}

int strncasecmp (char *a, char *b, int i) {

  while (toupper (*a) == toupper (*b) && *a != 0 && i > 0) {
      i--;
      a++;
      b++;
      }

  if (i == 0 || *a == 0) return 0;
  else return 1;

}

#endif

void memcheck (int iiitmp) {

  if (iiitmp > MaxTmp) MaxTmp=iiitmp;

}

int cvar(char * str) {
      int i;
      for (i=0; i<cvarx; i++) 
            if (strcmp(str,cvars[i].name)==0) return 1;
      return 0;
      }

char * Extract2 (char * str) {
      int i,j;
      static char tmp1[64],tmp2[64];
      if (str[0]!='#') return str;
      for (i=3; str[i]!='#' && str[i]!='\0'; i++);
      memcpy(tmp1,&str[3],i-3);
      tmp1[i-3]='\0';
      for (j=++i; str[i]!='#' && str[i]!='\0'; i++);
      memcpy(tmp2,&str[j],i-j);
      tmp2[i-j]='\0';
      if (strncmp(str,"#S#",3)==0) {
            fprintf( Out, 
		"\t if (sym_(SYMGET,(unsigned char *) %s,(unsigned char *) %s,"
		"svPtr)==NULL) \n\t\tVariableNotFound1(svPtr->LineNumber,(unsigned char *) %s);\n", 
                  tmp1,tmp2,tmp1); 
		}
      else if (strncmp(str,"#G#",3)==0)
            fprintf(Out,
                  "\t if (!Mglobal(RETRIEVE,%s,%s,svPtr)) VariableNotFound(svPtr->LineNumber);\n", 
                  tmp1,tmp2,tmp2);
      return tmp2;
      }

char * Extract1 (char * str) {
      int i,j;
      static char tmp1[64],tmp2[64];
      if (str[0]!='#') return str;
      for (i=3; str[i]!='#' && str[i]!='\0'; i++);
      memcpy(tmp1,&str[3],i-3);
      tmp1[i-3]='\0';
      return tmp1;
      }

char * Extract2a (char * str) {
      int i,j;
      static char tmp1[64],tmp2[64];

      if (str[0]!='#') return str;
      for (i=3; str[i]!='#' && str[i]!='\0'; i++);
      memcpy(tmp1,&str[3],i-3);
      tmp1[i-3]='\0';
      for (j=++i; str[i]!='#' && str[i]!='\0'; i++);
      memcpy(tmp2,&str[j],i-j);
      tmp2[i-j]='\0';
      if (strncmp(str,"#S#",3)==0)
            fprintf( Out, 
		"\t sym_(1,(unsigned char *) %s,(unsigned char *) %s,"
		"svPtr)?%s:VariableNotFound1(svPtr->LineNumber,(unsigned char *)%s); //E21000\n", 
                 tmp1,tmp2,tmp2,tmp1);
      else if (strncmp(str,"#G#",3)==0)
            fprintf(Out,
                  "\t Mglobal(RETRIEVE,%s,%s,svPtr)?%s:VariableNotFound(svPtr->LineNumber);\n", 
                  tmp1,tmp2,tmp2);
      return tmp2;
      }

void ExpandQS(unsigned char * v1d, int i, unsigned char * bp) {
	char arg1[32]="";
	char arg2[32]="";
	char arg3[32]="";
	int j;

	i++;
	if (strncmp(&v1d[i],"#G#",3)==0) {
      		i=i+3;
      		for (j=0; v1d[i]!='#'; j++) arg1[j]=v1d[i++]; 
      		i++;
      		for (j=0; v1d[i]!='#'; j++) arg2[j]=v1d[i++]; 
      		i=i+1;
      		if (v1d[i]==CodedComma) {
            		i++;
            		if (strncmp(&v1d[i],"#G#",3)==0  ||
                		strncmp(&v1d[i],"#S#",3)==0) { 
                  		strcpy(arg3,Extract2(&v1d[i])); 
                  		}
            	else for (j=0; v1d[i]<128&&v1d[i]!='\0'; j++) arg3[j]=v1d[i++]; 
            	}
      	else strcpy(arg3,"NULL");
                        
      fprintf(Out,"\t GlobalQS((unsigned char *) %s,(unsigned char *) %s,(unsigned char *) %s,svPtr);\n",arg1,arg2,arg3);
      strcpy (bp, arg2);
      return;
      }

if (strncmp(&v1d[i],"#S#",3)==0) {
      i=i+3;
      for (j=0; v1d[i]!='#'; j++) arg1[j]=v1d[i++]; 
      i++;
      for (j=0; v1d[i]!='#'; j++) arg2[j]=v1d[i++]; 
      i=i+1;
      if (v1d[i]==CodedComma) {
            i++;
            if (strncmp(&v1d[i],"#S#",3)==0 ||
                strncmp(&v1d[i],"#G#",3)==0) { 
                  strcpy(arg3,Extract2(&v1d[i])); 
                  }
            else for (j=0; v1d[i]<128&&v1d[i]!='\0'; j++) arg3[j]=v1d[i++]; 
            }
      else strcpy(arg3,"NULL");
                        
      fprintf(Out,"\t GlobalQS((unsigned char *) %s,(unsigned char *) %s,(unsigned char *) %s,svPtr);\n",arg1,arg2,arg3);
      strcpy (bp, arg2);
      return;
      }
}

void ExpandOrder(unsigned char * v1d, int i, unsigned char * bp) {
char arg1[32]="";
char arg2[32]="";
char arg3[32]="";
int j;

i++;
if (strncmp(&v1d[i],"#G#",3)==0) {
      i=i+3;
      for (j=0; v1d[i]!='#'; j++) arg1[j]=v1d[i++]; 
      i++;
      for (j=0; v1d[i]!='#'; j++) arg2[j]=v1d[i++]; 
      i=i+1;
      if (v1d[i]==CodedComma) {
            i++;
            if (strncmp(&v1d[i],"#G#",3)==0  ||
                strncmp(&v1d[i],"#S#",3)==0) { 
                  strcpy(arg3,Extract2(&v1d[i])); 
                  }
            else for (j=0; v1d[i]<128&&v1d[i]!='\0'; j++) arg3[j]=v1d[i++]; 
            }
      else strcpy(arg3,"NULL");
                        
      fprintf(Out,"\t GlobalOrder((unsigned char *) %s,(unsigned char *) %s,(unsigned char *) %s,svPtr);\n",arg1,arg2,arg3);
      strcpy (bp, arg2);
      return;
      }

if (strncmp(&v1d[i],"#S#",3)==0) {
      i=i+3;
      for (j=0; v1d[i]!='#'; j++) arg1[j]=v1d[i++]; 
      i++;
      for (j=0; v1d[i]!='#'; j++) arg2[j]=v1d[i++]; 
      i=i+1;
      if (v1d[i]==CodedComma) {
            i++;
            if (strncmp(&v1d[i],"#S#",3)==0 ||
                strncmp(&v1d[i],"#G#",3)==0) { 
                  strcpy(arg3,Extract2(&v1d[i])); 
                  }
            else for (j=0; v1d[i]<128&&v1d[i]!='\0'; j++) arg3[j]=v1d[i++]; 
            }
      else strcpy(arg3,"NULL");
                        
      fprintf(Out,"\t LocalOrder((unsigned char *) %s,(unsigned char *) %s,(unsigned char *) %s,svPtr);\n",arg1,arg2,arg3);
      strcpy (bp, arg2);
      return;
      }
}

void ExpandData(unsigned char * v1d, int i, unsigned char * bp) {
char arg1[32]="";
char arg2[32]="";
int j;

i++;
if (strncmp(&v1d[i],"#G#",3)==0) {
      i=i+3;
      for (j=0; v1d[i]!='#'; j++) arg1[j]=v1d[i++]; 
      i++;
      for (j=0; v1d[i]!='#'; j++) arg2[j]=v1d[i++]; 
      fprintf(Out,"\t GlobalData(%s,%s,svPtr);\n",arg1,arg2);
      strcpy (bp, arg2);
      return;
      }

if (strncmp(&v1d[i],"#S#",3)==0) {
      i=i+3;
      for (j=0; v1d[i]!='#'; j++) arg1[j]=v1d[i++]; 
      i++;
      for (j=0; v1d[i]!='#'; j++) arg2[j]=v1d[i++]; 
      fprintf(Out,"\t LocalData((unsigned char *) %s,(unsigned char *) %s,svPtr);\n",arg1,arg2);
      strcpy (bp, arg2);
      return;
      }
}

//void ExpandQlength(unsigned char * v1d, int i, unsigned char * bp) {
//char arg1[32]="";
//char arg2[32]="";
//int j;
//
//i++;
//if (strncmp(&v1d[i],"#G#",3)==0) {
//      i=i+3;
//      for (j=0; v1d[i]!='#'; j++) arg1[j]=v1d[i++]; 
//      i++;
//      for (j=0; v1d[i]!='#'; j++) arg2[j]=v1d[i++]; 
//      fprintf(Out,"\t Qlength(%s,%s,svPtr);\n",Extract2(arg1),arg2);
//      strcpy (bp, arg2);
//      return;
//      }
//
//if (strncmp(&v1d[i],"#S#",3)==0) {
//      i=i+3;
//      for (j=0; v1d[i]!='#'; j++) arg1[j]=v1d[i++]; 
//      i++;
//      for (j=0; v1d[i]!='#'; j++) arg2[j]=v1d[i++]; 
//      fprintf(Out,"\t Qlength(%s,%s,svPtr);\n",Extract2(arg1),arg2);
//      strcpy (bp, arg2);
//      return;
//      }
//}

void ExpandNext(unsigned char * v1d, int i, unsigned char * bp) {
char arg1[32]="";
char arg2[32]="";
int j;

i++;
if (strncmp(&v1d[i],"#G#",3)==0) {
      i=i+3;
      for (j=0; v1d[i]!='#'; j++) arg1[j]=v1d[i++]; 
      i++;
      for (j=0; v1d[i]!='#'; j++) arg2[j]=v1d[i++]; 
//      fprintf(Out,"\t GlobalNext(%s,%s,svPtr);\n",arg1,arg2);
      fprintf(Out,"\t GlobalOrder(%s,%s,(unsigned char *) \"1\", svPtr);\n",arg1,arg2);
 	fprintf(Out,"\t if (strlen((char *)%s)==0) strcpy((char *)%s,\"-1\");\n",arg2,arg2);
      strcpy (bp, arg2);
      return;
      }

if (strncmp(&v1d[i],"#S#",3)==0) {
      i=i+3;
      for (j=0; v1d[i]!='#'; j++) arg1[j]=v1d[i++]; 
      i++;
      for (j=0; v1d[i]!='#'; j++) arg2[j]=v1d[i++]; 
      fprintf(Out,"\t LocalNext((unsigned char *) %s,(unsigned char *) %s,svPtr);\n",arg1,arg2);
      strcpy (bp, arg2);
      return;
      }
}

void ExpandGet(unsigned char * v1d, int i, unsigned char * bp) {
char arg1[32]="";
char arg2[32]="";
char arg3[32]="";
int j;

i++;
if (strncmp(&v1d[i],"#G#",3)==0) {
      i=i+3;
      for (j=0; v1d[i]!='#'; j++) arg1[j]=v1d[i++]; 
      i++;
      for (j=0; v1d[i]!='#'; j++) arg2[j]=v1d[i++]; 
      i=i+1;
      if (v1d[i]==CodedComma) {
            i++;
            if (strncmp(&v1d[i],"#G#",3)==0  ||
                strncmp(&v1d[i],"#S#",3)==0) { 
                  strcpy(arg3,Extract2(&v1d[i])); 
                  }
            else for (j=0; v1d[i]<128&&v1d[i]!='\0'; j++) arg3[j]=v1d[i++]; 
            }
      else strcpy(arg3,"NULL");
                        
      fprintf(Out,"\t GlobalGet((unsigned char *) %s,(unsigned char *) %s,(unsigned char *) %s,svPtr);\n",arg1,arg2,arg3);
      strcpy (bp, arg2);
      return;
      }

if (strncmp(&v1d[i],"#S#",3)==0) {
      i=i+3;
      for (j=0; v1d[i]!='#'; j++) arg1[j]=v1d[i++]; 
      i++;
      for (j=0; v1d[i]!='#'; j++) arg2[j]=v1d[i++]; 
      i=i+1;
      if (v1d[i]==CodedComma) {
            i++;
            if (strncmp(&v1d[i],"#S#",3)==0 ||
                strncmp(&v1d[i],"#S#",3)==0) { 
                  strcpy(arg3,Extract2(&v1d[i])); 
                  }
            else for (j=0; v1d[i]<128&&v1d[i]!='\0'; j++) arg3[j]=v1d[i++]; 
            }
      else strcpy(arg3,"NULL");
                        
      fprintf(Out,"\t LocalGet((unsigned char *) %s,(unsigned char *) %s,(unsigned char *) %s,svPtr);\n",arg1,arg2,arg3);
      strcpy (bp, arg2);
      return;
      }
}

void ExpandText(unsigned char * v1d, int i, unsigned char * bp) {
// ????
int j;
i++;
for (j=i; v1d[j]!='\0'; j++) if (v1d[j]>128||v1d[j]==1) {v1d[j]='\0'; break;}
fprintf (Out, "\t strcpy((char *) &gtmp[1],\"$test\\x%x\"); /* CodedOpen */\n",CodedOpen);
fprintf (Out, "\t strcat((char *) &gtmp[1],(const char *) %s);\n", Extract2a(&v1d[i]));
fprintf (Out, "\t strcat((char *) &gtmp[1],\"\\x%x\"); /* CodedClose */\n", CodedClose);
fprintf (Out, "\t strmove((unsigned char *) &svPtr->v1d[1],(unsigned char *)  &gtmp[1]);\n");
memcheck (iiitmp);
fprintf (Out, "\t fcn(svPtr);\n");
fprintf (Out, "\t strmove((unsigned char *) tmp%d,(unsigned char *) &svPtr->bd[1]);\n",iiitmp);
sprintf (bp, "tmp%d", iiitmp);
iiitmp++;
memcheck (iiitmp);
return;
}

void ExpandName(unsigned char * v1d, int i, unsigned char * bp) {
char arg1[32]="";
char arg2[32]="";
char arg3[32]="";
int j;

i++;
if (strncmp(&v1d[i],"#G#",3)==0) {
      i=i+3;
      for (j=0; v1d[i]!='#'; j++) arg1[j]=v1d[i++]; 
      i++;
      for (j=0; v1d[i]!='#'; j++) arg2[j]=v1d[i++]; 
      i=i+1;
      if (v1d[i]==CodedComma) {
            i++;
            if (strncmp(&v1d[i],"#G#",3)==0  ||
                strncmp(&v1d[i],"#S#",3)==0) { 
                  strcpy(arg3,Extract2(&v1d[i])); 
                  }
            else for (j=0; v1d[i]<128&&v1d[i]!='\0'; j++) arg3[j]=v1d[i++]; 
            }
      else strcpy(arg3,"NULL");
                        
      fprintf(Out,"\t GlobalName(%s,%s,%s,svPtr);\n",arg1,arg2,arg3);
      strcpy (bp, arg2);
      return;
      }

if (strncmp(&v1d[i],"#S#",3)==0) {
      i=i+3;
      for (j=0; v1d[i]!='#'; j++) arg1[j]=v1d[i++]; 
      i++;
      for (j=0; v1d[i]!='#'; j++) arg2[j]=v1d[i++]; 
      i=i+1;
      if (v1d[i]==CodedComma) {
            i++;
            if (strncmp(&v1d[i],"#S#",3)==0 ||
                strncmp(&v1d[i],"#S#",3)==0) { 
                  strcpy(arg3,Extract2(&v1d[i])); 
                  }
            else for (j=0; v1d[i]<128&&v1d[i]!='\0'; j++) arg3[j]=v1d[i++]; 
            }
      else strcpy(arg3,"NULL");
                        
      fprintf(Out,"\t LocalName((unsigned char *) %s,(unsigned char *) %s,(unsigned char *) %s,svPtr);\n",arg1,arg2,arg3);
      strcpy (bp, arg2);
      return;
      }
}

// void ExpandQsub(unsigned char * v1d, int i, unsigned char * bp) {
// char arg1[32]="";
// char arg2[32]="";
// char arg3[32]="";
// int j;

// i++;
// if (strncmp(&v1d[i],"#G#",3)==0) {
//       i=i+3;
//       for (j=0; v1d[i]!='#'; j++) arg1[j]=v1d[i++]; 
//       i++;
//       for (j=0; v1d[i]!='#'; j++) arg2[j]=v1d[i++]; 
//       i=i+1;
//       if (v1d[i]==CodedComma) {
//             i++;
//             if (strncmp(&v1d[i],"#G#",3)==0  ||
//                strncmp(&v1d[i],"#S#",3)==0) { 
//                   strcpy(arg3,Extract2(&v1d[i])); 
//                   }
//             else for (j=0; v1d[i]<128&&v1d[i]!='\0'; j++) arg3[j]=v1d[i++]; 
//             }
//       else strcpy(arg3,"NULL");
//                         
//       fprintf(Out,"\t Qsub(%s,%s,%s,svPtr);\n",arg1,arg2,arg3);
//       strcpy (bp, arg2);
//       return;
//       }
// 
// if (strncmp(&v1d[i],"#S#",3)==0) {
//       i=i+3;
//       for (j=0; v1d[i]!='#'; j++) arg1[j]=v1d[i++]; 
//       i++;
//       for (j=0; v1d[i]!='#'; j++) arg2[j]=v1d[i++]; 
//       i=i+1;
//       if (v1d[i]==CodedComma) {
//             i++;
//             if (strncmp(&v1d[i],"#S#",3)==0 ||
//                 strncmp(&v1d[i],"#S#",3)==0) { 
//                   strcpy(arg3,Extract2(&v1d[i])); 
//                   }
//             else for (j=0; v1d[i]<128&&v1d[i]!='\0'; j++) arg3[j]=v1d[i++]; 
//             }
//       else strcpy(arg3,"NULL");
//                         
//       fprintf(Out,"\t Qsub(%s,%s,%s,svPtr);\n",arg1,arg2,arg3);
//       strcpy (bp, arg2);
//       return;
//       }
// }

int Extract(unsigned char * v1d, unsigned char * bp) {

	  int i, j, r, a;
	  char tmp[1024];

	  for (i = 1; v1d[i] >= 32 && v1d[i] <= 127; i++);	//* fcn nme 

//	  strcpy (v1d, &v1d[i + 1]);	                        //* remove function name 
	for (SSS=v1d,TTT=&v1d[i+1]; *TTT != 0; SSS++,TTT++) *SSS = *TTT;
        *SSS=0;
	  i = 0;
	  a = 0;
	  strcpy (tmp, "");

	  while (1) {
	      j = i;
	      for (; v1d[i] >= 32 && v1d[i] <= 127; i++);

	      if (v1d[i] == 0) {
		  if (a == 0 || a > 3) return a;
		  if (a == 1) strcat (tmp, ", (unsigned char *) \"-1\",(unsigned char *) \"-1\"");
		  else if (a == 2) strcat (tmp, ",(unsigned char *) \"-1\"");
		  memcheck (iiitmp);
		  fprintf (Out, "\t _extract(" "(unsigned char *) tmp%d,(unsigned char *) %s);\n", iiitmp, tmp);
		  sprintf (bp, "tmp%d", iiitmp);
		  iiitmp++;
              memcheck (iiitmp);
              return 0;
		  }

	      v1d[i++] = 0;
	      if (a++)
		strcat (tmp, ",(unsigned char *) ");
	      strcat (tmp, Extract2(&v1d[j]));
            }
      }

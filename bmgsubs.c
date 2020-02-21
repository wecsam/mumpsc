/*==========================================================================================
      The following was obtained from:

      ftp://ftp.uu.net/usenet/comp.sources.unix/volume5/bmgsubs.Z

      and is believed to be contributed source to Unix and is unrestricted
      with respect to use and redistribution.  Its is further believed that 
      the code was written by employee(s) of the United States and is thus in 
      the public domain.

      See also: README.bmg and bmgsubs.3l (man page)
==========================================================================================*/

/*
 * bmgsubs.c
 *
 * Subroutines for fast string searching; no regular expressions
 *
 * Entries:
 *
 * bmg_setup(pattern_string, case_fold_flag)
 * char *pattern_string;	-- the string you are searching for
 * int case_fold_flag;		-- true if you want search to ignore case
 *
 * bmg_fsearch(file_des, action_func)
 * int file_des;		-- file descriptor to read on
 * int (*action_func)();	-- called on each hit
 *
 * bmg_search(buffer, buflen, action_func)
 * char *buffer;		-- buffer to search
 * int buflen;			-- bytes in buffer
 * int (*action_func)();	-- called on each hit
 *
 * Usage:
 *	Start by calling bmg_setup() to specify a pattern.  Then open
 * the file you want to search and pass the file descriptor (NOT a
 * stdio file pointer) to bmg_fsearch().  For each line that contains
 * the pattern, bmg_fsearch() will call action_func(string, position)
 * with string being a static copy of the matching line and position
 * being the disntance in bytes from the beginning of the search to the
 * matching substring.
 *	action_func() should return a non-zero integer unless the
 * search should be terminated, in which case it should return 0.
 *	bmg_search() works the same as bmg_fsearch(), but searches
 * a buffer rather than a file.
 *
 * Adapted from:
 *
     Boyer/Moore/Gosper-assisted 'egrep' search, with delta0 table as in
     original paper (CACM, October, 1977).  No delta1 or delta2.  According to
     experiment (Horspool, Soft. Prac. Exp., 1982), delta2 is of minimal
     practical value.  However, to improve for worst case input, integrating
     the improved Galil strategies (Apostolico/Giancarlo, Siam. J. Comput.,
     February 1986) deserves consideration.

     James A. Woods					Copyright (c) 1986
     NASA Ames Research Center
 *
 * 29 April 1986	Jeff Mogul	Stanford
 *	Adapted as a set of subroutines for use by a program. No
 *	regular-expression support.
 */

#include <stdio.h>
#include <ctype.h>
#include <sys/types.h>
// #include <malloc.h>
#include <string.h>

#ifdef	BSD
#define	strchr	index
#endif
#ifndef	BUFSIZE
#define BUFSIZE	50000
#endif
#ifndef	PATSIZE
#define PATSIZE 9000
#endif
#define LARGE 	BUFSIZE + PATSIZE
#define NL	'\n'
#define	EOS	'\0'

struct bmg_data {
	int     bmg_delta0[256];		/* ascii only */
	char    bmg_cmap[256];		/* (un)folded characters */
	char    bmg_str[BUFSIZE + 2];
	char    bmg_linetemp[BUFSIZE];
	char	bmg_pattern[PATSIZE];
	int	bmg_patlen;
	int	bmg_nsuccess;
} bmdata;
#define delta0	bmdata.bmg_delta0
#define cmap	bmdata.bmg_cmap
#define str	bmdata.bmg_str
#define linetemp	bmdata.bmg_linetemp
#define	pattern	bmdata.bmg_pattern
#define	patlen	bmdata.bmg_patlen
#define	nsuccess	bmdata.bmg_nsuccess

// char   *strcpy(), *strncpy(), *malloc();

/* modifications by K. O'Kane follow */

void Bcopy(char *, char *, int);
void bmg_setup(char *, int);

int bmg_found=0;
int bmg_act(char * p, int i) { bmg_found=i; return 1; }
int bmg_fullsearch(char *p, char *inp) {
      int len,orgoff,bmx,score=0;
      bmg_setup(p,0);
      bmg_found=0;
      orgoff=0;
      len=strlen(inp);
      while (orgoff<len) {
            bmx=bmg_search(&inp[orgoff],strlen(&inp[orgoff]),bmg_act);
            if (!bmx) break;
            score+=bmx;
            orgoff+=bmg_found;
            }
      return score;
      }

/* end modifications by K. O'Kane follow */


int bmg_search(buffer, buflen, action)
char	*buffer;
int	buflen;
int	(*action)();
{
	register char  *k=0,
	               *strend=0,
	               *s=0;
	register int    j=0;
	char   *t;
	char   *strbegin;
	char   *gotamatch();
	int     byte_offset = 0;
	char	last_byte = buffer[buflen - 1];

	nsuccess = 0;

	/* make sure that buffer ends with NL */
	if (last_byte != NL)
	    buffer[buflen - 1] = NL;

	/*
	 * We must process the buffer in chunks of BUFSIZE to make
	 * "LARGE" hack work right.
	 */
	for (strbegin = buffer;
		strbegin < &buffer[buflen]; strbegin += BUFSIZE) {
	    strend = strbegin + BUFSIZE;

	    if (strend > &buffer[buflen])	/* stay inside buffer */
		strend = &buffer[buflen];
	    
	    /* find end of last full line in this chunk of the buffer */
	    s = strbegin;
	    while ((strend[-1]) != NL && (strend > s))
		strend--;
	    if (strend <= strbegin)	/* line longer than BUFSIZE, punt */
		continue;

	    k = strbegin + patlen - 1;

	    for (;;) {
		/* 
		 for a large class of patterns, upwards of 80% of 
		 match time is spent on the next line.  
		 we beat existing microcode (vax 'matchc') this way.
		 */
		while ((k += delta0[*(unsigned char *) k]) < strend)
			;
		if (k < (strbegin + LARGE))
		    break;
		k -= LARGE;
    
		j = patlen - 1;
		s = k - 1;
		while (cmap[*s--] == pattern[--j]);
		/* 
		 * delta-less shortcut for literati, but 
		 * short shrift for genetic engineers.
		 */
		if (j >= 0)
		    k++;
		else {		/* submatch */
		    t = k;
		    s = k - patlen + 1;
		    do
			;
		    while (*s != NL && --s >= strbegin);
		    k = s + 1;	/* at line start */
    
		    if ((k = gotamatch( k,
					(t - buffer),
					action)) == NULL)
			return -1 ;
		    if (k >= strend)
			break;
		}
	    }
	}
	if (buffer[buflen - 1] != last_byte)
		buffer[buflen - 1] = last_byte;
	return(nsuccess);
}

bmg_fsearch(fd, action)
int	fd;
int	(*action)();
{
	register char  *k,
	               *strend,
	               *s;
	register int    j;
	char   *t;
	char   *gotamatch();
	int     nleftover,
	        count,
		file_offset = 0;

	nleftover  = 0;
	nsuccess = 0;

	while ((count = read(fd, str + nleftover, BUFSIZE - nleftover)) > 0) {
	    count += nleftover;
	    if (count != BUFSIZE && fd != 0) {
		str[count++] = NL;	/* insurance for broken last line */
	    }
	    str[count] = 0;
	    for (j = count - 1; str[j] != NL && j >= 0;)
		j--;
	    if (j < 0) {	/* break up long line */
		str[count] = NL;
		str[++count] = EOS;
		strend = str + count;
		linetemp[0] = EOS;
		nleftover = 0;
	    }
	    else {		/* save partial line */
		strend = str + j;
		nleftover = count - j - 1;
		strncpy(linetemp, str + j + 1, nleftover);
	    }
	    k = str + patlen - 1;

	    for (;;) {
		/* 
		 for a large class of patterns, upwards of 80% of 
		 match time is spent on the next line.  
		 we beat existing microcode (vax 'matchc') this way.
		 */
		while ((k += delta0[*(unsigned char *) k]) < strend)
			;
		if (k < (str + LARGE))
		    break;
		k -= LARGE;

		j = patlen - 1;
		s = k - 1;
		while (cmap[*s--] == pattern[--j]);
		/* 
		 * delta-less shortcut for literati, but 
		 * short shrift for genetic engineers.
		 */
		if (j >= 0)
		    k++;
		else {		/* submatch */
		    t = k;
		    s = k - patlen + 1;
		    do
		        ;
		    while (*s != NL && --s >= str);
		    k = s + 1;	/* at line start */

		    if ((k = gotamatch( k,
		    			(file_offset + (t - str)),
					action)) == NULL)
			return -1;
		    if (k >= strend)
			break;
		}
	    }
	    file_offset += ( 1 + (strend - str));
	    strncpy(str, linetemp, nleftover);
	}
	return(nsuccess);
}

void bmg_setup(pat, folded)		/* compute "boyer-moore" delta table */
char   *pat;		/* ... HAKMEM lives ... */
int	folded;
{
	register int    j=0;

delta0[0]=0; // bmdata.bmg_delta0
cmap[0]=0; // bmdata.bmg_cmap
str[0]=0; // bmdata.bmg_str
linetemp[0]=0; // bmdata.bmg_linetemp
pattern[0]; // bmdata.bmg_pattern
patlen=0; // bmdata.bmg_patlen

	/* 
	 for multibyte characters (e.g. kanji), there are ways.
	 extrapolating 256 to 64K may be unwise, in favor of more
	 dynamics within boyermoore() itself. 
	 */
	patlen = strlen(pat);
	if (folded) {	/* fold case while saving pattern */
	    for (j = 0; j < patlen; j++) {
		pattern[j] = (isupper((int) pat[j]) 
				? (char) tolower((int) pat[j]) : pat[j]);
	    }
	}
	else
	    Bcopy((char *)pat, (char *)pattern, patlen);

	for (j = 0; j < 256; j++) {
	    delta0[j] = patlen;
	    cmap[j] = (char) j;	/* could be done at compile time */
	}
	for (j = 0; j < patlen - 1; j++)
	    delta0[pattern[j]] = patlen - j - 1;
	delta0[pattern[patlen - 1]] = LARGE;

	if (folded) {
	    for (j = 0; j < patlen - 1; j++)
		if (islower((int) pattern[j]))
		    delta0[toupper((int) pattern[j])] = patlen - j - 1;
	    if (islower((int) pattern[patlen - 1]))
		delta0[toupper((int) pattern[patlen - 1])] = LARGE;
	    for (j = 'A'; j <= 'Z'; j++)
		cmap[j] = (char) tolower((int) j);
	}
}

char *gotamatch(s, pos, action)
register char *s;
register int pos;
int (*action)();
{
	static char	result[BUFSIZE];
	register char *r = result;

	nsuccess++;
	do
	    *r++ = *s;
	while (*s++ != NL);
	*r = 0;
	if (action == NULL) {
	    printf("%s", result);
	    return(s);
	}
	else
	    if (action(result, pos))
		return(s);
	    else 
	    	return(NULL);
}

#ifndef	BSD
void Bcopy(from, to, len)
char *from;
char *to;
int len;
{
	while (len-- > 0) {
		*to++ = *from++;
	}
}
#endif

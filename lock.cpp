//#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//#+    Mumps Compiler Run-Time Support Functions
//#+    Copyright (c) 2001, 2002, 2012, 2014 by Kevin C. O'Kane
//#+    kc.okane@gmail.com
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

//* lock.c - Mumps file lock library

// name of file that contains the current locks
// when a process terminates, any locks it has
// should be erased from here.

#define LOCKFILE "/tmp/Mumps.Locks"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifndef _MSC_VER
#include <unistd.h>
#else
#include <io.h>
#endif

#include <mumpsc/defines.h>
#include <mumpsc/fcns.h>
#include <mumpsc/global.h>

char * makeLock(char *, char *, char *, char, char *); /* global array lock service */
char * cleanLocks(char *); /* global array lock service */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* This does not work with NFS files !!!! (NFS problem, not mine) */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

//*********************************************************************************************
//*********************************************************************************************
//*********************************************************************************************

char *cleanLocks(char * pid) { /* remove locks fro this process */

int i,j,k;

// structure of a lock record

struct rec {
      char pid [16];  // locking process id
      char ref [512]; // global array node reference locked
      } buf;

i=open(LOCKFILE, O_EXCL | O_RDWR);

if (i<0) i=open(LOCKFILE, O_CREAT | O_EXCL | O_RDWR, 0666);

if (i<0) return (char *) "0";

// find any locks for this pid and delete them

while (read(i,&buf,(size_t)sizeof(struct rec))!=0) {
      if (strcmp(buf.pid,pid)==0) {
            lseek(i,-(off_t)sizeof(struct rec),SEEK_CUR);
            for (j=0; j<15; j++) buf.pid[j]=' ';
            buf.pid[j]='\0';
            for (j=0; j<511; j++) buf.ref[j]=' ';
            buf.ref[j]='\0';
            write(i,&buf,(size_t)sizeof(struct rec));
            }
      }

chmod(LOCKFILE,0666);
close(i);
return (char *) "1";
}

//*********************************************************************************************
//*********************************************************************************************
//*********************************************************************************************

char *makeLock(char *ref, char *code, char *pid, char Lf, char * timeout) { /*create a lock */

int i,j,k;

struct rec {
      char pid [16];
      char ref [512];
      } buf = {"               ", "               "};

i=open(LOCKFILE, O_EXCL | O_RDWR);

if (i<0) i=open(LOCKFILE, O_CREAT | O_EXCL | O_RDWR, 0666);

if (i<0) return (char *) "0";

while (read(i,&buf,(size_t)sizeof(struct rec))!=0) {
      if (strcmp(buf.ref,ref)==0 ||
          strncmp(buf.ref,ref,strlen(buf.ref)-1)==0 ||
          strncmp(buf.ref,ref,strlen(ref)-1)==0 ) {
            if (Lf=='-') {
                  FILE *xxx;
                  long L;
                  if (strcmp(buf.pid,pid)!=0) {
			chmod(LOCKFILE,0666);
                        close(i);
                        return (char *) "0";
                        }
                  xxx=fdopen(i,"w+");
                  L=ftell(xxx);
                  L=L-sizeof(struct rec);
                  lseek(i,(off_t)L,SEEK_SET);
                  buf.ref[0]=' ';
                  buf.pid[0]=' ';
                  write(i,&buf,(size_t)sizeof(struct rec)); /* lock */
                  chmod(LOCKFILE,0666);
                  close(i);
                  return (char *) "1";
                  }
                  
            chmod(LOCKFILE,0666);
            close(i);
            return (char *) "0";  /* lock fails */
            }
      }

lseek(i,(off_t)0,SEEK_SET); /* rewind */
while (read(i,&buf,(size_t)sizeof(struct rec))!=0) 
      if (strncmp(buf.ref,"     ",5)==0) {
            lseek(i,-(off_t)sizeof(struct rec),SEEK_CUR);
            break;
            }

for (j=0; j<15; j++) buf.pid[j]=' ';
buf.pid[j]='\0';
for (j=0; j<511; j++) buf.ref[j]=' ';
buf.ref[j]='\0';
strcpy(buf.pid,pid);
strcpy(buf.ref,ref);
write(i,&buf,(size_t)sizeof(struct rec)); /* add lock */
chmod(LOCKFILE,0666);
close(i);
return (char *) "1";
}

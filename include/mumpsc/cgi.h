//#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//#+    Mumps Compiler Run-Time Support Functions
//#+    Copyright (c) 2001 by Kevin C. O'Kane
//#+    okane@cs.uni.edu
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
/*--------------------------------------------
	decode arguments passed to processor
	from command line or environment
----------------------------------------------*/

#define QS_MAX 2048
#define QS_MAX1 2047
/*-------------
#if SYSTEM==OS2
        _envargs(&argc,&argv,"QUERY_STRING");
#endif 
---------------*/

/****************************************************************************
*******
******* install default program to execute init.mps or decode shell variable
*******
****************************************************************************/

{

char _ftmp[STR_MAX];

if (getenv("REMOTE_ADDR")!=NULL)  {
		  char t[QS_MAX];
		  strncpy(t,(const char *)getenv("REMOTE_ADDR"),QS_MAX1);
        	  sym_((int)0,(unsigned char *)"%RA",(unsigned char *)t,svPtr); /* store */
            }

if (getenv("REMOTE_HOST")!=NULL)  {
		  char t[QS_MAX];
		  strncpy(t,(const char *)getenv("REMOTE_HOST"),QS_MAX1);
        	  sym_((int)0,(unsigned char *)"%RH",(unsigned char *)t,svPtr); /* store */
            }

if (getenv("QUERY_STRING")!=NULL)  {

		  char t[QS_MAX],t1[1024];
		  int i,j,k,m,n,p,dup=0;

		  strncpy(t,(const char *)getenv("QUERY_STRING"),QS_MAX1);

            for (i=0; t[i]!='&' && t[i]!=0 && i<QS_MAX; i++); /* find end */
            if (i==QS_MAX) t[0]='\0';
            sym_((int)0,(unsigned char *)"%QS",(unsigned char *)t,svPtr); /* store */
            if (t[0]=='\0') goto cgi_exit;

	/***************************
	convert plus signs to blanks
	***************************/

		  for (i=0; t[i]!=0 && i<QS_MAX; i++) if (t[i]=='+') t[i]=' ';

nxtarg: for (i=0; t[i]!='&' && t[i]!=0 && i<QS_MAX; i++); /* find end */

        if (t[i]==0) k=0; 
		  else k=1;

		  t[i]=0;
		  for (j=0; t[j]!='=' && j<QS_MAX; j++);
              if (j==QS_MAX)  goto cgi_exit;
		  t[j]=0;

	/***************************
	copy right hand side to _ftmp
	***************************/

		  for (n=0,m=j+1; t[m]!=0; m++) {

			if (t[m]!='%') {
				_ftmp[n]=t[m];
				n++;
				continue;
				}

		/**************
		first hex digit
		**************/

		if (t[m+1]>='a'&&t[m+1]<='z')t[m+1]=t[m+1]-32;
		if (t[m+1]>='0'&&t[m+1]<='9') p=(t[m+1]-'0')*16;
			else p=(t[m+1]-'A'+10)*16;

		/***************
		second hex digit
		***************/
		if (t[m+2]>='a'&&t[m+2]<='z')t[m+2]=t[m+2]-32;
                if (t[m+2]>='0'&&t[m+2]<='9') p=p+(t[m+2]-'0');
	                else p=p+(t[m+2]-'A'+10);

                _ftmp[n]=p;  /* insert value into output string */
		n++; 
		m=m+2;
                }

        _ftmp[n]=0; 

	{
		char * p1;
		p1=sym_((int)11,(unsigned char *)t,(unsigned char *)t1,svPtr); /* retrieve */

	/*********************************************************************
	multiple instance of the same variable name have nbrs appended to name
	*********************************************************************/

		if (p1!=NULL) {
                	dup++;
                	sprintf(t1,"%d",dup);
                	strcat(t,t1);
                	}

        	p1=sym_((int)0,(unsigned char *)t,(unsigned char *)_ftmp,svPtr); /* store */
	}

	/**********************************
	not at end yet - shift input string
	**********************************/

        if (k) { 
		for (k=i+1; t[k]!=0 && k<QS_MAX; k++) t[k-(i+1)]=t[k];
                t[k-(i+1)]=0;
                goto nxtarg;
                }
}

cgi_exit: ;

}


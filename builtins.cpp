#include <mumpsc/libmpscpp.h>

char * Cosine(struct MSV* svptr, char * ep, char * arg1, char * arg2) {

      int i,j;
      double x;
      static char tmp[32];
      for (i=0; arg1[i]!=0; i++) if (arg1[i]==1) break;
      arg1[i]=0;
      global a(&arg1[1]); // bypass ^

      for (j=0; arg2[j]!=0; j++) if (arg2[j]==1) break;
      arg2[j]=0;
      global b(&arg2[1]); // bypass ^

      x=a(&arg1[i+1]).Cosine(b(&arg2[j+1]));

      sprintf(tmp,"%g",x);
      return tmp;
      }

char * Avg(struct MSV* svptr, char * ep, char * arg1) {

      int i,j;
      double x;
      static char tmp[32];
      for (i=0; arg1[i]!=0; i++) if (arg1[i]==1) break;
      arg1[i]=0;
      global a(&arg1[1]); // bypass ^

      x=a(&arg1[i+1]).Avg();

      sprintf(tmp,"%g",x);
      return tmp;
      }

char * Count(struct MSV* svptr, char * ep, char * arg1) {

      int i,j;
      double x;
      static char tmp[32];
      for (i=0; arg1[i]!=0; i++) if (arg1[i]==1) break;
      arg1[i]=0;
      global a(&arg1[1]); // bypass ^

      x=a(&arg1[i+1]).Count();

      sprintf(tmp,"%g",x);
      return tmp;
      }

char * Max(struct MSV* svptr, char * ep, char * arg1) {

      int i,j;
      double x;
      static char tmp[32];
      for (i=0; arg1[i]!=0; i++) if (arg1[i]==1) break;
      arg1[i]=0;
      global a(&arg1[1]); // bypass ^

      x=a(&arg1[i+1]).Max();

      sprintf(tmp,"%g",x);
      return tmp;
      }

char * Min(struct MSV* svptr, char * ep, char * arg1) {

      int i,j;
      double x;
      static char tmp[32];
      for (i=0; arg1[i]!=0; i++) if (arg1[i]==1) break;
      arg1[i]=0;
      global a(&arg1[1]); // bypass ^

      x=a(&arg1[i+1]).Min();

      sprintf(tmp,"%g",x);
      return tmp;
      }

char * Multiply(struct MSV* svptr, char * ep, char * arg1, char * arg2, char * arg3) {

      int i,j,k;
      double x;
      static char tmp[32];
      for (i=0; arg1[i]!=0; i++) if (arg1[i]==1) break;
      arg1[i]=0;
      global a(&arg1[1]); // bypass ^

      for (j=0; arg2[j]!=0; j++) if (arg2[j]==1) break;
      arg2[j]=0;
      global b(&arg2[1]); // bypass ^

      for (k=0; arg3[k]!=0; k++) if (arg3[k]==1) break;
      arg3[k]=0;
      global c(&arg3[1]); // bypass ^

      a(&arg1[i+1]).Multiply(b(&arg2[j+1]),c(&arg3[k+1]));

      return "";
      }

char * Sum(struct MSV* svptr, char * ep, char * arg1) {

      int i,j;
      double x;
      static char tmp[32];
      for (i=0; arg1[i]!=0; i++) if (arg1[i]==1) break;
      arg1[i]=0;
      global a(&arg1[1]); // bypass ^

      x=a(&arg1[i+1]).Sum();

      sprintf(tmp,"%g",x);
      return tmp;
      }

char * Transpose(struct MSV* svptr, char * ep, char * arg1, char * arg2) {

      int i,j;
      double x;
      static char tmp[32];
      for (i=0; arg1[i]!=0; i++) if (arg1[i]==1) break;
      arg1[i]=0;
      global a(&arg1[1]); // bypass ^

      for (j=0; arg2[j]!=0; j++) if (arg2[j]==1) break;
      arg2[j]=0;
      global b(&arg2[1]); // bypass ^

      a(&arg1[i+1]).Transpose(b(&arg2[j+1]));

      return "";
      }

char * SmithWaterman (struct MSV *, char * ep, char * s1, char *s2, char *sa, char * sm, char * gap,
       char * mm, char * ma){

      int sax,smx,gapx,mmx,max;
      char s1a[STR_MAX],s2a[STR_MAX];
      static char tmp[32];
      s1a[0]=s2a[0]=' ';
      strcpy(&s1a[1],s1);
      strcpy(&s2a[1],s2);
      sscanf(sa,"%d",&sax);
      sscanf(sm,"%d",&smx);
      sscanf(gap,"%d",&gap);
      sscanf(mm,"%d",&mmx);
      sscanf(ma,"%d",&max);
      sax=sw(s1a,s2a,sax,smx,gapx,mmx,max);
      sprintf(tmp,"%d",sax);
      return tmp;
      }

char * IDF (struct MSV* svptr, char * ep, char * arg1, char * arg2) {

      int i,j;
      double x;
      static char tmp[32];
      for (i=0; arg1[i]!=0; i++) if (arg1[i]==1) break;
      arg1[i]=0;
      global a(&arg1[1]); // bypass ^
      sscanf(arg2,"%lf",&x);
      a(&arg1[i+1]).IDF(x);
      return "";
      }

const char * Replace (struct MSV* svPtr, char * ep, char *arg1, char * arg2, char arg3) {
        mstring a,b,c;
        a=arg1;
        b=arg2;
        c=arg3;
        if (a.replace(b,c)==1) {
                svPtr->tpx=1;
                }
        svPtr->tpx=0;
        return a.c_str();
        }

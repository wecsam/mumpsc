        zmain
+#include <mumpsc/cgi.h>
+ static struct C {char * s; C *next;} *S=NULL,*p1, *p2=NULL;
+ int DirectRead(int,unsigned char *);
+ if (argc>=2) $SymPut("%",argv[1]);
+ else $SymPut("%","");
+ if (argc>=3) $SymPut("%1",argv[2]);
+ if (argc>=4) $SymPut("%2",argv[3]);
+ if (argc>=5) $SymPut("%3",argv[4]);
+ if (argc>=6) $SymPut("%4",argv[5]);
+ if (argc>=7) $SymPut("%5",argv[6]);
+ if (argc>=8) $SymPut("%6",argv[7]);
+ if (argc>=9) $SymPut("%7",argv[8]);
+ if (argc>=10) $SymPut("%8",argv[9]);
        if %'="" do
      . if $f(%,"./") set %=$p(%,"./",2)
        . set %="d ^"_%
        . x %
        . halt
        write !,"Mumps Interpreter V11.0 ",$zd,!!
        for  do
        . write "> "
      . read %%
        . if %%="h" halt
        . if %%="halt" halt
      . x %%

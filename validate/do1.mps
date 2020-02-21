+ /* note: C fcns must preceed Mumps fcns */
+#include <mumpsc/libmpscpp.h>
+ char * fff(StateVector svPtr, char * ep, char * x) {
+     printf("%s\n",x);
+     return "";
+     }

^ccc()
      for i=1:1:5 write i," "
      write !
      quit

^ddd(x)
      write x,!
      quit

^eee(x)
      quit x

^ggg()
ep1   write "1 2 3 4 5",!
      quit
ep2   write "6 7 8 9 0",!
      quit

^hhh(a)
ep1   write "1 2 3 4 5",a,!
      quit
ep2   write "6 7 8 9 0",a,!
      quit

      zmain
      write "*** 1 2 3 4 5",!
      do abc
      write "*** 1 2 3 4 5",!
      do:1=1 abc
      write "*** 1 2 3 4 5",!
      do abc:1=1
      write "*** 1 2 3 4 5",!
      do:1=1 abc:1=1
      write "*** 1 2 3 4 5",!
      do:1=0 abc:1=1 do abc
      write "*** 1 2 3 4 5",!
      do:1=1 def:1=0 do abc
      write "*** 1 2 3 4 5",!
      do:1=1 def:1=0,abc
      write "*** 1 2 3 4 5 10 11 12 13 14 15",!
      do abc,def
      write "*** 1 2 3 4 5 10 11 12 13 14 15",!
      do:1=1 abc,def
      write "*** 1 2 3 4 5 10 11 12 13 14 15",!
      do:1=1 abc,def:1=1
      write "*** 1 2 3 4 5 10 11 12 13 14 15",!
      do:1=1 abc:1=1,def:1=1

      write "*** 1 2 3 4 5",!
      do aaa("1 2 3 4 5")
      write "*** 1 2 3 4 5",!
      write $$bbb("1 2 3 4 5"),!
      write "*** 1 2 3 4 5",!
      do ^ccc
      write "*** 1 2 3 4 5",!
      do ^ddd("1 2 3 4 5")
      write "*** 1 2 3 4 5",!
      write $$^eee("1 2 3 4 5"),!
      write "*** 1 2 3 4 5",!
      write $$^fff("1 2 3 4 5")
      set i="1 2 3 4 5"
      write "*** 1 2 3 4 5",!
      do ep1^ggg
      write "*** 6 7 8 9 0",!
      do ep2^ggg
      write "*** 1 2 3 4 5*",!
      do ep1^hhh("*")
      write "*** 6 7 8 9 0*",!
      do ep2^hhh("*")
      write "*** 1 2 3 4 5*",!
      do jjj

      set j=0
      write "*** done",!
retry for i=1:1:10 do  
      . set j=j+1
      . if j<100000 goto retry
      write "done",!


      halt
abc   for i=1:1:5 write i," "
      write !
      quit
def   for i=10:1:15 write i," "
      write !
      quit
aaa(x)
      write x,!
      quit
bbb(x)
      quit x
jjj   write "1 2 3"
      do kkk
      quit
kkk   write " 4 5",!
      quit

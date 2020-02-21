#!/usr/bin/mumps
 KILL

 if 1=1 do
 . new a
 . set a=88
 . write "lev 1 expect 88: ",a,!
 . if 1=1 do
 .. new b
 .. set b=100
 .. write "****************** lev 2 expect 88 100 a=",a," b=",b,!
 . write "&&&&&& lev 1 expect 88 0 ",a," ",$d(b)," &&&&&&&&",!

 write "expect 0 ",$d(a),!


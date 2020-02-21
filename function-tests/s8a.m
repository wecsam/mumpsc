#!/usr/bin/mumps
 KILL

 if 1=1 do
 . new a
 . set a=88
 . write "lev 1 expect 88: ",a,!
 . write "&&&&&& lev 1 expect 88 0 ",a," ",$d(b)," &&&&&&&&",!

 write "expect 0 ",$d(a),!


#!/usr/bin/mumps

 write "test 1 -  alterations of $t should be undone",!
 write "expect 1 0 0",!,"--------------------",!!

 KILL

 set a=1,b=2

 if a=b do
 . do one
 else  do
 . do two
 . write $t,!

 write $t,!

one if 1=1
    quit

two if 1=1
 write $t,!
    quit

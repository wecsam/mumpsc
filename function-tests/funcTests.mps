#!/usr/bin/mumps
 KILL

 write !!,"Test function calls and New",!!
 set y=99
 do one
 write "01 expect 99 0: ",y," ",$data(x),!!

 do two
 write "02 expect 1: ",$data(x),!!

 do three(101)
 write "03 expect 0: ",$d(d),!!

 kill

 set j=99
 if 1=1 do
 . new a
 . set a=99
 . if 1=1 do
 .. new b
 .. s b=102
 .. write "04 exepect 99 102: ",a," ",b,!
 . write "05 expect 99 0: ",a," ",$d(b),!

 write "06 expect 99 0 0: ",j," ",$d(a)," ",$d(b),!!

 kill
 write "call s6a.m as function with return value",!
 set %=$$^s6a.m
 write "07 expect 6 1 1 1 0: ",%," ",$d(a)," ",$d(b)," ",$d(c)," ",$d(y),!!

 kill
 write "call s6a.m with DO and no return value",!
 do ^s6a.m
 write "08 expect 1 1 1 0: ",$d(a)," ",$d(b)," ",$d(c)," ",$d(y),!!

 kill
 set p=888
 do ^s6b.m(p)
 write "09 expect 1 1 1 0: ",$d(a)," ",$d(b)," ",$d(c)," ",$d(k),!!

 kill
 s i=1,j=2,k=3
 do ^s6c.m(i,j,k)
 write "10 expect 2: ",j,!!

 kill
 write "recursive function call factorial",!
 set i=$$factorial^factor.mps(5)
 write "expect 120: ",i,!

 halt

one new x
    set x=100
    write "expect 99 100: ",y," ",x,!
    do two
    write "expect 99 99: ",y," ",x,!
    quit

two 
    set x=99
    quit

three(d)
    write "expect 101: ",d,!
    quit

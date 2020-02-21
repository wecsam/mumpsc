#!/usr/bin/mumps
 write !!

 set i=123
 do one
 write "expect 0 345: ",$data(x)," ",i,!
 halt

 do two
 write "expect 1: ",$data(x),!

 halt

one write !,"enter sub one",!
    new x
    set x=99
    write "in sub one expect 123 99 i=",i," x=",x,!
    do two
    write "in sub one expect 123 88 i=",i," x=",x,!
    write !,"leave sub one",!
    quit

two 
    write !,"enter sub two",!
    set x=88
    write "in sub two expect 88 123 x=",x," i=",i,!
    set i=345
    write !,"leave sub two",!
    quit

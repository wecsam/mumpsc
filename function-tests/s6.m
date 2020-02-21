#!/usr/bin/mumps
 KILL

 set y=99
 do one
 write "expect 99 0  -> ",y," ",$data(x),!

 do two
 write "expect 1 ->  ",$data(x),!

 set x=222
 do three(101)
 write "expect 0 ->  ",$d(d),!

 kill
 set x=33
 do four(.x)
 write "expect 44 ->  ",x,!

 kill

 set j=99
 if 1=1 do
 . new a,c
 . set c=456,a=99
 . if 1=1 do
 .. new b,c
 .. s b=102,c=789
 .. write "expect 99 102 789 ->  ",a," ",b," ",c,!
 . write "expect 99 0 456 ->  ",a," ",$d(b)," ",c,!

 write "**expect 99 0 0 0 ->  ",j," ",$d(a)," ",$d(b)," ",$data(c),!

 kill
 set %=$$^s6a.m
 write "expect 6 1 1 1 0 ->  ",%," ",$d(a)," ",$d(b)," ",$d(c)," ",$d(y),!

 kill
 do ^s6a.m
 write "expect 1 1 1 0 ->  "," ",$d(a)," ",$d(b)," ",$d(c)," ",$d(y),!

 kill
 set p=888
 do xx^s6b.m(p)
 write "expect 1 1 1 0 -> ",$d(a)," ",$d(b)," ",$d(c)," ",$d(k),!

 kill
 s i=1,j=2,k=3
 do ^s6c.m(i,j,k)
 write "expect 2 -> ",j,!

 kill
 s i=1,j=2,k=3
 s z=$$^s6d.m(i,j,k)
 write "expect 6 2 -> ",z," ",j,!
 s i=1,j=2,k=3
 s z=$$^s6d.m(i,.j,k)
 write "expect 6 99 -> ",z," ",j,!

 kill

 set p=888
 do ^s6b.m(.p)
 write "expect 1 1 1 0 999 -> ",$d(a)," ",$d(b)," ",$d(c)," ",$d(k)," ",p,!

 kill

 w "expect a b c -> ",!
 d a^s16a.m
 w "expect  b c -> ",!
 d b^s16a.m
 w "expect c -> ",!
 d c^s16a.m

 kill

 s x="a^s16a.m"
 w "expect a b c",!
 d @x

 kill

 w "expect 99 -> "
 s xx="two"
 d @xx
 w x,!

 kill

 w "expect expect 1 2 3 22 -> "
 s xx="^s6a.m"
 d @xx

 kill

 s xx="xx^s6b.m(101)"
 do @xx
 write "expect 1 1 1 0 -> ",$d(a)," ",$d(b)," ",$d(c)," ",$d(k),!

 kill

 set x=222
 s xx="three(101)"
 do @xx
 write "expect 0 ",$d(d),!


 kill

 set p=888
 set xx="xx^s6b.m(.p)"
 do @xx
 write "expect 1 1 1 0 999 -> ",$d(a)," ",$d(b)," ",$d(c)," ",$d(k)," ",p,!

 halt

#---------------------------------------------

 kill
 s x=10
 f i=1:1:x s a(i)=i f j=1:1:5 s a(i,j)=j
 w "expect 1...10 ",!
 f i=1:1:x w ! f j=1:1:5 w " ",a(i,j)
 w i," ",j,!

 f i="":$o(a(i)):"" w i,!

 kill
 s x=10
 f i=1:1:x s ^a(i)=i f j=1:1:5 s ^a(i,j)=j
 w "expect 1...10 ",!
 f i=1:1:x w !,"*" f j=1:1:5 w " ",^a(i,j)
 w i," ",j,!

 f i="":$o(^a(i)):"" w i,!

 kill
 s x="f i=1:1:10 w i,!"
 html expect 1 thru 10 &!
 x x 

 halt

one new x
    set x=100
    write "expect 99 100 -> ",y," ",x,!
    do two
    write "expect 99 99 -> ",y," ",x,!
#    goto xx
xx quit

two 
    set x=99
    quit

three(d)
    write "expect 101 222 -> ",d," ",x,!
    do five(x)
    quit

four(z)
    write "expect 33 -> ",z,!
    set z=44
    quit

five(x)
    write "*expect 101 ",d,!
    quit
    

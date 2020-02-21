#!/usr/bin/mumps
 write "start s6.mps",!
 kill
 write "after initial kill",!!

 set y=99
 do one
 write "a1 expect 99 0  -> ",y," ",$data(x),!!

 do two
 write "a2 expect 1 ->  ",$data(x),!!

 do three(101)
 write "a3 expect 0 ->  ",$d(d),!

 kill

 set x=33
 do four(.x)
 write "a4 expect 44 ->  ",x,!

 kill
 set y=33
 do five(.y)
 write "a4a expect 44 -> ",y,!
 write "$d(a) $d(z) -> 0 0 -> ",$d(a),$d(z),!

 kill

 set j=99
 if 1=1 do
 . new a
 . set a=99
 . if 1=1 do
 .. new b
 .. s b=102
 .. write "a5 expect 99 102 ->  ",a," ",b,!
 . write "a6 expect 99 0 ->  ",a," ",$d(b),!

 write "a7 expect 99 0 0 ->  ",j," ",$d(a)," ",$d(b),!

 kill
 set %=$$^s6a.mps
 write "a8 expect 6 1 1 1 0 ->  ",%," ",$d(a)," ",$d(b)," ",$d(c)," ",$d(y),!

 kill
 do ^s6a.mps
 write "a9 expect 1 1 1 0 ->  "," ",$d(a)," ",$d(b)," ",$d(c)," ",$d(y),!

 kill
 set p=888
 write "val(k) is 888",!
 do xx^s6b.mps(p)
 write "a10 expect 1 1 1 0 -> ",$d(a)," ",$d(b)," ",$d(c)," ",$d(k),!

 kill
 s i=1,j=2,k=3
 write "val (i j k) 1 2 3",!
 do ^s6c.mps(i,j,k)
 write "a11 expect 2 -> ",j,!

 kill
 s i=1,j=2,k=3
 s z=$$^s6d.mps(i,j,k)
 write "a12 expect 6 2 -> ",z," ",j,!
 s i=1,j=2,k=3
 s z=$$^s6d.mps(i,.j,k)
 write "a13 expect 6 99 -> ",z," ",j,!

 kill

 set p=888
 write "val 888",!
 do ^s6b.mps(.p)
 write "a14 expect 1 1 1 0 999 -> ",$d(a)," ",$d(b)," ",$d(c)," ",$d(k)," ",p,!

 kill

 w "a15 expect a b c -> ",!
 d a^s16a.mps
 w "a16 expect  b c -> ",!
 d b^s16a.mps
 w "a17 expect c -> ",!
 d c^s16a.mps

 kill

 s x="a^s16a.mps"
 w "a18 expect a b c",!
 d @x

 kill

 w "a19 expect 99 -> "
 s xx="two"
 d @xx
 w x,!

 kill

 w "a20 expect expect 1 2 3 22 -> "
 s xx="^s6a.mps"
 d @xx

 kill

 s xx="xx^s6b.mps(101)"
 write "a21 val 101",!
 do @xx
 write "a21 expect 1 1 1 0 -> ",$d(a)," ",$d(b)," ",$d(c)," ",$d(k),!

 kill

 s xx="three(101)"
 w "a22 val 101",!
 do @xx
 write "a22 expect 0 ",$d(d),!


 kill

 set p=888
 write "a23 val 888",!
 set xx="xx^s6b.mps(.p)"
 do @xx
 write "a23 expect 1 1 1 0 999 -> ",$d(a)," ",$d(b)," ",$d(c)," ",$d(k)," ",p,!

 halt

#---------------------------------------------

 kill
 s x=10
 f i=1:1:x s a(i)=i f j=1:1:5 s a(i,j)=j
 w "a24 expect 1...10 ",!
 f i=1:1:x w ! f j=1:1:5 w " ",a(i,j)
 w i," ",j,!

 f i="":$o(a(i)):"" w i,!

 kill
 s x=10
 f i=1:1:x s ^a(i)=i f j=1:1:5 s ^a(i,j)=j
 w "a25 expect 1...10 ",!
 f i=1:1:x w !,"*" f j=1:1:5 w " ",^a(i,j)
 w i," ",j,!

 f i="":$o(^a(i)):"" w i,!

 kill
 s x="f i=1:1:10 w i,!"
 html a26 expect 1 thru 10 &!
 x x 

 halt

one write "in one",!
    new x
    set x=100
    write "one 1 a27 expect 99 100 -> ",y," ",x,!
    do two
    write "one 2 a28 expect 99 99 -> ",y," ",x,!
    quit

two 
    write "in two",!
    set x=99
    quit

three(d)
    write "a29 expect 101 -> ",d,!
    quit

four(z)
    write "a30 expect 33 -> ",z,!
    set z=44
    quit

five(a)
    write "a31 rcvs expect 33 -> ",a,!
    do four(.a)
    write "a31 rtrnd expect 44 -> ",a,!
    quit

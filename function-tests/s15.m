#!/usr/bin/mumps

 kill ^b,^a

 s t1=$zd1
 s c=0
 f i=1:1:100 f j=1:1:100 f k=1:1:100 s ^b(1,i,j,k)=c s c=c+1

 w "time=",$zd1-t1," count=",c,!
 s t1=$zd1
 write "merge test",!
 s ^a(1)=999

 merge ^a(1)=^b(1)
 w "time=",$zd1-t1,!
 s t1=$zd1

 set x="^a(1)"

 s c=0
 f  d
 . set x=$q(x)
 . i x="" break
 . s c=c+1

 w "time=",$zd1-t1," count=",c,!

 halt

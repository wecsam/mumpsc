#!/usr/bin/mumps

 kill
 s x=1000
 f i=1:1:x s ^a(i)=i f j=1:1:5 s ^a(i,j)=j
 w "expect 1...10 ",!
 f i=1:1:x w !,"*" f j=1:1:5 w " ",^a(i,j)
 w i," ",j,!

# f i="":$o(^a(i)):"" w i,!

 kill
 s x="f i=1:1:10 w i,!"
 html expect 1 thru 10 &!
 x x 

 halt


#!/usr/bin/mumps

 for i=$o(%globals(i)) do
 . w i,!
 . sql drop table &~i~ ;

 sql/f

 f i=1:1:10 f j=1:1:5 f k=1:1:5 f m=1:1:5 s ^a(i,j,k,m)=i

 s x="^a"

 for  do
 . set x=$query(@x)
 . if x="" break
 . w x," ",@x,!

 kill ^a(5)

 w "====================================",!

 s x="^a"

 for  do
 . set x=$query(@x)
 . if x="" break
 . w x," ",@x,!

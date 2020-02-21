#!/usr/bin/mumps

 kill
 f i=1:1:10 s ^aa(i)=i
 f i=1:1:10 w ^aa(i)
 w !
 k ^aa
 f i=1:1:10 w "*",^aa(i)
 w !
 f i=1:1:10 s ^aa(i)=i
 kill ^aa(5)
 f i=1:1:10 w "*",^aa(i)
 w !
 f i=1:1:10 s ^aa(i)=i f j=1:1:5 s ^aa(i,j)=j
 kill ^aa(5)
 f i=1:1:10 w !,i,"-> " f j=1:1:5 w "*",^aa(i,j)
 w !,"end",!

 w !
 f i=1:1:10 s ^aa(i)=i f j=1:1:5 f k=1:1:5 s ^aa(i,j,k)=j
 kill ^aa(5)
 f i=1:1:10 w !,i,"-> " f j=1:1:5 w !,j,"-: " f k=1:1:5 w "*",^aa(i,j,k)
 w !,"end",!

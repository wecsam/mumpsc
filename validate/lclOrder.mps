#!/usr/bin/mumps

 for i=1:1:10 s a(i)=i for j=1:1:5 set a(i,j)=j+i
 write "expect 1 thru 10",!
 for i=1:1:10 w a(i)," "
 write !

 write "expect 9 thru 10, 1",!
 set i=""
 for  do
 . set i=$order(a(i),-1)
 . if i="" break
 . write i," "
 write !

 write "expect 1 10 ... 9",!
 set i=""
 for  do
 . set i=$order(a(i),1)
 . if i="" break
 . write i," "
 write !

 write "expect 1 10 ... 9",!
 set i=""
 for  do
 . set i=$order(a(i))
 . if i="" break
 . write i," "
 write !

#!/usr/bin/mumps

 kill ^a,^b

 set ^a(1)="a"
 set ^a(1,2)="b"
 set ^a(1,2,3)="c"
 set ^a(1,3)="d"
 set ^b(1)="100"
 set ^b(1,2)="200"
 set ^b(1,3)="300"

 merge ^a(1,2)=^b(1)

 set x="^a"

 for  do
 . set x=$query(x)
 . if x="" break
 . write x," ",@x,!

 halt

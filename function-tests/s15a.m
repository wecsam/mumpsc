#!/usr/bin/mumps

 kill ^b,^a

 KILL ^A,^B
 SET ^A(1,2)="First"
 SET ^A(1,2,4)="Second"
 SET ^B(5,6,7)="Third"
 SET ^B(5,6,8)="Fourth"
 SET ^B(5,6,7,8,1)="Fifth"
 SET ^B(5,6,7,8,9)="Sixth"

 MERGE ^A(1,2)=^B(5,6,7)

 set x="^A(1,2)"
 w x," ",@x,!
 set x=$q(x)
 w x," ",@x,!
 set x=$q(x)
 w x," ",@x,!
 set x=$q(x)
 w x," ",@x,!

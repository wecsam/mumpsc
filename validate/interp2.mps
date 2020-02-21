#!/usr/bin/mumps
 set a=1,b=2,c=3,d=4
 set x(1,2,3,4)=99
 write "*** $name() tests",!
 write "expect x(1,2,3,4) ",@"$name(x(a,b,c,d))",!
 write "expect x(1,2,3,4) ",@"$name(x(a,b,c,d),99)",!
 write "expect x(1,2,3,4) ",@"$name(x(a,b,c,d),4)",!
 write "expect x(1,2,3) ",@"$name(x(a,b,c,d),3)",!
 write "expect x(1,2) ",@"$name(x(a,b,c,d),2)",!
 write "exepct x(1) ",@"$name(x(a,b,c,d),1)",!
 write "expect x ",@"$name(x(a,b,c,d),0)",!
 set a=1,b=2,c=3,d=4
 set ^x(1,2,3,4)=99
 write "*** $name() tests",!
 write "expect ^x(1,2,3,4) ",@"$name(^x(a,b,c,d))",!
 write "expect ^x(1,2,3,4) ",@"$name(^x(a,b,c,d),99)",!
 write "expect ^x(1,2,3,4) ",@"$name(^x(a,b,c,d),4)",!
 write "expect ^x(1,2,3) ",@"$name(^x(a,b,c,d),3)",!
 write "expect ^x(1,2) ",@"$name(^x(a,b,c,d),2)",!
 write "exepct ^x(1) ",@"$name(^x(a,b,c,d),1)",!
 write "expect ^x ",@"$name(^x(a,b,c,d),0)",!

 k
 k ^b
 write "$ql() expect 2 ",@"$ql(""b(1,2)"")",!
 set name="dob(1862,1)"
 write "$qs() expect 1862 ",@"$qs(name,1)",!
 set b(1)=1
 set b(1,2)=2
 set b(2)=2
 write "$q() expect b(1,2) ",@"$q(""b(1)"")",!

 write "$ql() expect 2 ",@"$ql(""^b(1,2)"")",!
 set name="^dob(1862,1)"
 write "$qs() expect 1862 ",@"$qs(name,1)",!
 set ^b(1)=1
 set ^b(1,2)=2
 set ^b(2)=2
 write "$q() expect ^b(1,2) ",@"$q(""^b(1)"")",!


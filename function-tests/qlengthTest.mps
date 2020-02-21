#!/usr/bin/mumps

 w !,"qsubscript tests ",!!

 s k=99
 s x="^a(1,k,3)"
 s ^x(1)="^a(1,""a,b,c"",3)"


 html write "expect 3 ",$qlength("a(1,2,3)"),! &!
 write "expect 3 ",$qlength("a(1,2,3)"),!

 html write "expect 3 ",$qlength("^a(1,2,3)"),! &!
 write "expect 3 ",$qlength("^a(1,2,3)"),!

 html write "expect 3 ",$qlength(x),! &!
 write "expect 3 ",$qlength(x),!

 html write "expect 3 ",$qlength(^x(1)),! &!
 write "expect 3 ",$qlength(^x(1)),!

 halt

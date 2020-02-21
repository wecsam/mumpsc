#!/usr/bin/mumps

 w !,"qsubscript tests ",!!

 s x="^a(1,k,3)"
 s y(1)=x
 s j=2
 s k=99
 s ^x(1)=2
 s ^x(2)="^a(1,k,3)"

 html s z=$qsubscript(x,j) &!
 s z=$qsubscript(x,j)
 write "ans=",z,!
 html &! s z=$qsubscript(x,2) &!
 s z=$qsubscript(x,2)
 write "ans=",z,!
 html &! s z=$qsubscript(y(1),2) &!
 s z=$qsubscript(y(1),2)
 write "ans=",z,!
 html &! s z=$qsubscript(x,^x(1)) &!
 s z=$qsubscript(x,^x(1))
 write "ans=",z,!
 html &! s z=$qsubscript(^x(2),j) &!
 s z=$qsubscript(^x(2),j)
 write "ans=",z,!
 html &! s z=$qsubscript(^x(2),"2") &!
 s z=$qsubscript(^x(2),"2")
 write "ans=",z,!
 html &! s z=$qsubscript(^x(2),^x(1)) &!
 s z=$qsubscript(^x(2),^x(1))
 write "ans=",z,!
 html &! s z=$qsubscript("^a(1,99,3)","2") &!
 s z=$qsubscript("^a(1,99,3)","2")
 write "ans=",z,!
 html &! s z=$qsubscript("^a(1,99,3)",j) &!
 s z=$qsubscript("^a(1,99,3)",j)
 write "ans=",z,!
 html &! s z=$qsubscript("^a(1,99,3)",^x(1)) &!
 s z=$qsubscript("^a(1,99,3)",^x(1))
 write "ans=",z,!

 halt

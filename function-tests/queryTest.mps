#!/usr/bin/mumps

 w !,"query qsubscript qlength tests",!

 set a(2,2)=99

 w "expect a(2,2) ",$query(@"a"),!
 w "expect nothing (empty string) ",$query(@"a(2,2)"),!
 w "expect a(2,2) ",$query(@"a(2,1)"),!
 w "expect a(2,2) ",$query(@"a(1)"),!


 kill ^a
 f i=1:1:5 f j=1:1:3 s ^a(i,j)=i+j
 f i=1:1:5 f j=1:1:3 s a(i,j)=i+j

 set j=1

 w "expect a(1,1) ",$query(^a(1)),!
 w "expect a(1,2) ",$query(^a(1,1)),!
 w "expect a(1,2) ",$query(^a(1,j)),!
 w "expect a(1,1) ",$query(@"^a(1)"),!
 w "expect nothing (empty string) ",$query(@"^a(5,3)"),!
 w "expect a(1,1) ",$query(@"a"),!
 w "expect a(1,1) ",$query(@"a(1)"),!
 w "expect a(1,1) ",$query(@"a(0)"),!
 w "expect nothing (empty string) ",$query(@"a(5,3)"),!
 w "-----------------------------------",!


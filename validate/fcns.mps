#!/usr/bin/mumps
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#+   
#+     Mumps Compiler Example Code
#+     Copyright (C) 2000, 2001, 2002, 2012, 2013 by Kevin C. O'Kane  
#+
#+     Kevin C. O'Kane
#+     Department of Computer Science
#+     University of Northern Iowa
#+     Cedar Falls, IA 50613-0507 USA
#+
#+     kc.okane@gmail.com
#+     http://www.cs.uni.edu/~okane
#+     http://omahadave.com
#+
#+
#+ This program is free software; you can redistribute it and/or modify
#+ it under the terms of the GNU General Public License as published by
#+ the Free Software Foundation; either version 2 of the License, or
#+ (at your option) any later version.
#+ 
#+ This program is distributed in the hope that it will be useful,
#+ but WITHOUT ANY WARRANTY; without even the implied warranty of
#+ MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#+ GNU General Public License for more details.
#+ 
#+ You should have received a copy of the GNU General Public License
#+ along with this program; if not, write to the Free Software
#+ Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#+
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

      Zmain

      write "Functions and Builtin Variables",!!

      write "variables/fcns",?30,"expected",?50,"actual",!

      write "$io",?30,"5 ",?50,$io,!
      write "$zd date",?30,"varies",?50,$zd,!
      write "horolog date ",?30,"varies",?50,$h,!
      if 1=1 set i=1
      write "$test",?30,"1 ",?50,$test,!
      write "$TEST",?30,"1 ",?50,$TEST,!
      write "$T",?30,"1 ",?50,$T,!
      write "$t",?30,"1 ",?50,$t,!
      if 1=0 set i=1
      write "$test",?30,"0 ",?50,$test,!
      write "$job ",?30,"varies",?50,$job,!
      write "$storage",?30,"999 ",?50,$s,!
      write "$x $y",?30,"varies",?50,$x," ",$y,!

      write "$fnumber",?30,"not imp",?50,$fn(42000,"P",2),!
      write "$ascii",?30,"65",?50,$a("A"),!
      write "$ascii",?30,"66 ",?50,$ascii("Beethoven"),!
      write "$ascii(""HAYDEN"",3)",?30,"89 ",?50,$ascii("HAYDEN",3),!
      write "$CHAR(66,-1,65,67,72)",?30,"BACH ",?50,$CHAR(66,-1,65,67,72),!
      set a="66"
      write "$char(a)",?30,"B ",?50,$c(a),!

      write "------",!
      kill ^a
      write "------",!
      set ^a(1)=1
      set ^a(2)=1

      set ^a(1,1)=11
      set ^a(3,1)=1
      write "$data",?30,"0",?50,$data(^a("none")),!
      write "$data",?30,"11",?50,$data(^a(1)),!
      write "$data",?30,"1",?50,$data(^a(1,1)),!
      write "$data",?30,"1",?50,$data(^a(2)),!
      write "$data",?30,"10",?50,$data(^a(3)),!
      write "$data",?30,"0",?50,$data(none),!
      set i=1
      write "$data",?30,"1",?50,$data(i),!
      set xxx(1)=1
      write "$data",?30,"1",?50,$data(xxx(1)),!
      set xxx(1,1)=11
      write "$data",?30,"11",?50,$data(xxx(1)),!
      set yyy(1,1)=99
      write "$data",?30,"10",?50,$data(yyy(1)),!
      write "$data",?30,"10",?50,$data(yyy),!

      for i=1:1:10 s a(i)=i
      write "$next",?30,"1",?50,$n(a(-1)),!
      write "$next",?30,"10",?50,$n(a(1)),!
      write "$next",?30,"2",?50,$n(a(10)),!

      write "$extract",?30,"B",?50,$extract("Brahms"),!
      write "$extract",?30,"e",?50,$extract("Handel",5),!
      write "$extract",?30,"art",?50,$extract("Mozart",4,6),!
      do ^extractTests.mps

      write "$find",?30,"3",?50,$find("SIBELIUS","I"),!
      set i=3
      write "$find",?30,"7",?50,$find("SIBELIUS","I",i),!
      write "$find",?30,"0",?50,$find("SIBELIUS","I",7),!

      write "$get",?30,"unknown",?50,$get(abc),!

      write "$justify(""3.14159"",9)",?30,"xx3.14159",?50,$justify("3.14159",9),!
      write "$justify(""3.14159"",9,2)",?30,"xxxxx3.14",?50,$justify("3.14159",9,2),!

      write "$length",?30,"14 ",?50,$length("Verdi & Wagner"),!
      write "$length",?30,"2",?50,$length("Verdi & Wagner","&"),!
      write "$length",?30,"3",?50,$length("Verdi & Wagner"," "),!

      set B3="Beethoven,Bach,Brahms"
      write "$piece",?30,"Beethoven",?50,$p(B3,","),!
      write "$piece",?30,"Brahms",?50,$p(B3,",",3),!
      write "$piece",?30,"Beethoven,Bach",?50,$p(B3,",",1,2),!

      write "$random",?30,"{0,8}",?50,$random(9),!
      set i="test"
      set j=9
      write "select (test): ",?30,9,?50,$select(j+1:i,1:2),!

      set a="abcdefghijklmnop"
      write "translate",?30,"abcDEFghijklmnop",?50,$translate(a,"def","DEF"),!
      write "translate",?30,"abcDEFghimnop",?50,$translate(a,"defjkl","DEF"),!

      set a="aaa$bbb$ccc"
      set b="$"
      set $p(a,b,2)="test"
      write "setpiece: (aaa$test$ccc) ",?30,"aaa$testccc",?50,a,!
      set x(1)="123.45.6789"
      set x="123.45.6789"
      set j=1
      set ^a(j)=x
      set $piece(x(j),".",2)="**"
      write "setpiece local array ",?30,"123.**.6789",?50,x(j),!
      set $piece(x,".",2)="**"
      write "setpiece local scalar ",?30,"123.**.6789",?50,x,!
      set $piece(^a(j),".",2)="**"
      write "setpiece global array ",?30,"123.**.6789",?50,^a(j),!
      read "Enter a value for setpiece test: ",$p(x,".",2)
      write "setpiece on read ",?30,"as typed",?50,x,!

      write "$zd ",?50,$zd,!
      write "$zd1 ",?50,$zd1,!
      write "$zd2($zd1): ",?50,$zd2($zd1),!
      write "$zd3(1998,11,25) (day of year) ",?50,$zd3(1998,11,25),!
      write "$zd4(1998,329) (Nov 25 1998) ",?50,$zd4(1998,329),!
      write "$zd5(1998,11,25) ",?50,$zd5(1998,11,25),!
      write "$zd6 ",?50,$zd6,!
      write "$zd7 ",?50,$zd7,!
      write "$zd8 ",?50,$zd8,!

      write "$zab",?30,"99",?50,$zab(-99),!  // absolute value
      write "$zb",?30,"now is the time",?50,$zb("  now  is   the   time"),!  // remove blanks
      write "$zf",?30,"1",?50,$zf("fcns.mps"),!  // file exists?
      write "$zh",?30,"now+is",?50,$zh("now is"),!  // html encode
      write "$zl",?30,"nat log 10",?50,$zl(10),!  // natural log
      write "$zn",?30,"now",?50,$zn("N?$oW"),! //
      write "$zp",?30,"aaa    *",?50,$zp("aaa",7),"*",!  // left justify
      write "$zqrt",?30,"6",?50,$zsqrt(36),!  // sq root
      write "$zu",?30,"1",?50,$zu(123456789),!  // numeric?
      set test=999
      write "$zv",?30,"999",?50,$zv("test"),!  // retrieve from sym tab

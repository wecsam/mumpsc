#!/usr/bin/mumps
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#+   
#+     Mumps Compiler/Interpreter Example Code
#+     Copyright (C) 2000, 2001, 2002, 2003, 2009, 2012, 2015 by Kevin C. O'Kane  
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

 ; comments may either begin with a semi-colon like
 ; this PROVIDED that the semi-colon is placed where
 ; a command would go.  Semi-colons may not be used
 ; prior to the required TAB character at the beginning
 ; of a line.

# This is also a comment - it must be the very 1st thing on
# a line and have NO TAB characters.
# test of comment /* xxx */

#########################################################################


 write !!,"Compiler/Interpreter Checkout Routines",!!

# delete old globals

 for i=$o(%globals(i)) do
 . w i,!
 . sql drop table &~i~ ;

 sql/f

 write ?45,"Expected",?65,"actual",!!
 write "Builtin variables",!
 write "$io",?45,"5 ",?65,$io,!
 write "$zd",?45,"current date ",?65,$zd,!
 write "$h",?45,"current date ",?65,$h,!

 if 1=1 set i=1
 write "$test",?45,"1 ",?65,$test,!
 write "$TEST",?45,"1 ",?65,$TEST,!
 write "$T",?45,"1 ",?65,$T,!
 write "$t",?45,"1 ",?65,$t,!

 if 1=0 set i=1
 write "$test",?45,"0 ",?65,$test,!

 write "$job",?45,"varies",?65,$job,!
 write "$storage",?45,"999 ",?65,$s,!
 write "$x $y",?45,"varies",?65,$x," ",$y,!

 write !,"Functions",!!

 write "$ascii(""Beethoven"")",?45,"66 ",?65,$ascii("Beethoven"),!
 write "$ascii(""HAYDEN"",3)",?45,"89 ",?65,$ascii("HAYDEN",3),!
 write "$char(66,-1,65,67,72)",?45,"BACH ",?65,$char(66,-1,65,67,72),!

 set a="66"
 write "$char(a)",?45,"B ",?65,$char(a),!

 write "$fnumber(42000,""P"",2) ",?45,"42000.00",?65,$fn(42000,"P",2),!

 set i=1,j=2,k=3
 set b(1)=99
 write !,"$qlength()",!
 write "$ql()",?45,"3",?65,$ql("a(i,j,k)"),!
 write "$ql()",?45,"3",?65,$ql("^a(i,j,k)"),!
 write "$ql()",?45,"2",?65,$ql("a(b(1),2)"),!
 write "$ql()",?45,"1",?65,$ql("a(i)"),!
 write "$ql()",?45,"0",?65,$ql("i"),!

 write !,"$qsubscript()",!
 set i=1,j=2,k=3
 write "$qs(),",?45,"current directory",?65,$qs(a(i,j,k),-1),!
 write "$qs(),",?45,"^a",?65,$qs(^a(i,j,k),0),!
 write "$qs(),",?45,"1",?65,$qs(^a(i,j,k),1),!
 write "$qs(),",?45,"2",?65,$qs(^a(i,j,k),2),!
 write "$qs(),",?45,"3",?65,$qs(^a(i,j,k),3),!

 write !,"$query() Expect ^s(1) ^s(1,1) ... ^s(10,10)",!
 k ^s
 for i=1:1:10 s ^s(i)=1 f j=1:1:10 s ^s(i,j)=j
 set x="^s(1)"
 for  do
 . s x=$query(@x)
 . if x="" break
 . write x,!

 k ^a
 set ^a(1)=1
 set ^a(2)=1
 set ^a(1,1)=11
 set ^a(3,1)=1

 write !,"$data()",!
 write "$data(^a(""none""))",?45,"0",?65,$data(^a("none")),!
 write "$data(^a(1))",?45,"11",?65,$data(^a(1)),!
 write "$data(^a(1,1))",?45,"1",?65,$data(^a(1,1)),!
 write "$data(^a(2))",?45,"1",?65,$data(^a(2)),!
 write "$data(^a(3))",?45,"10",?65,$data(^a(3)),!
 write "$data(none)",?45,"0",?65,$data(none),!
 set i=1
 write "$data(i)",?45,"1",?65,$data(i),!
 set xxx(1)=1
 write "$data(xxx(1)",?45,"1",?65,$data(xxx(1)),!
 set xxx(1,1)=11
 write "$data(xxx(1)",?45,"11",?65,$data(xxx(1)),!
 set yyy(1,1)=99
 write "$data(yyy(1)",?45,"10",?65,$data(yyy(1)),!
 write "$data(yyy)",?45,"10",?65,$data(yyy),!

  write !,"$next() [deprecated]",!
  for i=1:1:10 s a(i)=i
  write "$next(a(-1))",?45,"1",?65,$n(a(-1)),!
  write "$next(a(10))",?45,"10",?65,$n(a(1)),!
  write "$next(a(9))",?45,"-1",?65,$n(a(9)),!

 write !,"$extract()",!
 write "$extract(""Brahms"")",?45,"B",?65,$extract("Brahms"),!
 write "$extract""Handel"",5)",?45,"e",?65,$extract("Handel",5),!
 write "$extract(""Mozart"",4,6)",?45,"art",?65,$extract("Mozart",4,6),!

 write !,"$find()",!
 write "$find(""SIBELIUS"",""I"")",?45,"3",?65,$find("SIBELIUS","I"),!
 set i=3
 write "i=3",!
 write "$find(""SIBELIUS"",""I"",i)",?45,"7",?65,$find("SIBELIUS","I",i),!
 write "$find(""SIBELIUS"",""I"",7)",?45,"0",?65,$find("SIBELIUS","I",7),!

 write !,"$get()",!
 write "$get(abc,""unknown"")",?45,"unknown",?65,$get(abc,"unknown"),!
 write "$get(^abc,""unknown"")",?45,"unknown",?65,$get(^abc,"unknown"),!
 write "$get(i,""unknown"")",?45,"3",?65,$get(i,"unknown"),!

 write !,"$justify()",!
 write "$justify(""3.14159"",9)",?45,?65,"xx3.14159",?65,$justify("3.14159",9),!
 write "$justify(""3.14159"",9,2)",?45,?65,"xxxxx3.14",?65,$justify("3.14159",9,2),!

 write !,"$length()",!
 write "$length(""Verdi & Wagner"")",?45,"14 ",?65,$length("Verdi & Wagner"),!
 write "$length(""Verdi & Wagner"",""&"")",?45,"2",?65,$length("Verdi & Wagner","&"),!
 write "$length(""Verdi & Wagner"","" "")",?45,"3",?65,$length("Verdi & Wagner"," "),!

 write !,"$piece()",!
 set B3="Beethoven,Bach,Brahms"
 write "set B3=""Beethoven,Bach,Brahms""",!
 write "$piece(B3,"","")",?45,"Beethoven",?65,$p(B3,","),!
 write "$piece(B3,"","",3)",?45,"Brahms",?65,$p(B3,",",3),!
 write "$piece(B3,"","",1,2)",?45,"Beethoven,Bach",?65,$p(B3,",",1,2),!

 set a=1,b=2,c=3,d=4
 set x(1,2,3,4)=99
 write !,"$name()",!
 write ?45,"x(1,2,3,4) ",?65,$name(x(a,b,c,d)),!
 write ?45,"x(1,2,3,4) ",?65,$name(x(a,b,c,d),99),!
 write ?45,"x(1,2,3,4) ",?65,$name(x(a,b,c,d),4),!
 write ?45,"x(1,2,3) ",?65,$name(x(a,b,c,d),3),!
 write ?45,"x(1,2) ",?65,$name(x(a,b,c,d),2),!
 write ?45,"x(1) ",?65,$name(x(a,b,c,d),1),!
 write ?45,"x ",?65,$name(x(a,b,c,d),0),!

 write !,"$random(9)",?45,"{0,8}",?65,$random(9),!

      set a="abcdefghijklmnop"
 write !,"translate",!
 write "translate",?45,"abcDEFghijklmnop",?65,$translate(a,"def","DEF"),!
 write "translate",?45,"abcDEFghimnop",?65,$translate(a,"defjkl","DEF"),!

 write !,"Operators ...",!!

 write "Unary +""27.3 days""",?45,"27.3",?65,+"27.3 days",!
 write "Unary -""3.14 radiand""",?45,"-3.14",?65,-"3.14 radians",!
 write "Sum 2.718+""2 above e""",?45,"4.718",?65,2.718+"2 above e",!
 write "Difference 2.12-""6.3 eV""",?45,"-4.18",?65,2.12-"6.3 eV",!
 write "Product 1.00794*""2 atoms/H2""",?45,"2.01588",?65,1.00794*"2 atoms/H2",!
 write "Division 144.132/12.011",?45,"12",?65,144.132/12.011,!
 write "Integer Division 82.8\""29.5 years/orbit""",?45,"2",?65,82.8\"29.5 years/orbit",!

 write !,"Modulo works like C modulo",!
 write "Modulo 42#5",?45,"2",?65,42#5,!
 write "Modulo -42#5",?45,"3",?65,-42#5,!
 write "Modulo 42#-5",?45,"3",?65,42#-5,!
 write "Modulo -42#-5",?45,"2",?65,-42#-5,!

 write "Less Than 1642<1879",?45,"1",?65,1642<1879,!
 write "Greater Than 1452>1564",?45,"0 ",?65,1452>1564,!

 write "Concatenate ""Feynman ""_1918",?45,"Feynman 1918 ",?65,"Feynman "_1918,!

 write "Equals 1969-5=1964",?45,"1",?65,1969-5=1964,!
 write "Equals 1967=""1967: M""",?45,"0",?65,1967="1967: M",!
 write "Equals 1966=01966",?45,"1",?65,1966=01966,!
 write "Equals 1966=""01966""",?45,"0",?65,1966="01966",!
 write "Equals ""Lovelace""=""Hopper""+2",?45,"2",?65,"Lovelace"="Hopper"+2,!
 write "Equals ""Lovelace""=""Lovelace""+3",?45,"3",?65,"Lovelace"="Lovelace"+2,!

 write "not equals ",?45,"0 ",?65,1969-5'=1964,!
 write "not equals ",?45,"1 ",?65,1967'="1967: M",!
 write "not equals ",?45,"0 ",?65,1966'=01966,!
 write "not equals ",?45,"0 ",?65,1966'="01966",!
 write "not equals ",?45,"3 ",?65,"Lovelace"'="Hopper"+2,!
 write "not equals ",?45,"2 ",?65,"Lovelace"'="Lovelace"+2,!

 write "Contains ",?45,"1 ",?65,"Darwin"["win",!
 write "Contains ",?45,"1 ",?65,"Linnaeus"["",!

 write "Follows ",?45,"0 ",?65,"COPERNICUS"]"KEPLER",!

 write "Pattern ",?45,"0 ",?65,"Leakey"?1a,!
 write "Pattern ",?45,"1 ",?65,"Boaz"?1.a,!
 write "Pattern ",?45,"1 ",?65,"Fossey"?1u.5l,!
 write "Pattern ",?45,"0 ",?65,"Goodall"?.4l.p6c.e,!
 write "Pattern ",?45,"1 ",?65,"Maslow"?.E1"low".CNP,!

 write "And ",?45,"0 ",?65,"Watson"&"Crick",!
 write "And ",?45,"0 ",?65,"Morgan"&1735,!
 write "And ",?45,"1 ",?65,1838&1839,!
 write "And ",?45,"1 ",?65,-12000&1996,!
 write "And ",?45,"0 ",?65,1859&0,!

 write "Or ",?45,"0 ",?65,"Jennifer"!"Pasteur",!
 write "Or ",?45,"1 ",?65,"Hoffman"!1928,!
 write "Or ",?45,"1 ",?65,1898!-400,!
 write "Or ",?45,"1 ",?65,1867!0,!

 write "Sorts After ]] ",?45,"1 ",?65,"zzz"]]"aaa",!
 write "Sorts After ]] ",?45,"0 ",?65,"aaa"]]"zzz",!
 write "Not Sorts After ]] ",?45,"0 ",?65,"zzz"']]"aaa",!
 write "Not Sorts After ]] ",?45,"1 ",?65,"aaa"']]"zzz",!
 set a="aaa"
 set b="zzz"
 write "Sorts After ]] ",?45,"1 ",?65,b]]a,!
 write "Sorts After ]] ",?45,"0 ",?65,a]]b,!

 set a="aaa$bbb$ccc"
 set b="$"
 set $p(a,b,2)="test"
 write !,"setpiece",?45,"aaa$test$ccc ",?65,a,!
 set x(1)="123.45.6789"
 set x="123.45.6789"
 set j=1
 set ^a(j)=x
 set $piece(x(j),".",2)="**"
 write "setpiece",?45,"123.**.6789",?65,x(j),!
 set $piece(x,".",2)="**"
 write "setpiece",?45,"123.**.6789",?65,x,!
 set $piece(^a(j),".",2)="**"
 write "setpiece",?45,"123.**.6789",?65,^a(j),!
 read "Enter a value for setpiece test: ",$piece(x,".",2)
 write !,"setpiece after read ",?65,x,!
 set i=1
 set j=2
 set k=3
 set (i,j,k)=99
 write !,"Local multiple assignment",?45,"99 99 99",?65,i," ",j," ",k,!
 set ^a(1)=1,^a(2)=2,^a(3)=3
 set (^a(1),^a(2),^a(3))=99
 write "Global multiple assignment",?45,"99 99 99",?65,^a(1)," ",^a(2)," ",^a(3),!
 set (i,^a(1),j,^a(2))=77
 write "mixed multiple assignment",?45,"77 77 77 77",?65,i," ",^a(1)," ",j," ",^a(2),!

 write "Exponention",!
 set a=3
 set a=a**2
 write "3**2",?45,9,?65,a,!
 set a=9
 set a=a**.5
 write "9**.5",?45,3,?65,a,!

 write "Not ",?45,"1 ",?65,'"Turing",!
 write "Not Not",?45,0,?65,''"Babbage",!
 write "Not ",?45,"1 ",?65,'"Backus"&1957,!
 write "Not ",?45,"1 ",?65,'("Wirth"&"Codd"),!

 write !,"Command examples...",!
 write "Open a file for output and write to it...",!
 open 1:"tmp.tmp,new"
 use 1
 for i=1:1:10 write "test ",i,!
 close 1
 use 5
 write "Reopen the same file and read from it ...",!
 open 1:"tmp.tmp,old"
 for i=1:1 use 1 read a quit:'$t  use 5 write "***",a,!
 use 5
 close 1

 write "Set command ...",!
 set a=1+(2+(3+(4+5)))
 set:1=1 a=1+(2+(3+(4+5))) 

 write "for command ... 1 2 3 4 5 6 7 8 9 10",!
 for i=1:1:10 write " ",i
 write !
 write "for command ... 1 2 3 4 5 6 7 8 9 10",!
 for i=1:1 quit:i>10  write " ",i
 write !

 for i=1:1:10 do fordo write i,!
 if i'=11 write "error for loop control ",i,!! halt
 goto lab99

fordo set j=1
      for k=1:1:5 do
      . write k," "
      write !
      quit

lab99 write "Goto based loops...",!
 set i=1
lab1 write i," "
 set i=i+1
 if i<11 goto lab1
 write !

 kill ^a
 write "Init a global and Next thru it ",!
 for i=1:1:10 for j=1:1:10 set ^a(i,j)=i_","_j
 for i=1:1:10 write ! for j=1:1:10 w ^a(i,j)," "
 write !
 set i=-1
lab2 set i=$next(^a(i))
  if i<0 goto lab3
  write !,i,":"
  set j=-1
lab2a set j=$next(^a(i,j))
  if j<0 goto lab2
  write i,",",j,"="
  write ^a(i,j)," "
  goto lab2a
lab3 write !

 write !,"Init a global and Next thru it ...",!
 for i=1:1:10 for j=1:1:10 set ^b(i,j)=i_","_j
 for i=1:1:10 write ! for j=1:1:10 w ^b(i,j)," "
 write !
 set i=-1
xlab2 set i=$next(^b(i))
 if i<0 goto xlab3
 write !,i,":"
 set j=-1
xlab2a set j=$next(^b(i,j))
 if j<0 goto xlab2
 write ^b(i,j)," "
 goto xlab2a
xlab3 write !

 write !,"global $order()",!
 k ^a
 k ^b
 for i=1:1:10 s ^a(i)=i
 set ^b(1)=1
 set ^b(2)=-1
 write ?45,"1 ",?65,$order(^a("")),!
 write ?45,"9 ",?65,$order(^a(""),-1),!
 write ?45,"1 ",?65,$order(^a(""),1),!
 write ?45,"1 ",?65,$order(^a(""),^b(1)),!
 write ?45,"9 ",?65,$order(^a(""),^b(2)),!
 set i=0,j=1
 write ?45,"1 ",?65,$order(^a(""),j),!
 write ?45,"9 ",?65,$order(^a(""),-j),!
 write ?45,"1 ",?65,$order(^a(""),i+j),!
 write ?45,"9 ",?65,$order(^a(""),i-j),!

 write "expect 1, 10 thru 9",!
 set i=""
 for  do
 . set i=$order(^a(i),1)
 . if i="" break
 . write i,!

 write "expect 9 thru 3,2,10,1",!
 set i=""
 for  do
 . set i=$order(^a(i),-1)
 . if i="" break
 . write i,!

 write "** order without ",!
 k ^a
 k ^b
 for i=1:1:10 s ^a(i)=i
 set ^b(1)=1
 set ^b(2)=-1
 write "expect (next) 1 ",$order(^a("")),!
 write "expect (back) 9 ",$order(^a(""),-1),!
 write "expect 1 ",$order(^a(""),^b(1)),!
 write "expect 9 ",$order(^a(""),^b(2)),!
 set i=0,j=1
 write "expect 1 ",$order(^a(""),j),!
 write "expect 9 ",$order(^a(""),-j),!
 write "expect 1 ",$order(^a(""),i+j),!
 write "expect 9 ",$order(^a(""),i-j),!

 set i=""
 write "expect 1 10 2 3 ... 9",!
 for  do
 . set i=$order(^a(i),1)
 . if i="" break
 . write i,!

 write "expect 9 8 7 ... 10 1",!
 set i=""
 for  do
 . set i=$order(^a(i),-1)
 . if i="" break
 . write i,!

 write "*** local order with ",!
 k 
 for i=1:1:10 s a(i)=i for j=1:1:5 set a(i,j)=j+i
 set b(1)=1
 set b(2)=-1
 write "expect (next) 9 ",$order(a(""),-1),!
 write "expect (next) 1 ",$order(a("10"),-1),!
 write "expect (next) 8 ",$order(a("9"),-1),!
 write "expect (next) <empty> ",$order(a("1"),-1),!
 write "there is a scalar named the same: $data(a) ",$d(a)," a=",a,!

 write "expect 1 thru 10",!
 set i=""
 for  do
 . set i=$order(a(i),1)
 . if i="" break
 . write i,!

 write "expect 9 thru 1",!
 set i=""
 for  do
 . set i=$order(a(i),-1)
 . if i="" break
 . write "i=",i,!

 write "expect** 9 thru 1 with 5 thru 1",!
 set i=""
 for  do
 . set i=$order(a(i),-1)
 . if i="" break
 . write i,": "
 . set j=""
 . for  do
 .. set j=$order(a(i,j),-1)
 .. if j="" break
 .. write "   ",j
 . write !

 write "expect 1 thru 10 with 1 thru 5",!
 set i=""
 for  do
 . set i=$order(a(i),1)
 . if i="" break
 . write i,": "
 . set j=""
 . for  do
 .. set j=$order(a(i,j),1)
 .. if j="" break
 .. write "   ",j
 . write !

 write "expect*** 1 thru 10 with 5 thru 1",!
 set i=""
 for  do
 . set i=$order(a(i),1)
 . if i="" break
 . write i,": "
 . set j=""
 . for  do
 .. set j=$order(a(i,j),-1)
 .. if j="" break
 .. write "   ",j
 . write !

 write "expect 10 thru 9 with 1 thru 5",!
 set i=""
 for  do
 . set i=$order(a(i),-1)
 . if i="" break
 . write i,": "
 . set j=""
 . for  do
 .. set j=$order(a(i,j),1)
 .. if j="" break
 .. write "   ",j
 . write !

 k ^a
# write !,"Naked indicator global array check (not functional)",!
# set ^a(1,2)=77
# set ^a(1,3)=100
# write "expect 77: ",^(2),!
# set ^(2)=888
# write "expect 888: ",^(2),!

 write !,"Merge tests on globals",!
 for i=1:1:9 set ^m(i)="mmm"_i for j=1:1:9 set ^m(i,j)="m"_(i+j)
 merge ^n(1,2)=^m(3+1)
 write !,"expect m5 m6 ... m13",!
 for i=1:1:9 w ^n(1,2,i)," "
 write !!,"expect m4 m5 ... m12",!
 merge ^p=^m(3)
 for i=1:1:9 write ^p(i)," "
 write !

 ; too confusing - works but disabled
 ; read "read with prompt - enter something: ",a
 ; write "you wrote ",a,!

 write !,"Kill test",!
 k ^a
 for i=1:1:10 s ^a(i)=i
 kill ^a(5)
 write !,"expect 6   ",$n(^a(4)),!
 set i=1
 set j=2
 write !,"expect 1 1   ",$d(i)," ",$d(j),!
 kill i,j
 write "expect 0 0   ",$d(i)," ",$d(j),!
 set i=1,j=2,k=3
 write !,"expect 1 1 1   ",$d(i)," ",$d(j)," ",$d(k),!
 kill (i,k)
 write "expect 1 0 1   ",$d(i)," ",$d(j)," ",$d(k),!
 set i=10
 set j="i"
 kill @j
 write "expect 0   ",$d(i),!

 write !,"Hang test for 1 second",!
 hang 1
 write "Was that 1 second?",!

 write !,"ascending for loop (1 to 10): " for i=1:1:10 w i," "
 write !,"descending for loop (10 to 1): " for i=10:-1:1 w i," "
 write !

 write !,"Horolog of ",$zd," is ",$h,!
 write "$zd ",$zd,!
 write "$zd1 - seconds since Jan 1, 1970: ",$zd1,!
 write "$zd2($zd1): ",$zd2($zd1),!
 write "$zd3(1998,11,25) (day of year) ",$zd3(1998,11,25),!
 write "$zd4(1998,329) (Nov 25 1998) ",$zd4(1998,329),!
 write "$zd5(1998,11,25) ",$zd5(1998,11,25),!
 write "$zd6 ",$zd6,!
 write "$zd7 ",$zd7,!
 write "$zd8 ",$zd8,!

 write !,"$select() ",!
 write "expect c   ",$select(0:"a",0:"b",1:"c",0:"d"),!
 set i=1,j=0
 set x="c"
 write "expect c   ",$select(j:"a",j:"b",i:"c",j:"d"),!
 write "expect c   ",$select(i-i:"a",i-i:"b",i:"c",i-i:"d"),!
 write "expect c   ",$select(i-i:"a",i-i:x,i:x,i-i:"d"),!
 set x="cccccccccc"
 write "expect cccccccccc   ",$select(i-i:"a",i-i:x,i:x,i-i:"d"),!
 write "expect cccccccccc   ",$select(i-i:"a",i-i:x,j+1:x,i-i:"d"),!
 write "expect a   ",$select(1:"a",i-i:x,j+1:x,i-i:"d"),!

 write !
 set i="HTML"
 HTML This is an &~i~ test &!
 HtMl This is an &~i~ test &!

 Write !,"New style comment test",!  // this is a comment

 write !,"New command *** ",!
 set i=99
 write "initial i (expect 99)=",i,!
 do
 . write "in block before New i (expect 99)=",i,!
 . new
 . set i=100
 . write "in block after ""new"" i (expect 100)=",i,!
 write "new after block i (expect 99)=",i,!
 set i=99
 do
 . write "in block i(expect 99)=",i,!
 . new i
 . set i=100
 . write "after ""new i"" i(expect 100)=",i,!
 write "after block i(expect 99)=",i,!
 set i=99,j=100
 do
 . write "in block i(expect 99)=",i," j(expect 100)=",j,!
 . new (i)
 . set i=200
 . set j=300
 write "after block and ""new (i)"" i(expect 200)=",i," j(expect 100)=",j,!

 write !,"$text() test - expect 3 lines of code ",!
 for i=0:1:2 write ?10,i," ",$text(txt+i),!
 goto nxt

txt ;; text line 0
 ;; text line 1
 ;; text line 2
 ;; text line 3

nxt   set i=1,j=2,k=3

 set b=1
 set c=2
 set aa(1,2)="test array"
 set a=aa(b,c)
 write "Array test expect ""test array"" twice: ",a," ",aa(b,c),!

 write !,"Block test",!
 write "expect outer followed by 5 inners etc",!
 for j=1:1:5 do
 . write "I am an outer block ",j,!
 . for i=1:1:5 do
 .. write "I am an inner block ",i,!
 .. quit
 . quit
 write "I am not a block",!

# lock

 lock ^k(1,2)
 write !,"Lock [deprecated - use PsotgreSQL facilities]",$t,!

# indirection can be used with IF, SET and WRITE only.

 write !,"Indirection...",!
 set i="2*3"
 set %=@i
 write "@""2*3"" expect 6",%,!
 set ^a(1)=99
 set i="^a(1)+1"
 set %=@i
 write "@",i,"expect 100 => ",%,!
 set i="^a(j)"
 set j=10
 set @i=999
 set %=@i
 write "expect 999 ",%,!
 write "expect yes: " if @i=999 write "yes",!
 write "expect 999: ",@i,!

 write !,"Xecute tests",!
 write "expect 2",!
 set a="set i=1 set i=i+1 write i,!"
 xecute a
 write "expect 1 thru 10",!
 set a="for i=1:1:10 write i,!"
 xecute a

 write !,"Extrinsic tests ",!
 write "loop call to extrinsic with parameter - expect 11,12,13,14,15,16",!
 for i=10:1:15 write $$fcn^ext1.mps(i),!

 write "loop call to extrinsic without parameter - expect 10,11,12,13,14,15",!
 for i=10:1:15 write $$^ext2.mps,!

 write "quitting",!
 quit

test1 set i=12345
 quit "xxx"_i

test2(a,b,c)      ; function
 quit a+b+c

test4(a,b,c)      ; fucntion
 write "function test",!
 write a,!
 write b,!
 write c,!
 quit

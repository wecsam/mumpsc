#!/usr/bin/mumps
 s abcde="|||"
 w "---------------------------------",!
# s abcde="a|bb|||"
# s x=$p(abcde,"|",2)
# w "xxx",x,"xxx",!
 s abcde="a|ff|||"
 s x=$p(abcde,"|",2)
 w "xxx",x,"xxx",!
# w "---------------------------------",!
# halt

#"|" compart many data, such asxxx|yyy|zzzz|abc|...#
 
 w "x : ",abcde,!
 w "...",$piece(abcde,"|",1),"...",!
 w "...",$piece(abcde,"|",2),"...",!
 w "...",$piece(abcde,"|",3),"...",!
 w "...",$piece(abcde,"|",4),"...",!

 w "---------------------------------",!
 s a="a.b.c.e.f.g.h.i.j.k"
 f i=1:1:9 w i," ",$p(a,".",i),!
 w "---------------------------------",!
 f i=1:1:10 w i," ",$p(a,".",i),!
 w "---------------------------------",!
 f i=1:1:12 w i," ",$p(a,".",i),!
 w "---------------------------------",!
 f i=1:1:10 f j=i:1:10 w i," ",j," ",$p(a,".",i,j),!
 w "---------------------------------",!

 s a="a.b.c.d.e.f.g.h.i.j.k"
 s $p(a,".",3)="XXX" w a,!
 s a="a.b.c.d.e.f.g.h.i.j.k"
 w "read setpiece insert: "
 read $p(a,".",3)
 w "result: ",a,!
 s a="a.b.c.d.e.f.g.h.i.j.k"
 w "read setpiece insert: "
 read $p(a,".",3,5)
 w "result: ",a,!
 halt

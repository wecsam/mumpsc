#!/usr/bin/mumps
# The sql commands are ignored by the native file handler

	for i=$o(%globals(i)) do
	. w i,!
	. sql drop table &~i~ ;

	sql/f

	kill ^a
	sql/f a 4

	for i=1:1:10 s ^a(i)=i for j=1:1:5 set ^a(i,j)=j for k=1:1:5 set ^a(i,j,k)=k

	write !,"$zzmax()",!!
	write "expect 10",?65,$zzmax(^a),!
	write "expect 5",?65,$zzmax(^a(3)),!
	write "expect 5",?65,$zzmax(^a(3,2)),!

	kill ^a

	sql/f a 4
	for i=1:1:10 s ^a(i)=i for j=1:1:5 set ^a(i,j)=j for k=1:1:5 set ^a(i,j,k)=-k

	write !,"$zzmin()",!!
	write "expect -5",?65,$zzmin(^a),!
	write "expect -5",?65,$zzmin(^a(3)),!
	write "expect -5",?65,$zzmin(^a(3,2)),!

	write !,"$zzmultiply()",!!

	sql/f d 3
	sql/f e 3

	set ^d("1","1")=2
	set ^d("1","2")=3
	set ^d("2","1")=1
	set ^d("2","2")=-1
	set ^d("3","1")=0
	set ^d("3","2")=4

	set ^e("1","1")=5
	set ^e("1","2")=-2
	set ^e("1","3")=4
	set ^e("1","4")=7
	set ^e("2","1")=-6
	set ^e("2","2")=1
	set ^e("2","3")=-3
	set ^e("2","4")=0

	set %=$zzMultiply(^d,^e,^f)

	write !,"---------------------------"
	for i=$order(^d(i)) do
	. write !
	. for j=$order(^d(i,j)) write $j(^d(i,j),3)

	write !,"---------------------------"
	write !,"          TIMES"
	write !,"---------------------------"

	for i=$order(^e(i)) do
	. write !
	. for j=$order(^e(i,j)) write $j(^e(i,j),3)

	write !,"---------------------------"
	write !,"          EQUALS"
	write !,"---------------------------"

	for i=$order(^f(i)) do
	. write !
	. for j=$order(^f(i,j)) write $j(^f(i,j),4)

	write !,"---------------------------",!

	write !,"$zzsum() ",!!

	write "expect 6",?65,$zzsum(^e),!
	write "expect 14",?65,$zzsum(^e(1)),!
	write "expect 0",?65,$zzsum(^e(1,2)),!

	write !,"$zztranspose()",!

	k ^f
	set %=$zztranspose(^e,^f)

	for i=$order(^f(i)) do
	. write !
	. for j=$order(^f(i,j)) write $j(^f(i,j),4)
	write !

	write !,"$idf()",!!
	kill ^a
	set ^a("now")=2
	set ^a("is")=5
	set ^a("the")=6
	set ^a("time")=3
	set j=4
	set %=$zzIDF(^a,j)
	write "expect:",?65,"is 0.7",!,?65,"now 2.0",!,?65,"the 0.4",!,?65,"time 1.4",!!
	for i="":$order(^a(i)):"" write i," ",^a(i),!

	sql/f A 3
	sql/f B 3

	write !,"$termcorrelate()",!
	kill ^A,^B

	write "---------",!

	set ^A("1","computer")=5
	set ^A("1","data")=2
	set ^A("1","program")=6
	set ^A("1","disk")=3
	set ^A("1","laptop")=7
	set ^A("1","monitor")=1

	set ^A("2","computer")=5
	set ^A("2","printer")=2
	set ^A("2","program")=6
	set ^A("2","memory")=3
	set ^A("2","laptop")=7
	set ^A("2","language")=1

	set ^A("3","computer")=5
	set ^A("3","printer")=2
	set ^A("3","disk")=6
	set ^A("3","memory")=3
	set ^A("3","laptop")=7
	set ^A("3","USB")=1

	set ^B(22)=""
	set %=$zzTermCorrelate(^A,^B)

	write !,"Expect (sample of output):",!
	write "computer",!
	write "         USB 1",!
	write "         data 1",!
	write "         disk 2",!
	write "         language 1",!
	write "         laptop 3",!
	write "         memory 2",!
	write "         monitor 1",!
	write "         printer 2",!
	write "         program 2",!
	write "--------------------------",!

	for i="":$order(^B(i)):"" do
	. write i,!
	. for j="":$order(^B(i,j)):"" do
	.. write ?10,j," ",^B(i,j),!

	write !,"$zzdoccorrelate() Cosine",!

	set %=$zzDocCorrelate(^A,^B,"Cosine",.5)

	write "Expect:",!
	write "1",!
	write "         2 0.887096774193548",!
	write "         3 0.741935483870968",!
	write "2",!
	write "         1 0.887096774193548",!
	write "         3 0.701612903225806",!
	write "3",!
	write "         1 0.741935483870968",!
	write "         2 0.701612903225806",!
	write "------------------------------",!

	for i="":$order(^B(i)):"" do
	. write i,!
	. for j="":$order(^B(i,j)):"" do
	.. write ?10,j," ",^B(i,j),!


        kill ^A,^B

        set ^A("1")=3
        set ^A("2")=2
        set ^A("3")=1
        set ^A("4")=0
        set ^A("5")=0
        set ^A("6")=0
        set ^A("7")=1
        set ^A("8")=1

        set ^B("1")=1
        set ^B("2")=1
        set ^B("3")=1
        set ^B("4")=0
        set ^B("5")=0
        set ^B("6")=1
        set ^B("7")=0
        set ^B("8")=0

	write !,"$zzCosine() expect 0.75",?65,$zzCosine(^A,^B),!

	write !,"$zzSim1() expect 6",?65,$zzSim1(^A,^B),!

	write !,"$zzDice() expect 1",?65,$zzDice(^A,^B),!

	write !,"$zzJaccard() expect 1",?65,$zzJaccard(^A,^B),!

	write !,"$zzcentroid()",!!
	write "expect 10 5s",!
	kill ^A
	for i=0:1:10 do
	. for j=1:1:10 do
	.. set ^A(i,j)=5
	set %=$zzCentroid(^A,^B)
	for i=1:1:10 write ^B(i)," "
	write !

	write !,"$zzavg()",!!
	write "expect 5.5",?65
	kill ^a
	sql/f a 4
	for i=1:1:10 set ^a(3,99,i)=i
	set i=$zzAvg(^a(3,99))
	write "average=",i,!

	write !,"$zzcount()",!!
	write "expect 10",?65
	kill ^a
	for i=1:1:10 set ^a(99,i)=i
	set i=$zzCount(^a(99))
	write i,!

#!/usr/bin/mumps

	set $ztable="labs"
	set $ztabsize=4
	sql/f

	sql begin transaction;

	for i=1:1:1000 do
	. read a
	. if '$test break
	. set a=$znoblanks(a)
	. s ptid=$p(a,"#",1)
	. s date=$p(a,"#",2)
	. s time=$p(a,"#",3)
	. s test=$p(a,"#",4)
	. s rslt=$p(a,"#",5)
	. w "."
	. set ^labs(ptid,test,date,time)=rslt

	sql commit;

	w !

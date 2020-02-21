#!/usr/bin/mumps

	set $ztable="vitals"
	set $ztabsize=7
	sql/f

	sql beging transaction;

	for i=1:1:1000 do
	. read a
	. if '$test break
	. set a=$znoblanks(a)
	. s ptid=$p(a,"#",1)
	. s date=$p(a,"#",2)
	. s time=$p(a,"#",3)
	. s sys=$p(a,"#",4)
	. s dia=$p(a,"#",5)
	. s resp=$p(a,"#",6)
	. s temp=$p(a,"#",7)
	. w "."
	. set ^vitals(ptid,date,time,sys,dia,resp)=temp

	sql commit;

	w !

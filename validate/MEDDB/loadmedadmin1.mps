#!/usr/bin/mumps

	sql begin transaction;

	for i=1:1:1000 do
	. read a
	. if '$test break
	. set a=$znoblanks(a)
	. s ptid=$p(a,"#",1)
	. s medcode=$p(a,"#",2)
	. s dose=$p(a,"#",3)
	. s date=$p(a,"#",4)
	. s time=$p(a,"#",4)
	. w "."
	. set ^medadmin(ptid,medcode,dose,date)=time

	sql commit;

	w !

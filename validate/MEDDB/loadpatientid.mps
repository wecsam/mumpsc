#!/usr/bin/mumps

	set $ztable="patientid"
	set $ztabsize=8
	sql/f

	set $ztable="ptname"
	set $ztabsize=1
	sql/f

	sql begin transaction;	

	for i=1:1:1000 do
	. read a
	. if '$test break
	. s name=$p(a,"#",4)
	. set a=$znoblanks(a)
	. s ptid=$p(a,"#",1)
	. s date=$p(a,"#",2)
	. s time=$p(a,"#",3)
	. s prefix=$p(a,"#",5)
	. s suffix=$p(a,"#",6)
	. s street=$p(a,"#",7)
	. s citystate=$p(a,"#",8)
	. s zip=$p(a,"#",9)
	. s tel=$p(a,"#",10)
	. s insurercode=$p(a,"#",11)

	. set $ztable="patientid"
	. set ^patientid(ptid,date,time,street,citystate,zip,tel,insurercode)=""

	. set $ztable="ptname"
	. set ^ptname(ptid)=name
	. write "."

	sql commit;

	write !

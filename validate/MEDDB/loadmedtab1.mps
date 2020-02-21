#!/usr/bin/mumps

	sql begin transaction;

	for i=1:1:1000 do
	. read a
	. if '$test break
	. s medname=$p(a,"#",2)
	. set a=$znoblanks(a)
	. s medcode=$p(a,"#",1)
	. s lowdose=$p(a,"#",3)
	. s highdose=$p(a,"#",4)
	. w "."
	. set ^medtab(medcode,lowdose,highdose)=medname

	sql commit;

	w !

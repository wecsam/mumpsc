#!/usr/bin/mumps

	sql begin transaction;

	set $ztable="problems"
	set $ztabsize=3
	sql/f

	for i=1:1:1000 do
	. read a
	. if '$test break
	. set a=$znoblanks(a)
	. s ptid=$p(a,"#",1)
	. s onset=$p(a,"#",2)
	. s resolv=$p(a,"#",3)
	. s dxphys=$p(a,"#",4)
	. w "."
	. set ^problems(ptid,onset,resolv)=dxphys

	sql commit;

	w !

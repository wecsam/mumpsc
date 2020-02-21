#!/usr/bin/mumps

	set $ztable="labtab"
	set $ztabsize=3
	sql/f

	sql begin transaction;

	for i=1:1:1000 do
	. read a
	. if '$test break
	. s name=$p(a,"#",2)
	. set a=$znoblanks(a)
	. s test=$p(a,"#",1)
	. s low=$p(a,"#",3)
	. s high=$p(a,"#",4)
	. set ^labtab(test,name,low)=high
	. w "."

	sql commit;

	write !

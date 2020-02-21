#!/usr/bin/mumps

	set $ztable="probtab"
	set $ztabsize=1
	sql/f

	sql begin transaction;

	for i=1:1:1000 do
	. read a
	. if '$test break
	. set a=$znoblanks(a)
	. s icd=$p(a,"#",1)
	. s dx=$p(a,"#",2)
	. w "."
	. set ^probtab(icd)=dx

	sql commit;

	w !

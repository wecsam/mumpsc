#!/usr/bin/mumps

	write "$fnumber tests and examples",!

	set i=-1234.5678
l1	write i," ",$text(l1),?70,$fn(i,"p"),!!

	set i=1234.5678
l2	write i," ",$text(l2),?70,$fn(i,"p"),!!

	set i=1234.5678
l3	write i," ",$text(l3),?70,$fn(i,"+"),!!

	set i=-1234.5678
l4	write i," ",$text(l4),?70,$fn(i,"+"),!!

	set i=-1234.5678
l5	write i," ",$text(l5),?70,$fn(i,"P"),!!

	set i=1234.5678
l6	write i," ",$text(l6),?70,$fn(i,",P"),!!

	set i=-1234.5678
l7	write i," ",$text(l7),?70,$fn(i,"P",2),!!

	set i=-1234.5678
l8	write i," ",$text(l8),?70,$fn(i,"P",2),!!

	set i=1234.5678
i9	write i," ",$text(i9),?70,$fn(i,",T+",2),!!

	set i=-1234.5678
i9	write i," ",$text(i9),?70,$fn(i,",T+",2),!!

	write "$Fnumber using strfmon",!!

	set x=12345.6789
i10	write x," ",$test(i10),?70,$fn(x,"*%!n"),!
	write x," ",$test(i10+1),?70,$fn(x,"*%n"),!
	write x," ",$test(i10+2),?70,$fn(x,"*%i"),!
	write x," ",$test(i10+3),?70,$fn(x,"*%.3n"),!
	write x," ",$test(i10+4),?70,$fn(x,"*%20n"),!
	write x," ",$test(i10+5),?70,$fn(x,"*%=*#15n"),!
	set x=-x write x," ",$test(i10+6),?70,$fn(x,"*%(!n"),!

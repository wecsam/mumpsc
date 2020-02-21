#!/usr/bin/mumps

	write "begin multi-depts fcn calls",!
	set i=5
	set i=$$factor(1)
	write "expect 3: ",i,!
	halt

factor(a)
	quit a+$$f1(1)

f1(b)
	quit b*2

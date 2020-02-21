#!/usr/bin/mumps

	for i=1:1:10000 do
	. set j=$$add(i)
	. write j," ",!
	halt

add(a)
	set a=a+1
        quit a

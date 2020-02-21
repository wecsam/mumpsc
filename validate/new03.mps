#!/usr/bin/mumps
        set i=10
        set j=20
        set k=30
        do test1
        write "Main: expect 11 22 30 50: ",i," ",j," ",k," ",y,!
        halt

test1	write "test1: expect 10 20 30: ",i," ",j," ",k,!
	new (i,j)
        set i=11,j=22,k=33,y=50
	do test2
	write "test1: expect 11 23 34 55 : ",i," ",j," ",k," ",y,!
        quit

test2	write "test2: expect 11 22 33 50: ",i," ",j," ",k," ",y,!
	new i
	set i=12,j=23,k=34,y=55
	write "test2: expect 12 23 34 55 : ",i," ",j," ",k," ",y,!
	quit

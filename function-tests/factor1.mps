#!/usr/bin/mumps

	write "factor1.mps",!
	set i=$$factorial(5)
	write "expect 5: ",i,!
	halt

factorial(a)
	write "factorial entry parameter: ",a,!
        if a<2 quit 1
        quit a*$$factorial(a-1)

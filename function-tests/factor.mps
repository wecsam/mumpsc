#!/usr/bin/mumps
factorial(a)
	write "factorial entry parameter: ",a,!
        if a<2 quit 1
        quit a*$$factorial(a-1)

#!/usr/bin/mumpsRO

	hang 1
	set x=0
	for i=1:1:100 set x=x+1
	write "proc ",$job," ",x,!

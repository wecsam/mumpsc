#!/usr/bin/mumps
# calls.mps

	set i=10
	do fcn(i)
	do fcn(5)
	do $$fcn(i)
	do $$fcn(5)
	set k=$$fcn(5)
	write "returned k=",k,!

	set i=10
	do fcn^ext.mps(i)
	do fcn^ext.mps(5)
	do $$fcn^ext.mps(i)
	do $$fcn^ext.mps(5)
	set k=$$fcn^ext.mps(5)
	write "returned k=",k,!

	do fcn^ext1.mps
	do fcn^ext1.mps
	do $$fcn^ext1.mps
	do $$fcn^ext1.mps
	set k=$$fcn^ext1.mps
	write "returned k=",k,!

	halt

fcn(x) write "in fcn(x) value passed is ",x,!
       quit x

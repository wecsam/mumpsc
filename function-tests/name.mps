#!/usr/bin/mumps

	kill ^a
	set ^a(1,2,3,4)=4
	set i=1,j=2,k=3,m=4
	w $name(^a(i,j,k,m)),!
	w $name(^a(i,j,k,^a(1,2,3,4))),!

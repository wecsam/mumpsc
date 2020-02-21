#!/usr/bin/mumps

	for i=1:1:10 s a(i)=i for j=1:1:5 set a(i,j)=j
	write $order(a("")),!
	write $order(a(1,"")),!
	for i=1:1:10 w i," ",$order(a(i)),! for j=1:1:5 write i," ",j," ",$order(a(i,j)),!
	for i=$order(a(i)) w i,!
	for j=$order(a(1,j)) w j,!

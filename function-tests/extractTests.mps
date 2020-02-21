#!/usr/bin/mumps

# extract and tests

	write "$extract tests",!
	set $e(x)="Z"
	write "$e(x)=Z x does not exist:    ",x,!

	set x="123456789"
	set $e(x,5)="abc"
	write "$e(x,5)=abc x=123456789:     ",x,!

	kill x
	set $e(x,5)="abc"
	write "$e(x,5)=abc x not exist:     ",x,!

	s x="123456789"
	s $e(x,3,5)="abc"
	write "$e(x,3,5)=abc, x=123456789:  ",x,!

	s x="123456789"
	s $e(x,8,10)="abc"
	write "$e(x,8,10)=abc, x=123456789: ",x,!

	s x="123"
	s $e(x,8,10)="abc"
	write "$e(x,8,10)=abc, x=123:       ",x,!

	s ^a(1)=123456789
	s i="3-1"
	s $e(^a(@i))="abc"
	write "$e(^a(@i))=abc  ^a=12...89   ",^a(@i),!

	k ^a
	s i="4-1"
	s $e(^a(@i))="abc"
	write "$e(^a(@i))=abc  ^a=nada      ",^a(@i),!

	s i="3-1"
	s ^a(@i)=123456789
	set $e(^a(@i),5)="abc"
	write "$e(^a(2),5)=abc x=1..9:      ",^a(@i),!

	s i="3-1"
	s ^a(@i)=123
	set $e(^a(@i),5)="abc"
	write "$e(^a(2),5)=abc x=123:       ",^a(@i),!

	kill ^a
	s i="3-1"
	set $e(^a(@i),5)="abc"
	write "$e(^a(2),5)=abc not exist    ",^a(@i),!

	s ^a(1)="123456789"
	s $e(^a(1),3,5)="abc"
	write "$e(^a(1),3,5)=abc, x=1..9:   ",^a(1),!

	s ^a(1)="123456789"
	s $e(^a(1),8,10)="abc"
	write "$e(^a(1),8,10)=abc, x=1..9:  ",^a(1),!

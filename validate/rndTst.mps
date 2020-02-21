#!/usr/bin/mumps

#	sql/f
	k ^a
	sql start transaction;
	for i=0:1:99 s ^a(i)=0
	sql commit;
	sql begin;
	for i=1:1:%1 do
	. r j
	. if '$t break
	. set ^a(j)=^a(j)+1
	sql commit;

	for i=$o(^a(i)) write ^a(i),!
	halt

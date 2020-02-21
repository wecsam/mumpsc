#!/usr/bin/mumps

	write "$query $qlength $qsubscript ",!!
	s a(1,2,3)=99
	s a(1,2,4)=98
	s a(1,2,5)=97

	s x="a"
	s x=$query(@x)
	w "expect a(1,2,3) ",x,!
	s x=$query(@x)
	w "expect a(1,2,4) ",x,!
	s x=$query(@x)
	w "expect a(1,2,5) ",x,!

	w "$qlength expect 3 ",$qlength(@x),!

	s ^a(1)=3
	s b(1)=3
	s i=3
	w "numeric index  expect 5 ",$qsubscript(@x,3),!
	w "char index     expect 5 ",$qsubscript(@x,"3"),!
	w "variable index expect 5 ",$qsubscript(@x,i),!
	w "expr index     expect 5 ",$qsubscript(@x,1+2),!
	w "global index   expect 5 ",$qsubscript(@x,^a(1)),!
	w "array index    expect 5 ",$qsubscript(@x,b(1)),!

	write "=========================",!

	k ^a

	s ^a(1,2,3)=99
	s ^a(1,2,4)=98
	s ^a(1,2,5)=97

	s x="^a"
	s x=$query(@x)
	w "expect ^a(1,2,3) ",x,!
	s x=$query(@x)
	w "expect ^a(1,2,4) ",x,!
	s x=$query(@x)
	w "expect ^a(1,2,5) ",x,!

	w "$qlength expect 3 ",$qlength(@x),!

	s i=3
	s ^b(1)=3
	w "var index   expect 5 ",$qsubscript(@x,i),!
	w "const index expect 5 ",$qsubscript(@x,3),!
	w "char index  expect 5 ",$qsubscript(@x,"3"),!
	w "expr index  expect 5 ",$qsubscript(@x,1+2),!
	w "gbl  index  expect 5 ",$qsubscript(@x,^b(1)),!
	w "array index expect 5 ",$qsubscript(@x,b(1)),!

	write "=========================",!

	write "string indices testing",!

	kill

	s a("a1","a2","a3")=99
	s a("a1","a2","a4")=98
	s a("a1","a2","a5")=97

	s x="a"
	s x=$query(@x)
	w "expect a(a1,a2,a3) ",x,!
	s x=$query(@x)
	w "expect a(a1,a2,a4) ",x,!
	s x=$query(@x)
	w "expect a(a1,a2,a5) ",x,!

	w "$qlength expect 3 ",$qlength(@x),!

	s ^a(1)=3
	s b(1)=3
	s i=3
	w "numeric index  expect a5 ",$qsubscript(@x,3),!
	w "char index     expect a5 ",$qsubscript(@x,"3"),!
	w "variable index expect a5 ",$qsubscript(@x,i),!
	w "expr index     expect a5 ",$qsubscript(@x,1+2),!
	w "global index   expect a5 ",$qsubscript(@x,^a(1)),!
	w "array index    expect a5 ",$qsubscript(@x,b(1)),!

	write "=========================",!

	k ^a

	s ^a("a1","a2","a3")=99
	s ^a("a1","a2","a4")=98
	s ^a("a1","a2","a5")=97

	s x="^a"
	s x=$query(@x)
	w "expect ^a(a1,a2,a3) ",x,!
	s x=$query(@x)
	w "expect ^a(a1,a2,a4) ",x,!
	s x=$query(@x)
	w "expect ^a(a1,a2,a5) ",x,!

	w "$qlength expect 3 ",$qlength(@x),!

	s i=3
	s ^b(1)=3
	w "var index    expect a5 ",$qsubscript(@x,i),!
	w "const index  expect a5 ",$qsubscript(@x,3),!
	w "char index   expect a5 ",$qsubscript(@x,"3"),!
	w "expr index   expect a5 ",$qsubscript(@x,1+2),!
	w "gbl  index   expect a5 ",$qsubscript(@x,^b(1)),!
	w "array index  expect a5 ",$qsubscript(@x,b(1)),!
	w "nested qfcn  expect a5 ",$qsubscript(@x,$qlength(@x)),!
	w "+nested qfcn expect a5 ",$qsubscript(@x,$qlength($query(^a))),!

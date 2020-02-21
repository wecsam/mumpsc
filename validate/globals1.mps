#!/usr/bin/mumps
      write "global stress test",!
      write "killing old data ....",!

	for i=$o(%globals(i)) do
	. w i,!
	. sql drop table &~i~ ;

      sql/f

      set t1=$zd1
      set iter=100
      set seed=$r(10000)+1
      set %=$zsrand(seed)
      set (a,b,c)=0
      write "begin store ...",!
      for i=1:1:iter do
      . write:i#100=0 "Store Iteration ",i,!
      . for j=1:1:iter do
      .. set a=$r(100000)
      .. set b=$r(10000)
      .. set c=$r(1000)
      .. set ^a(a,b,c)=a+b+c

      set %=$zsrand(seed)
      set (a,b,c)=0
      write "begin retrieve ...",!
      for i=1:1:iter do
      . write:i#100=0 "Retrieve Iteration ",i,!
      . for j=1:1:iter do
      .. set a=$r(100000)
      .. set b=$r(10000)
      .. set c=$r(1000)
      .. if ^a(a,b,c)'=(a+b+c) do
      ... write "error ",i," ",a," ",b," ",c," ",^a(a,b,c)," ",(i+j),!
      ... halt

      write "done ",$zd1-t1,!

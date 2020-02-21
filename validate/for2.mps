#!/usr/bin/mumps
#
#     for's with do's
#
      write "*** 1 to 10",!
      for i=1:1:10 do
      . write i," "
      write !
      write "*** -5 to 5 by 1",!
      for i=-5:1:5 do
      . write i," "
      write !
      write "*** 2 to 20 by 2",!
      for i=2:2:20 do
      . write i," "
      write !
      write "*** 10 to 1",!
      for i=10:-1:1 do
      . write i," "
      write !
      write "*** 5 to -5",!
      for i=5:-1:-5 do
      . write i," "
      write !
      write "*** 1 to 5, 10 to 15",!
      for i=1:1:5,10:1:15 do
      . write i," "
      write !
      write "*** 10 to 5, 0 to -5",!
      for i=10:-1:5,0:-1:-5 do
      . write i," "
      write !
      write "*** 10 to 5, 5 to 10",!
      for i=10:-1:5,5:1:10 do
      . write i," "
      write !
      write "*** loop until quit: 1 to 10",!
      set j=0
      for i=1:1 q:i>10 do
      . write i," "
      write !
      write "*** nested loop 1 100 to 3 102",!
      for i=1:1:3 for j=100:1:102 do
      . write i," ",j," "
      write !
      write "*** nested loop",!
      for i=1:1:2 for j=100:1:101 for k=200:1:202 do
      . write i," ",j," ",k," "
      write !
      write "*** nested loop with quit (1 100 200) to (2 100 202)",!
      for i=1:1:2 for j=100:1:101 quit:j>100  for k=200:1:202 do
      . write i," ",j," ",k," "
      write !
      write "*** singles: 1 3 5 9",!
      for i=1,3,5,9 do
      . write i," "
      write !
      write "*** singles: 1 3 5 9 99 to 95",!
      for i=1,3,5,9,99:-1:95 do
      . write i," "
      write !
      write "*** singles: 20 to 25, 1 3 5 9, 99 to 95",!
      for i=20:1:25,1,3,5,9,99:-1:95 do
      . write i," "
      write !

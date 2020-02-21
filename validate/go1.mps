#!/usr/bin/mumps
	zmain
l1      write "*** 1 2 3 4 5",!
        goto s1
l2      write "*** 1 2 3 4 5",!
        goto:1=1 s2
l3      write "*** 1 2 3 4 5",!
        do abc:1=1
l4      write "*** 1 2 3 4 5",!
        goto:1=1 s4:1=1
l5      write "*** 1 2 3 4 5",!
        goto:1=0 s5:1=1 do abc
l6      write "*** 1 2 3 4 5",!
        goto:1=1 s6:1=0 do abc
l7	goto s7
l8      write "*** 1 2 3 4 5 10 11 12 13 14 15",!
        goto s8,def
l9      write "*** 1 2 3 4 5 10 11 12 13 14 15",!
        goto:1=1 s9,def
l10     write "*** 1 2 3 4 5 10 11 12 13 14 15",!
        goto:1=1 s10,def:1=1
l11     write "*** 1 2 3 4 5 10 11 12 13 14 15",!
        goto:1=1 s11:1=1,def:1=1
l12     write "*** 1 2 3 4 5",!
l13	set i="1 2 3 4 5"
        do ^remote.mps
        halt

s1   for i=1:1:5 write i," " write ! goto l2
s2   for i=1:1:5 write i," " write ! goto l3
s3   for i=1:1:5 write i," " write ! goto l4
s4   for i=1:1:5 write i," " write ! goto l5
s5   for i=1:1:5 write i," " write ! goto l6
s6   for i=1:1:5 write i," " write ! goto l7
s7   for i=1:1:5 write i," " write ! goto l8
s8   for i=1:1:5 write i," " write ! goto l9
s9   for i=1:1:5 write i," " write ! goto l10
s10   for i=1:1:5 write i," " write ! goto l11
s11   for i=1:1:5 write i," " write ! goto l12
s12   for i=1:1:5 write i," " write ! goto l13
abc   write "hello world",! quit
def   for i=10:1:15 write i," "
      write !
      halt

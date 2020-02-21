#!/usr/bin/mumps

 k ^a
 k ^b

 f i=1:1:10 f j=1:1:10 s ^a(i,j)=i

 merge ^b=^a(1)

 w !,$d(^b(1)),!

 k ^a
 k ^b

 f i=1:1:10 f j=1:1:10 s ^a(i,j)=i

 merge ^b=^a

 w !,$d(^b(1)),!

 f i=1:1:10 f j=1:1:10 w ^b(i,j)," "
 w !

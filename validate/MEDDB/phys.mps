#!/usr/bin/mumps

      write "use medical;",!
      write "drop table if exists physicians;",!
      write "create table physicians ( physician_code int, physician_name varchar(100) ); ",!
      set names=1
      open 1:"names,old"
      use 1
      for  do
      . use 1
      . read a
      . i '$t break
      . s ^names(names)=a
      . use 5
      . write "insert into physicians values ( ",names,", "
      . write "'",a,"' );",!
      . set names=names+1
      set names=names-1
      set ^Phys(0)=names
      close 1

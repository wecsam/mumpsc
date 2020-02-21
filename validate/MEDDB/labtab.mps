#!/usr/bin/mumps

      write "use medical;",!
      write "drop table if exists labtab;",!
      write "create table labtab (test_code int, test_name varchar(100), low_limit int, high_limit int);",!
      open 1:"labnames,old"
      use 1
      set labs=1
      for  do
      . use 1
      . read a
      . i '$t break
      . use 5
      . write "insert into labtab values ( ",labs,", '",a,"', "
      . write $r(50),", ",50+$r(40)," );",!
      . set labs=labs+1
      close 1

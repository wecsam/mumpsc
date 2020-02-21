#!/usr/bin/mumps

      write "use medical;",!
      write "drop table if exists medtab;",!
      write "create table medtab (medication_code int, medication varchar(100), low_dose int, high_dose int); ",!
      open 1:"meds,old"
      use 1
      set mc=10000
      for  do
      . use 1
      . read a
      . i '$t break
      . use 5
      . write "insert into medtab values ( ",mc,", "
      . set mc=mc+1
      . write "'",a,"', "
      . write $r(20)+1,", ",40+$r(60),");",!
      close 1

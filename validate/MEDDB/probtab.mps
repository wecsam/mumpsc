#!/usr/bin/mumps

      write "use medical;",!
      write "drop table if exists probtab;",!
      write "create table probtab (icd_code int, diagnosis varchar(100)); ",!
      open 1:"ICDTab.txt,old"
      use 1
      for  do
      . use 1
      . read a
      . i '$t break
      . use 5
      . write "insert into probtab values ( ",$p(a," ",1),", '"
      . write $p(a," ",2),"' );",!
      close 1

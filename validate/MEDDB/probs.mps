#!/usr/bin/mumps

      s i=$zsrand(7777)

      open 1:"dates,old"
      use 1
      set date=1
      for  do
      . read a
      . i '$t break
      . s ^dates(date)=a
      . set date=date+1
      set date=date-1
      close 1

      open 1:"time,old"
      use 1
      set time=1
      for  do
      . read a
      . i '$t break
      . s ^time(time)=a
      . set time=time+1
      set time=time-1
      close 1

      open 1:"ICDTab.txt,old"
      use 1
      set icd=1
      for  do
      . read a
      . i '$t break
      . s ^icd(icd)=a
      . s icd=icd+1
      set icd=icd-1
      close 1

      set names=1
      open 1:"names,old"
      use 1
      for  do
      . read a
      . i '$t break
      . s ^names(names)=a
      . set names=names+1
      set names=names-1
      close 1

      use 5

      if '$d(%2) %2=5

      write "use medical;",!
      write "drop table problems;",!
      write "create table problems (ptid char(10), icd_code char(10), onset date, "
      write "resolved date, physician_code int);",!

      for k=1:1:%2 do
      . set ptid=100000
      . for i=1:1:^ptcount(0) do
      .. set ptid=ptid+1000
      .. write "insert into problems values ( '",ptid,"', "
      .. set icdx=$p(^icd($r(icd)+1)," ",1)
      .. write "'",icdx,"', "
      .. write "'",^dates($r(date)+1),"', "
      .. write "'",^dates($r(date)+1),"', "
      .. set dx=$r(names)+1
      .. write dx," );",!
      .. set ^pdx(ptid,dx)=""
      .. set ^picd(ptid,icdx)=""

#!/usr/bin/mumps

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

      use 5
      write "use medical;",!
      write "drop table if exists officeVisit;",!
      write "create table officeVisit ( ptid char(10), physician_code int, date date, time time, transaction int);",!
      for %=1:1:10 do
      . set ptid=100000
      . for i=1:1:^ptcount(0) do
      .. set tran=^Tran(0) set ^Tran(0)=^Tran(0)+1
      .. set ptid=ptid+1000
      .. write "insert into officeVisit values ( '",ptid,"', "

      .. set kk=0
      .. for k=$o(^pdx(ptid,k)) s kk=kk+1
      .. for k=$o(^pdx(ptid,k)) if $r(kk)=0 break
      .. if k="" s k=$o(^pdx(ptid,""))

      .. write k,", "
      .. write " '",^dates($r(date)+1),"', "
      .. write " '",^time($r(time)+1),"', ",tran,"); ",!
      .. write "insert into insuranceBill values('",ptid,"',",$r(200)+1,".",$r(100),", ",tran," );",!

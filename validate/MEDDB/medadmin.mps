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

      open 1:"meds,old"
      use 1
      set mc=1
      for  do
      . use 1
      . read a
      . i '$t break
      . set ^meds(mc)=a
      . set mc=mc+1
      set mc=mc-1
      close 1

      use 5
      write "use medical;",!
      write "drop table if exists medadmin;",!
      write "create table medadmin ( ptid char(10), medication_code int, dose int, admin_date date, admin_time time, transaction int, icd_code int );",!
      for %=1:1:10 do
      . set ptid=100000
      . for i=1:1:^ptcount(0) do
      .. set ptid=ptid+1000

      .. set kk=0
      .. for k=$o(^picd(ptid,k)) s kk=kk+1
      .. for k=$o(^picd(ptid,k)) if $r(kk)=0 break
      .. if k="" s k=$o(^picd(ptid,""))

      .. set tran=^Tran(0) set ^Tran(0)=^Tran(0)+1
      .. write "insert into medadmin values ( '",ptid,"', "
      .. write $r(mc)+1,", "
      .. write $r(200),", "
      .. write " '",^dates($r(date)+1),"', "
      .. write " '",^time($r(time)+1),"', ",tran,", ",k,"); ",!

      .. write "insert into insuranceBill values('",ptid,"',",$r(1000)+1,".",$r(100),", ",tran," );",!

#!/usr/bin/mumps

      set i=$zsrand(7777)
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

      open 1:"labnames,old"
      use 1
      set labs=1
      for  do
      . read a
      . i '$t break
      . s ^labs(labs)=a
      . s labs=labs+1
      set labs=labs-1
      close 1

      use 5

      write "use medical;",!
      write "drop table if exists labs;",!
      write "create table labs (ptid char(10), test_date date, test_time time, test_name int, result int, icd_code int, transaction int); ",!

      for %=1:1:10 do
      . set ptid=100000
      . for i=1:1:^ptcount(0) do
      .. set ptid=ptid+1000
      .. set tran=^Tran(0) set ^Tran(0)=^Tran(0)+1
      .. write "insert into labs values ( "
      .. write "'",ptid,"', "
      .. set d=^dates($r(date)+1)
      .. set t=^time($r(time)+1)
      .. write "'",d,"', "
      .. write "'",t,"', "
      .. write $r(labs)+1,", "

      .. set kk=0
      .. for k=$o(^picd(ptid,k)) s kk=kk+1
      .. for k=$o(^picd(ptid,k)) if $r(kk)=0 break
      .. if k="" s k=$o(^picd(ptid,""))

      .. write $r(100),", ",k,", ",tran," );",!

      .. write "insert into insuranceBill values('",ptid,"',",$r(1000)+1,".",$r(100),", ",tran," );",!

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
      write "drop table if exists vitals;",!
      write "create table vitals (ptid char(10), date_taken date, time_take time, systolic int, "
      write " diastolic int, pulse int, respiration int, temperature int ); ",!

      for k=1:1:20 do
      . set ptid=100000
      . for i=1:1:^ptcount(0) do
      .. set ptid=ptid+1000
      .. write "insert into vitals values ( '",ptid,"', "
      .. write "'",^dates($r(date)+1),"', "
      .. write "'",^time($r(time)+1),"', "
      .. write 50+$r(70),", "
      .. write 70+$r(150),", "
      .. write 50+$r(70),", "
      .. write 10+$r(20),", "
      .. write 96+$r(10),");",!


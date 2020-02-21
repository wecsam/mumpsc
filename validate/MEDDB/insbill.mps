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

      open 1:"insurance,old"
      use 1
      for  do
      . read a
      . i '$t break
      . s code=$p(a," ",1)
      . s ins=$p(a," ",2,99)
      . s ^insurance(code)=ins
      close 1

      use 5
      write "use medical;",!
      write "drop table patientId;",!
      write "create table insuranceBill (ptid char(10), date date, time time, amount float, insurer char(10) );",!


      set ptid=100000
      for i=1:1:1000 do
      . set ptid=ptid+1000
      . write "insert into insuranceBill values ( '",ptid,"', "
      . write " '",^dates($r(date)+1),"', "
      . write " '",^time($r(time)+1),"', "
      . write " '",^names($r(names)+1),"', "
      . set pre=$r(2)
      . if pre=1 write "'Mr.', "
      . else write "'Ms.', "
      . set pre=$r(3)+1
      . if pre=1 write "'Jr.', "
      . if pre=2 write "'Sr.', "
      . if pre>2 write "NULL, "
      . write !
      . write "'",$r(999)+1," ",^streets($r(streets)+1)," "
      . s x=$r(3)
      . if x=0 write "Rd. "
      . if x=1 write "Lane "
      . if x=2 write "Ave. "
      . s x=$r(3)
      . if x=0 write "Apt ",$r(99)+1,"', "
      . else write "', "
      . write "'",^city($r(city)+1),"', "
      . for  set x=$r(99999) if x>999 quit
      . write "'",x,"', "
      . for  set a=$r(999) if a>99 quit
      . for  set b=$r(999) if b>99 quit
      . for  set c=$r(9999) if c>999 quit
      . write "'(",a,") ",b,"-",c,"' ); ",!
      
      

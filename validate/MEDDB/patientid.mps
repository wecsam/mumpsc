#!/usr/bin/mumps

      open 1:"city,old"
      use 1
      set city=1
      for  do
      . read a
      . i '$t break
      . s ^city(city)=a
      . set city=city+1
      set city=city-1
      close 1

      set ins=1
      for i=$o(^insurance(i)) set ins=ins+1

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

      open 1:"streets,old"
      use 1
      set streets=1
      for  do
      . read a
      . i '$t break
      . s ^streets(streets)=a
      . s streets=streets+1
      set streets=streets-1
      close 1

      if '$d(%2) set ptcount=1000
      else  set ptcount=+%2

      set ^ptcount(0)=ptcount

      use 5
      write "use medical;",!
      write "drop table if exists patientId;",!
      write "create table patientId (ptid char(10), entry_date date, entry_time time, name varchar(100), "
      write "prefix char(3), suffix char(3), street varchar (100), city_state varchar(100), zip char(5), "
      write "tel char(20), insurer_code char(10) );",!
      set ptid=100000
      for i=1:1:ptcount do
      . set ptid=ptid+1000
      . write "insert into patientId values ( '",ptid,"', "
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
      . write "'(",a,") ",b,"-",c,"' , "
      . set k=1
      . for x=$o(^insurance(x)) set z(k)=x set k=k+1
      . set k=$r(k-1)+1
      . write "'",z(k),"' );",!

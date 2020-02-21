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
      write "drop table if exists patientId;",!
      write "drop table if exists insurers;",!
      write "create table insurers (insurer_code char(10), insurer varchar(100), primary key (insurer_code) );",!
      for i=$o(^insurance(i)) do
      . write "insert into insurers values ('",i,"', '",^insurance(i),"');",!

      write !,"drop table if exists insuranceBill;",!

      write "create table insuranceBill (ptid char(10), amount float, transaction int, primary key (transaction), foreign key (ptid) references patientId );",!

      set ^Tran(0)=1

      zmain
      set flg=0
      set flg1=0

      for  do
      . read a
      . if '$test break
      . if a="" do

      .. if flg write ");"
      .. write !,"insert into demographic values ("
      .. set flg=1
      .. set flg1=0

      . else  do
      .. set b=$p(a," ",2,99)
      .. if flg1 write ", "
      .. set flg1=1
      .. write "'",b,"' "

      write ");",!
      halt
      

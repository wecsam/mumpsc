#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#+   
#+     Mumps Web Software Library
#+     Copyright (C) 2000 by Kevin C. O'Kane  
#+
#+     Kevin C. O'Kane
#+     anamfianna@earthlink.net
#+     okane@cs.uni.edu
#+
#+
#+ This program is free software; you can redistribute it and/or modify
#+ it under the terms of the GNU General Public License as published by
#+ the Free Software Foundation; either version 2 of the License, or
#+ (at your option) any later version.
#+ 
#+ This program is distributed in the hope that it will be useful,
#+ but WITHOUT ANY WARRANTY; without even the implied warranty of
#+ MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#+ GNU General Public License for more details.
#+ 
#+ You should have received a copy of the GNU General Public License
#+ along with this program; if not, write to the Free Software
#+ Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#+
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

      zmain
      zd #include <mumpsc/cgi.h>
      znumber

      html Content-type: text/html &!&!<html>

      html <head><title>Mumps Web Folders</title></head>
      html <body vlink=darkblue link=darkblue bgcolor=silver>&!
      html <!-- Mumps Web Folders, Copyright (C) 2001 Kevin C. O'Kane &!
      html Mumps Web Folders comes with ABSOLUTELY NO WARRANTY; &!
      html This is free software, and you are welcome to redistribute it&!
      html under certain conditions as set forth in the GNU GPL -->&!

      if '$data(^count(1)) set ^count(1)=1 set ^date(1)=$zd set date=$zd
      else  set ^count(1)=^count(1)+1 set date=^date(1)
      if '$data(ml) set ml=1

      if '$data(array) set array="lib"
      set %1="<a href=""index.cgi?array="_array_"&ml="
      set %2="<a href="
      set cls="<img align=top src=""folder03.gif"" border=0>"

      set lev=1,bx=0,ep=0,c(0)=""

      for i=0:1:20 do
      . set b(i)=""
      . set x="a"_i
      . set a(i)=""
      . if $data(@x) set b(i)=@x,ep=i

      html <font size=-1>
      html <center><font color=green>Kevin O'Kane's Web Index</font></center><hr>
      do layer
      html <center>
      html <hr><font size=-2>Page accesses since &~date~ : &~^count(1)~
      html <br>Copyright (c) 2001 Kevin C. O'Kane
      html <br><a href=http://www.cs.uni.edu/~okane target=_top>HOME</a>
      html </center>
      html </body></html>
      halt

layer set x(lev)="^"_array_"("
      set AFLG=0

      for i=1:1:lev do
      . set x(lev)=x(lev)_"a("_i_")"
      . if i'=lev set x(lev)=x(lev)_","

      set x(lev)=x(lev)_")"

      set a(lev)=-1

      if b(lev)'="",lev<ml do
      . set a(lev)="-1"

a1    set a(lev)=$next(@x(lev))

a0    if a(lev)=-1 set lev=lev-1 quit

      set p="array="_array

      if lev>bx do parm1

      set n="<br>"
      for i=1:1:lev-1 set n=n_"&nbsp;&nbsp;&nbsp;&nbsp;"

      if $data(@x(lev))>1,ml>lev,b(lev)=a(lev) do
      . write n," ",!,%1,lev
      . do parm
      . Html ">
      . Html <img align=middle src="folder05.gif" border=0>&!
      . set AFLG=1
      . goto a3a

      if $data(@x(lev))=1,lev=ml do
      . write n
      . set n=""
      . goto a3a

      if $data(@x(lev))'=1 do
      . write n,%1,lev+1
      . do parm
      . write """>",cls
      . set AFLG=1

a3a   if AFLG do tok
      if 'AFLG do
      . if $extract(@x(lev),1,1)="@" do
      .. set p=$extract(@x(lev),2,100)

      . write %2,p
      . html >
      . if $data(@x(lev))=1 html &~n~&nbsp;<img src=blueball.gif border=0 align=top>&nbsp;
      . do tok
      . Html </a>

      if lev<ml do

      . if $data(@x(lev))>1,b(lev)=a(lev) do
      .. if $extract(@x(lev),1,1)="@" do
      ... set p=$extract(@x(lev),2,100)
      .. write %2,p
      .. Html >
      .. Html </a>&!

      if @x(lev)="" goto a2a
      set x=@x(lev)

      if lev<ml goto a2a ; print only low level

      if $extract(x,1,1)="@" do
      . set x=$extract(x,2,255)

a2a   if lev>bx do parm1

      if $data(@x(lev))>1,ml>lev,b(lev)=a(lev) do
      . set lev=lev+1
      . do layer
      . goto a1

      goto a1

parm  for i=1:1:lev quit:a(i)=-1  write "&a",i,"=",$zh(a(i))
      quit

tok   write !,$piece(a(lev)," ",2,99)
      if AFLG html </a>
      quit

parm1 set bx=lev
      for i=1:1:lev set c(i)=a(i)
      quit



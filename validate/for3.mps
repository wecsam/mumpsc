#!/usr/bin/mumps
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#+   
#+     Mumps Compiler Example Code
#+     Copyright (C) A.D. 2000, 2001, 2002 by Kevin C. O'Kane  
#+
#+     Kevin C. O'Kane
#+     Department of Computer Science
#+     University of Northern Iowa
#+     Cedar Falls, IA 50613-0507 USA
#+
#+     okane@cs.uni.edu
#+     anamfianna@earthlink.net
#+     http://www.cs.uni.edu/~okane
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

#
#     terminating for's
#
      write "*** 1 to 10",!
      for i=1:1:20 q:i>10  write i," "
      write !
      write "*** 1 to 10",!
      for i=1:1 q:i>10  write i," "
      write !
      write "*** 1 to 10",!
      for i=1,2,3,4,5,6,7,8,9,10,11 q:i>10  write i," "
      write !
      write "*** 1 to 10",!
      for i=1:1:20 write i," " if i>9 quit
      write !
      write "*** 1 3 5 7 9",!
      for i=1:1:10 if i#2 write i," "
      write !
      write "*** 1 to 10",!
      for i=1:1:10 do
      . write i," "
      write !
      write "*** 1 to 5",!
      for i=1:1:10 do  if i>4 quit
      . write i," "
      write !
      write "*** 1 to 5",!
      for i=1:1:10 do  quit:i>4
      . write i," "
      write !
      write "*** 1 to 5",!
      for i=1:1:10 do
      . write i," "
      . if i>4 break
      write !
      write "*** 1 to 5",!
      for i=1:1:10 do
      . write i," "
      . break:i>4
      write !
      write "*** 1 to 5",!
      for i=1:1 do
      . write i," "
      . break:i>4
      write !
      write "*** 1 to 5",!
      for i=1:1 do  quit:i>4
      . write i," "
      write "*** 1 to 5",!
      set i=0 for  set i=i+1 write i," " quit:i>4
      write !
      write "*** 1 to 5",!
      set i=0 for  set i=i+1 write i," " if i>4 quit
      write !
      write "*** 1 to 5",!
      set i=0 for  do
      . set i=i+1 write i," " if i>4 break
      write !
      write "*** 1 to 5",!
      set i=0 for  do  if i>4 quit
      . set i=i+1 write i," "
      write !
      write "*** 1 to 5",!
      set i=0 for  do  quit:i>4
      . set i=i+1 write i," "
      write !
      write "*** 1 to 5",!
      set i=0 for  do  quit:i>4
      . for  do
      .. set i=i+1 write i," "
      .. if i>4 break
      write !
      write "*** 1 to 5",!
      for  do  quit:i>4
      . for i=1:1:5  do
      .. write i," "
      write !
      write "*** 1 to 5",!
      if 1=1 for i=1:1:5 write i," "
      write !
      write "*** 1 to 5",!
      if 1=1 do
      . for i=1:1:5 write i," "
      write !
      write "*** 1 to 5",!
      set i="for i=1:1:5 write i,"" """
      xecute i
      write !
      write "*** 1 to 5",!
      if 1=1 for i=1:1:10 do
      . if i>5 break
      . write i," "
      write !
      write "*** 1 to 5",!
      if 1=1 for i=1:1:10 do  if i>4 quit
      . write i," "
      write !

      Zmain
      Zd #include <mumpsc/cgi.h>

# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#   
#     Web Folders
#     Copyright (C) 2000 by Kevin C. O'Kane  
#
#     Kevin C. O'Kane
#     anamfianna@earthlink.net
#     okane@cs.uni.edu
#
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#
# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


      Set lev(0)="0000\Browser Tree"
      Set ord=1000

      For  Do
      . Read cmd
      . If '$Test Break
      . If cmd="" Continue

      . For i=0:1:10 If $Extract(cmd,i+1,i+1)'="." Quit

      . For  Do
      .. If $Extract(cmd,1,1)="."!($Extract(cmd,1,1)=" ") Set cmd=$Extract(cmd,2,512) Quit
      .. Break

      . Set lev(i)=ord_" "_cmd
      . Set ord=ord+1

      . Read order      // line2

      . For  Do
      .. If $Extract(order,1,1)="."!($Extract(order,1,1)=" ") Set order=$Extract(order,2,512) Quit
      .. Break

      . Set x=""
      . For j=0:1:i-1 Set x=x_""""_lev(j)_""","
      . Set x=x_""""_lev(i)_""""
      . Set x="^lib("_x
      . Set %=x_")"

      . set order="@"_order
      . Set @%=order
      . Write %," -> ",order,!

      Halt


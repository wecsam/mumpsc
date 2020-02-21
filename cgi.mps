#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#+    Mumps Compiler Run-Time Support Functions
#+    Copyright (c) 2006 by Kevin C. O'Kane
#+    okane@cs.uni.edu
#+
#+    This library is free software; you can redistribute it and/or
#+    modify it under the terms of the GNU Lesser General Public
#+    License as published by the Free Software Foundation; either
#+    version 2.1 of the License, or (at your option) any later version.
#+
#+    This library is distributed in the hope that it will be useful,
#+    but WITHOUT ANY WARRANTY; without even the implied warranty of
#+    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#+    Lesser General Public License for more details.
#+
#+   You should have received a copy of the GNU Lesser General Public
#+    License along with this library; if not, write to the Free Software
#+    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#+
#+    http://www.cs.uni.edu/~okane
#+
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	zmain
+#include <mumpsc/cgi.h>
+ if (argc==2) $SymPut("%",argv[1]);
+ else $SymPut("%","");
	for i=1:1:10 set j=$p(%,"/",i,i+1) if $p(%,"/",i+1)="" quit
	x "do ^"_j
	halt

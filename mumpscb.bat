echo off
rem #+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
rem #+   
rem #+     Mumps Compiler 
rem #+     Copyright (C) A.D. 2004 by Kevin C. O'Kane  
rem #+
rem #+     Kevin C. O'Kane
rem #+     Department of Computer Science
rem #+     University of Northern Iowa
rem #+     Cedar Falls, IA 50613-0507 USA
rem #+
rem #+     okane@cs.uni.edu
rem #+     http://www.cs.uni.edu/~okane
rem #+
rem #+
rem #+ This program is free software; you can redistribute it and/or modify
rem #+ it under the terms of the GNU General Public License as published by
rem #+ the Free Software Foundation; either version 2 of the License, or
rem #+ (at your option) any later version.
rem #+ 
rem #+ This program is distributed in the hope that it will be useful,
rem #+ but WITHOUT ANY WARRANTY; without even the implied warranty of
rem #+ MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
rem #+ GNU General Public License for more details.
rem #+ 
rem #+ You should have received a copy of the GNU General Public License
rem #+ along with this program; if not, write to the Free Software
rem #+ Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
rem #+
rem #++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
rem
rem #+ Mumps Compiler Build for MicroSoft Visual C++
rem
rem #++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
echo on

REM
REM Compile mumps programs 
REM
mumps2c %1.mps
cl /w /I c:\mumpsc\include /O1 /EHsc %1.cpp \mumpsc\lib\mumpsblib.lib \mumpsc\lib\libdb42.lib

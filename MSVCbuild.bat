
echo off
rem #+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
rem #+   
rem #+     Mumps Compiler 
rem #+     Copyright (C) A.D. 2004 2006, 2008 by Kevin C. O'Kane  
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

copy include\db.x include\mumpsc\db.h

rem Compile mumps2c.exe - the Mumps to C translator

del mumps.obj
del parse.obj
del sys1.obj

cl /W0 /Iinclude/ /o mumps2c mumps.c parse.c sys1.c

if %errorlevel% neq 0 goto err

rem Compile the Mumps C++ personality

rem cl /DMUMPS_SYM /O1 /W0 /EHsc /Iinclude/ /c sym.cpp  

rem if %errorlevel% neq 0 goto err
rem copy sym.obj sym1.obj

rem if %errorlevel% neq 0 goto err

rem cl /O1 /W0 /EHsc /Iinclude/ /c sym.cpp  

rem if %errorlevel% neq 0 goto err
rem copy sym.obj sym2.obj

rem if %errorlevel% neq 0 goto err

del libmpscpp.obj

del sym.obj

cl /O1 /W0 /EHsc /Iinclude/ /c libmpscpp.cpp sym.cpp 

if %errorlevel% neq 0 goto err
copy sym.obj sym1.obj

del interp.obj

cl /O1 /W0 /EHsc /Iinclude/ /c interp.cpp 

if %errorlevel% neq 0 goto err

rem cl /O1 /W0 /EHsc /Iinclude/ /c pm.cpp stem.cpp arith.cpp strmanip.cpp sysfunc.cpp lock.cpp global.cpp globalb.cpp btree.cpp bifs.cpp bstring.cpp 

del pm.obj 
del stem.obj 
del arith.obj 
del strmanip.obj 
del sysfunc.obj 
del lock.obj 
del globalb.obj 
del btree.obj 
del bifs.obj 
del bstring.obj 

cl /O1 /W0 /EHsc /Iinclude/ /c pm.cpp stem.cpp arith.cpp strmanip.cpp sysfunc.cpp lock.cpp globalb.cpp btree.cpp bifs.cpp bstring.cpp 

if %errorlevel% neq 0 goto err

rem Compile the Mumps runtime support libraries

cl /O1 /W0 /c /Iinclude/ bmgsubs.c rdbms-if.c 

if %errorlevel% neq 0 goto err

del include\mumpsc\db.h

rem Build the object module library

lib /OUT:pcre.lib pcre_chartables.obj pcre_compile.obj pcre_config.obj pcre_dfa_exec.obj pcre_exec.obj pcre_fullinfo.obj pcre_get.obj pcre_globals.obj pcre_info.obj pcre_maketables.obj pcre_ord2utf8.obj pcre_refcount.obj pcre_study.obj pcre_tables.obj pcre_try_flipped.obj pcre_ucp_searchfuncs.obj pcre_valid_utf8.obj pcre_version.obj pcre_xclass.obj

if %errorlevel% neq 0 goto err

lib /OUT:mumpslib1.lib interp.obj pm.obj stem.obj arith.obj strmanip.obj sym.obj sysfunc.obj lock.obj bmgsubs.obj globalb.obj btree.obj bifs.obj rdbms-if.obj bstring.obj libmpscpp.obj

if %errorlevel% neq 0 goto err

rem lib /OUT:mumpslib2.lib interp.obj pm.obj stem.obj arith.obj strmanip.obj sym2.obj sysfunc.obj lock.obj bmgsubs.obj globalb.obj btree.obj bifs.obj rdbms-if.obj bstring.obj libmpscpp.obj

if %errorlevel% neq 0 goto err

rem lib /OUT:mumpsblib1.lib interp.obj pm.obj stem.obj arith.obj strmanip.obj sym.obj sysfunc.obj lock.obj bmgsubs.obj global.obj bifs.obj rdbms-if.obj bstring.obj libmpscpp.obj

lib /OUT:mumpsblib1.lib interp.obj pm.obj stem.obj arith.obj strmanip.obj sym.obj sysfunc.obj lock.obj bmgsubs.obj bifs.obj rdbms-if.obj bstring.obj libmpscpp.obj

if %errorlevel% neq 0 goto err

rem lib /OUT:mumpsblib2.lib interp.obj pm.obj stem.obj arith.obj strmanip.obj sym2.obj sysfunc.obj lock.obj bmgsubs.obj global.obj bifs.obj rdbms-if.obj bstring.obj libmpscpp.obj

if %errorlevel% neq 0 goto err

rem Make directories and copy files
rem Ignore duplicate directory errors

mkdir c:\mumpsc
mkdir c:\mumpsc\include
mkdir c:\mumpsc\bin
mkdir c:\mumpsc\include
mkdir c:\mumpsc\include\mumpsc
mkdir c:\mumpsc\lib
mkdir c:\mumpsc\doc
mkdir c:\mumpsc\doc\examples
mkdir c:\mumpsc\doc\examples\btree
mkdir c:\mumpsc\src
mkdir c:\mumpsc\src\include
mkdir c:\mumpsc\src\include\mumpsc
mkdir c:\mumpsc\obj

echo off
copy mumps2c.exe c:\mumpsc\bin
copy include\mumpsc\* c:\mumpsc\include\mumpsc
copy mumpslib1.lib c:\mumpsc\lib
rem copy mumpslib2.lib c:\mumpsc\lib
copy mumpsblib1.lib c:\mumpsc\lib
copy pcre.lib c:\mumpsc\lib
rem copy mumpsblib2.lib c:\mumpsc\lib
copy *.bat c:\mumpsc\bin
copy doc\*.html c:\mumpsc\doc
copy doc\examples\checkout.mps c:\mumpsc\doc\examples
copy doc\examples\checkout1.mps c:\mumpsc\doc\examples
copy doc\examples\btree\AUTHORS c:\mumpsc\doc\examples\btree
copy doc\examples\btree\COPYING c:\mumpsc\doc\examples\btree
copy doc\examples\btree\COPYING.DOCS c:\mumpsc\doc\examples\btree
copy doc\examples\btree\btest1.cpp c:\mumpsc\doc\examples\btree
copy doc\examples\btree\btest2.cpp c:\mumpsc\doc\examples\btree
copy doc\examples\btree\btest3.cpp c:\mumpsc\doc\examples\btree
copy doc\examples\btree\btest4.cpp c:\mumpsc\doc\examples\btree
copy doc\examples\btree\btest5.cpp c:\mumpsc\doc\examples\btree
copy doc\examples\btree\btest6.cpp c:\mumpsc\doc\examples\btree
copy doc\examples\btree\btest7.cpp c:\mumpsc\doc\examples\btree
copy doc\examples\btree\btest8.cpp c:\mumpsc\doc\examples\btree
copy doc\examples\btree\checkout c:\mumpsc\doc\examples\btree
copy doc\examples\btree\checkout.bat c:\mumpsc\doc\examples\btree
copy doc\examples\btree\index.html c:\mumpsc\doc\examples\btree
copy doc\*.jpg c:\mumpsc\doc
copy INSTALL_MS_MSVC c:\mumpsc
copy PCRE-LICENSE c:\mumpsc
copy *.c c:\mumpsc\src
copy *.cpp c:\mumpsc\src
copy *.mps c:\mumpsc\src
copy *.obj c:\mumpsc\obj
copy include\db.x c:\mumpsc\src\include\db.h
copy include\pcre.h c:\mumpsc\src\include
date /t > c:\mumpsc\CREATION_DATE

del dosmumps.obj 

call c:\mumpsc\bin\mumpsc dosmumps.mps
rename dosmumps.exe mumps.exe
copy mumps.exe c:\mumpsc\bin


rem Add this to your search path (PATH): c:\mumpsc\bin

echo Done, no errors
exit/b

:err
echo Errors found - not complete
exit/b

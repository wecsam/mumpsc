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

      zmain
      write !,"Operators ...",!!

      write "Test",?30,"Expected",?50,"Actual",!
      write "Unary +",?30,"27.3",?50,+"27.3 days",!
      write "Unary - ",?30,"-3.14",?50,-"3.14 radians",!
      write "Sum ",?30,"4.718",?50,2.718+"2 above e",!
      write "Difference ",?30,"-4.18",?50,2.12-"6.3 eV",!
      write "Product ",?30,"2.01588",?50,1.00794*"2 atoms/H2",!
      write "Division ",?30,"12",?50,144.132/12.011,!
      write "Integer Division ",?30,"2",?50,82.8\"29.5 years/orbit",!

      write "Modulo works like C modulo",!
      write "Modulo ",?30,"2",?50,42#5,!
      write "Modulo ",?30,"2",?50,-42#5,!
      write "Modulo ",?30,"-2",?50,42#-5,!
      write "Modulo ",?30,"-2",?50,-42#-5,!

      write "Less Than ",?30,"1",?50,1642<1879,!
      write "Less Than ",?30,"0",?50,1942<1879,!
      write "Not Less Than ",?30,"0",?50,1642'<1879,!
      write "Not Less Than ",?30,"1",?50,1942'<1879,!
      write "Greater Than ",?30,"0 ",?50,1452>1564,!
      write "Greater Than ",?30,"1 ",?50,1652>1564,!
      write "Not Greater Than ",?30,"1 ",?50,1452'>1564,!
      write "Not Greater Than ",?30,"0 ",?50,1652'>1564,!

      write "Concatenate ",?30,"Feynman 1918",?50,"Feynman "_1918,!

      write "Equals ",?30,"1",?50,1969-5=1964,!
      write "Equals ",?30,"0",?50,1967="1967: M",!
      write "Equals ",?30,"1",?50,1966=01966,!
      write "Equals ",?30,"0",?50,1966="01966",!
      write "Equals ",?30,"2",?50,"Lovelace"="Hopper"+2,!
      write "Equals ",?30,"3",?50,"Lovelace"="Lovelace"+2,!

      write "not equals ",?30,"0 ",?50,1969-5'=1964,!
      write "not equals ",?30,"1 ",?50,1967'="1967: M",!
      write "not equals ",?30,"0 ",?50,1966'=01966,!
      write "not equals ",?30,"1 ",?50,1966'="01966",!
      write "not equals ",?30,"3 ",?50,"Lovelace"'="Hopper"+2,!
      write "not equals ",?30,"2 ",?50,"Lovelace"'="Lovelace"+2,!

      write "Contains ",?30,"1 ",?50,"Darwin"["win",!
      write "Not Contains ",?30,"1 ",?50,"Darwin"["wix",!
      write "Contains ",?30,"1 ",?50,"Linnaeus"["",!

      write "Follows ",?30,"0 ",?50,"COPERNICUS"]"KEPLER",!
      write "Follows ",?30,"1 ",?50,"XOPERNICUS"]"KEPLER",!
      write "Not Follows ",?30,"1 ",?50,"COPERNICUS"']"KEPLER",!
      write "Not Follows ",?30,"0 ",?50,"XOPERNICUS"']"KEPLER",!

      write "Pattern ",?30,"0 ",?50,"Leakey"?1a,!
      write "Pattern ",?30,"1 ",?50,"Boaz"?1.a,!
      write "Pattern ",?30,"1 ",?50,"Fossey"?1u.5l,!
      write "Pattern ",?30,"0 ",?50,"Goodall"?.4l.p6c.e,!
      write "Pattern ",?30,"1 ",?50,"Maslow"?.E1"low".CNP,!
      write "Not Pattern ",?30,"1 ",?50,"Leakey"'?1a,!
      write "Not Pattern ",?30,"0 ",?50,"Boaz"'?1.a,!
      write "Not Pattern ",?30,"0 ",?50,"Fossey"'?1u.5l,!
      write "Not Pattern ",?30,"1 ",?50,"Goodall"'?.4l.p6c.e,!
      write "Not Pattern ",?30,"0 ",?50,"Maslow"'?.E1"low".CNP,!

      write "And ",?30,"0 ",?50,"Watson"&"Crick",!
      write "And ",?30,"0 ",?50,"Morgan"&1735,!
      write "And ",?30,"1 ",?50,1838&1839,!
      write "And ",?30,"1 ",?50,-12000&1996,!
      write "And ",?30,"0 ",?50,1859&0,!
      write "Not And ",?30,"1 ",?50,"Watson"'&"Crick",!
      write "Not And ",?30,"1 ",?50,"Morgan"'&1735,!
      write "Not And ",?30,"0 ",?50,1838'&1839,!
      write "Not And ",?30,"0 ",?50,-12000'&1996,!
      write "Not And ",?30,"1 ",?50,1859'&0,!

      write "Or ",?30,"0 ",?50,"Jennifer"!"Pasteur",!
      write "Or ",?30,"1 ",?50,"Hoffman"!1928,!
      write "Or ",?30,"1 ",?50,1898!-400,!
      write "Or ",?30,"1 ",?50,1867!0,!
      write "Not Or ",?30,"1 ",?50,"Jennifer"'!"Pasteur",!
      write "Not Or ",?30,"0 ",?50,"Hoffman"'!1928,!
      write "Not Or ",?30,"0 ",?50,1898'!-400,!
      write "Not Or ",?30,"0 ",?50,1867'!0,!

      set a=3
      set a=a**2
      write "exponentiation ",?30,"9",?50,a,!
      set a=9
      set a=a**.5
      write "exponentiation ",?30,"3",?50,a,!

      write "Not ",?30,"1 ",?50,'"Turing",!
      write "Not ",?30,"0",?50,''"Babbage",!
      write "Not ",?30,"1 ",?50,'"Backus"&1957,!
      write "Not ",?30,"1 ",?50,'("Wirth"&"Codd"),!

      write "Indirection",?30,"123",?50,@"100+23",!


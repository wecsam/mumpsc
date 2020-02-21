/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#+   
#+     Mumps Compiler Example Code
#+     Copyright (C) A.D. 2000, 2001, 2002, 2003, 2004 by Kevin C. O'Kane  
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
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <mumpsc/libmpscpp.h>

/*..........................................................................
#############################################################################
# Example program to collect, store, and retrieve lab tests in a global array
#############################################################################

strt	Read !!,"Enter Patient ID or <cr> to quit: ",ptid

	If ptid="" Write "bye",!! Halt

	Read "Enter R for Retrieve or S to store: ",op

	If op="S"!(op="s") Do
	. Write "For patient ",ptid," enter test name: " Read test
	. Write "For patient ",ptid," enter date: " Read date
	. Write "For patient ",ptid," enter result: " Read rslt
	. Set ^patient(ptid,test,date)=rslt
	. Write "For patient ",ptid," test ",test," date ",date," result ",rslt," stored",!!
	. Goto strt

	If op="R"!(op="r") Do
	. If $Data(^patient(ptid))=0 Write "Patient not found",! Goto strt
	. Write !,"For patient ",ptid,!!
	. Set test=-1
	. For i=1:1 Do
	.. Set test=$Next(^patient(ptid,test))
	.. If test=-1 Break
	.. Set date=-1
	.. For j=1:1 Do
	... Set date=$Next(^patient(ptid,test,date))
	... If date=-1 Break
	... Write ptid,?10,test,?20,date,?40,^patient(ptid,test,date),!
	. Goto strt

err	Write "Sorry, code not recognized",!
	Goto strt

..........................................................................*/

/*#############################################################################
# Example program to collect, store, and retrieve lab tests in a global array
#############################################################################*/

global patient("patient");

int main () {

mstring ptid,op,test,date,rslt;

while (1) {

      cout << endl << endl << "Read Patient ID or -1 to quit: ";
      cin >> ptid;
      if (ptid == "-1") { cout << "bye" << endl; break; }

	cout << "Enter R for Retrieve or S to store: ";
      cin >> op;

	if ( op == "S" || op == "s" ) {
	      cout << "For patient " << ptid << " enter test name: ";
            cin >> test;
	      cout << "For patient " << ptid << " enter date: ";
            cin >> date;
	      cout << "For patient " << ptid << " enter result: ";
            cin >> rslt;
	      patient(ptid,test,date) = rslt;
	      cout << "For patient " << ptid << " test " << test << " date " << date 
                  << " result " << rslt << " stored" << endl << endl;
            continue;
            }

	if ( op == "R" || op == "r" ) {
	      if ( patient(ptid).Data() == 0) { cout << "Patient not found" << endl; continue; }
	      cout << endl << "For patient " << ptid << endl << endl;
	      test = "";
            while (1) {
	            test=$order(patient(ptid,test),1);
	            if ( test == "") break;
	            date = "";
                  while (1) {
	                  date = $order(patient(ptid,test,date),1);
	                  if ( date == "" ) break;
	                  cout << ptid << "\t" << test << "\t" << date << "\t" << patient(ptid,test,date) << endl;
                        }
                  }
            }
      }

GlobalClose;

return EXIT_SUCCESS;
}

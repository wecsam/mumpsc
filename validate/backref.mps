#!/usr/bin/mumps

   write !,"Testing Perl backrefs",!
   Write "Please enter a telephone number:",!
   Read phonenum
   write "entered: ",phonenum,!

   If $zperlmatch(phonenum,"^(1-)?(\(?\d{3}\)?)?(-| )?\d{3}-?\d{4}$") Do
   . Write "+++ This looks like a phone number.",!
   . If $data($2) Write "The area code is: ",$2,!
   . Halt

   Write "--- This didn't look like a phone number.",!
   Halt


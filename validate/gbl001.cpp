#include <mumpsc/libmpscpp.h>

global gbl("gbl");

int main () {

// test of globals
// gbl001.cpp
// http://threadsafebooks.com/

int i, j=10;
string a = "10", b = "20", c = "30";

gbl().Kill();

gbl(a,b,c) = 10;

i = gbl(a,b,c) + 20;
cout << "expect 30 " << i << endl;  // prints 30

i = 20 + gbl(a,b,c);
cout << "expect 30 " << i << endl;  // prints 30

i = gbl(a,b,c) / j;
cout << "expect 1 " << i << endl;  //prints 1

i = gbl(a,b,c) * 2;
cout << "expect 20 " << i << endl;  // prints 20

gbl(a,b,c) ++;
cout << "expect 11 " << gbl(a,b,c) << endl;  // prints 11

gbl(a,b,c) --;
cout << "expect 10 " << gbl(a,b,c) << endl;  // prints 10

i = ++ gbl(a,b,c);
cout << "expect 11 11 " << i << " " << gbl(a,b,c) << endl;  // prints 11

i = gbl(a,b,c) ++;
cout << "expect 11 12 " << i << " " << gbl(a,b,c) << endl;  // prints 11 12

gbl(a,b,c) += 10;
cout << "expect 22 " << gbl(a,b,c) << endl;  // prints 22

gbl(a,b,c) -= 10;
cout << "expect 12 " << gbl(a,b,c) << endl;  // prints 12

gbl(a,b,c) *= 2;
cout << "expect 24 " << gbl(a,b,c) << endl;  //prints 24

gbl(a,b,c) /= 2;
cout << "expect 12 " << gbl(a,b,c) << endl;  // prints 12

GlobalClose;
return 0;
}


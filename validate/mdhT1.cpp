#include <mumpsc/libmpscpp.h>

int main() {

// example of assignment to mstring
// http://threadsafebooks.com/

mstring x;

x = 10;         cout << x << endl;
x = 10.99;      cout << x << endl;
x = "test";     cout << x << endl;


string a1="abcdef";
float  a2=99.9;
double a3=99.8;
int    a4=99;
short  a5=98;
char   a6[]="abcdef";
global a7("a7"); a7("1")=99;

x = a1;         cout << x << endl;
x = a2;         cout << x << endl;
x = a3;         cout << x << endl;
x = a4;         cout << x << endl;
x = a5;         cout << x << endl;
x = a6;         cout << x << endl;
x = a7("1");    cout << x << endl;


GlobalClose;

return EXIT_SUCCESS;

}

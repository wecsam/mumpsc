#include <mumpsc/libmpscpp.h>

int main() {

// mdhT2.cpp - example mstring operators.
// http://threadsafebooks.com/

mstring x;
mstring y;
mstring z;

y = 1;

x = 10;

cout << "expect 11 " << x + 1 << endl;
cout << "expect  9 " << x - 1 << endl;
cout << "expect 20 " << x * 2 << endl;
cout << "expect  5 " << x / 2 << endl;
cout << "expect  1 " << x % 3 << endl;
cout << "expect 11 " << x + y << endl;

cout << "-----\n";

x = 10; x = x + 1;     cout << "expect  11 " << x << endl;
x = 10; x = x - 1;     cout << "expect   9 " << x << endl;
x = 10; x = x * 2;     cout << "expect  20 " << x << endl;
x = 10; x = x / 2;     cout << "expect   5 " << x << endl;
x = 10; x = x % 3;     cout << "expect   1 " << x << endl;
x = 10; x = x + y;     cout << "expect  11 " << x << endl;
x = 10; x = y + x;     cout << "expect  11 " << x << endl;


cout << "-----\n";

x = 10; x += 1;     cout << "expect  11 " << x << endl;
x = 10; x -= 1;     cout << "expect   9 " << x << endl;
x = 10; x *= 2;     cout << "expect  20 " << x << endl;
x = 10; x /= 2;     cout << "expect   5 " << x << endl;
x = 10; x %= 3;     cout << "expect   1 " << x << endl;

cout << "-----\n";

x=10; x += y;     cout << "expect  11 " << x << endl;
x=10; x -= y;     cout << "expect   9 " << x << endl;
x=10; x *= y;     cout << "expect  10 " << x << endl;
x=10; x /= y;     cout << "expect  10 " << x << endl;
x=10; x %= y;     cout << "expect   0 " << x << endl;

cout << "-----\n";

x = 10; x = 1 + x + y;   cout << "expect  12 " << x << endl;
x = 10; x = 1 - x + y;   cout << "expect - 8 " << x << endl;
x = 10; x = 1 * x + y;   cout << "expect  11 " << x << endl;
x = 10; x = 1 / x + y;   cout << "expect 1.1 " << x << endl;

cout << "-----\n";

x = 10; x = 1 + ( x + y ); cout << "expect  12 " << x << endl;
x = 10; x = (x + y)  + ( x + y ); cout << "expect  22 " << x << endl;

x = 10; cout << "expect 11 " << ++x ;
        cout <<  " expect 11 " << x << endl;
x = 10; cout << "expect 10 " << x++ ;
        cout << " expect 11 " << x << endl;
x = 10; cout << "expect  9 " << --x ;
        cout << " expect  9 " << x << endl;
x = 10; cout << "expect 10 " << x-- ;
        cout << " expect  9 " << x << endl;

cout << "-----\n";

x = 10; cout << "expect yes "; if ( x == 10 ) cout << "yes\n";
x = 10; cout << "expect yes "; if ( x >= 10 ) cout << "yes\n";
x = 10; cout << "expect yes "; if ( x <= 10 ) cout << "yes\n";
x = 10; cout << "expect yes "; if ( x >= 9 ) cout << "yes\n";
x = 10; cout << "expect yes "; if ( x > 9 ) cout << "yes\n";

x = 10; cout << "expect no "; if ( x != 10 ) cout << "yes\n"; else cout << "no\n";
x = 10; cout << "expect no "; if ( x > 10 ) cout << "yes\n"; else cout << "no\n";
x = 10; cout << "expect no "; if ( x < 10 ) cout << "yes\n"; else cout << "no\n";
x = 10; cout << "expect no "; if ( x <= 9 ) cout << "yes\n"; else cout << "no\n";
x = 10; cout << "expect no "; if ( x < 9 ) cout << "yes\n"; else cout << "no\n";

cout << "-----\n";

x = "test message";
cout << "expect \"test message\" " << x << endl;

cin >> x;
cout << "expect what you typed " << x << endl;

x = "test ";
y = "message";

z = x || y;
cout << "expect \"test message\" " << z << endl;

x = x || x || x;
cout << "expect \"test test test\" " << x << endl;

x = "test";
z = y = (x || " test");
cout << "expect \"test test test test\" " << y << " " << z << endl;

x = "test";
z = y = x = x || " test";
cout << "expect \"test test test test\" " << y << " " << z << endl;
cout << "expect \"test test\" " << x << endl;


GlobalClose;

return EXIT_SUCCESS;

}

#include <mumpsc/libmpscpp.h>

global t("t");

int main() {

// gbl002.cpp

int a;
float b;
mstring c;
mstring x;
char d[100];

t().Kill();

x=50; t(x)=99;

a=t(x).Int();
cout << "expect 99 " << a << endl;

b=t(x).Double();
cout << "expect 99 " << b << endl;

c=t(x).Mstring();
cout << "expect 99 " << c << endl;

t(x).Char(d,100);
cout << "expect 99 " << d << endl;

GlobalClose;
}


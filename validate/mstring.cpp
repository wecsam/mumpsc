#include <mumpsc/libmpscpp.h>

global x("x"), y("y");

int main() {

mstring a,b,c="99";
char t[100];
string s;

cout << "expect 99 " << c << endl;

cout << "assignment to mstring tests\n";
c=99;
cout << "expect 99 " << c << endl;
c="99";
cout << "expect 99 " << c << endl;
c=99.0;
cout << "expect 99 " << c << endl;
strcpy(t,"99"); 
c=t;
cout << "expect 99 " << c << endl;
s="99";
c=s;
cout << "expect 99 " << c << endl;
b=99;
c=b;
cout << "expect 99 " << c << endl;

cout << "expect 99 " << c << endl;
cout << "decrement expect 99 " << c-- << endl;
cout << "expect 98 " << c << endl;
cout << "decrement expect 97 " << --c << endl;
cout << "expect 97 " << c << endl;

c=100;
cout << "expect 100 " << c << endl;
cout << "increment expect 100 " << c++ << endl;
cout << "expect 101 " << c << endl;
cout << "increment expect 102 " << ++c << endl;
cout << "expect 102 " << c << endl;

cout << "add operations " << endl;

c=100;
c=c+1;
cout << "expect 101 " << c << endl;
c=100;
c=c+1.0;
cout << "expect 101 " << c << endl;
c=100;
c=c+"1";
cout << "expect 101 " << c << endl;
c=100;
b=1;
c=c+b;
cout << "expect 101 " << c << endl;
c=100;
s="1";
c=c+s;
cout << "expect 101 " << c << endl;
c=100;
s="1";
c=c+s;
cout << "expect 101 " << c << endl;
c=100;
strcpy(t,"1.0");
c=c+t;
cout << "expect 101 " << c << endl;
c=100;
c=1+c;
cout << "expect 101 " << c << endl;
c=100;
c=1.0+c;
cout << "expect 101 " << c << endl;
c=100;
c="1"+c;
cout << "expect 101 " << c << endl;
c=100;
b=1;
c=b+c;
cout << "expect 101 " << c << endl;
c=100;
s="1";
c=s+c;
cout << "expect 101 " << c << endl;
c=100;
s="1";
c=s+c;
cout << "expect 101 " << c << endl;
c=100;
strcpy(t,"1.0");
c=t+c;
cout << "expect 101 " << c << endl;
c=100;
x("100")=1;
c=c+x("100");
cout << "expect 101 " << c << endl;
c=100;
x("100")=1;
c=x("100")+c;
cout << "expect 101 " << c << endl;

c=100;
c+=1;
cout << "expect 101 " << c << endl;

c=100;
c+="1";
cout << "expect 101 " << c << endl;

c=100;
c+=1.0;
cout << "expect 101 " << c << endl;

c=100;
s="1";
c+=s;
cout << "expect 101 " << c << endl;

c=100;
strcpy(t,"1");
c+=t;
cout << "expect 101 " << c << endl;


//==========================================
c=100;
c=c-1;
cout << "expect 99 " << c << endl;
c=100;
c=c-1.0;
cout << "expect 99 " << c << endl;
c=100;
c=c-"1";
cout << "expect 99 " << c << endl;
c=100;
b=1;
c=c-b;
cout << "expect 99 " << c << endl;
c=100;
s="1";
c=c-s;
cout << "expect 99 " << c << endl;
c=100;
s="1";
c=c-s;
cout << "expect 99 " << c << endl;
c=100;
strcpy(t,"1.0");
c=c-t;
cout << "expect 99 " << c << endl;
c=100;
c=1-c;
cout << "expect -99 " << c << endl;
c=100;
c=1.0-c;
cout << "expect -99 " << c << endl;
c=100;
c="1"-c;
cout << "expect -99 " << c << endl;
c=100;
b=1;
c=b-c;
cout << "expect -99 " << c << endl;
c=100;
s="1";
c=s-c;
cout << "expect -99 " << c << endl;
c=100;
s="1";
c=s-c;
cout << "expect -99 " << c << endl;
c=100;
strcpy(t,"1.0");
c=t-c;
cout << "expect -99 " << c << endl;
c=100;
x("100")=1;
c=c-x("100");
cout << "expect 99 " << c << endl;
c=100;
x("100")=1;
c=x("100")-c;
cout << "expect -99 " << c << endl;
//========================================
c=100;
c=c*2;
cout << "expect 200 " << c << endl;
c=100;
c=c*2.0;
cout << "expect 200 " << c << endl;
c=100;
c=c*"2";
cout << "expect 200 " << c << endl;
c=100;
b=2;
c=c*b;
cout << "expect 200 " << c << endl;
c=100;
s="2";
c=c*s;
cout << "expect 200 " << c << endl;
c=100;
s="2";
c=c*s;
cout << "expect 200 " << c << endl;
c=100;
strcpy(t,"2.0");
c=c*t;
cout << "expect 200 " << c << endl;
c=100;
c=2*c;
cout << "expect 200 " << c << endl;
c=100;
c=2.0*c;
cout << "expect 200 " << c << endl;
c=100;
c="2"*c;
cout << "expect 200 " << c << endl;
c=100;
b=2;
c=b*c;
cout << "expect 200 " << c << endl;
c=100;
s="2";
c=s*c;
cout << "expect 200 " << c << endl;
c=100;
s="2";
c=s*c;
cout << "expect 200 " << c << endl;
c=100;
strcpy(t,"2.0");
c=t*c;
cout << "expect 200 " << c << endl;
c=100;
x("100")=2;
c=c*x("100");
cout << "expect 200 " << c << endl;
c=100;
x("100")=2;
c=x("100")*c;
cout << "expect 200 " << c << endl;
//================================================
c=100;
c=c/2;
cout << "expect 50 " << c << endl;
c=100;
c=c/2.0;
cout << "expect 50 " << c << endl;
c=100;
c=c/"2";
cout << "expect 50 " << c << endl;
c=100;
b=2;
c=c/b;
cout << "expect 50 " << c << endl;
c=100;
s="2";
c=c/s;
cout << "expect 50 " << c << endl;
c=100;
s="2";
c=c/s;
cout << "expect 50 " << c << endl;
c=100;
strcpy(t,"2.0");
c=c/t;
cout << "expect 50 " << c << endl;
c=100;
c=200/c;
cout << "expect 2 " << c << endl;
c=100;
c=200/c;
cout << "expect 2 " << c << endl;
c=100;
c="200"/c;
cout << "expect 2 " << c << endl;
c=100;
b=200;
c=b/c;
cout << "expect 2 " << c << endl;
c=100;
s="200";
c=s/c;
cout << "expect 2 " << c << endl;
c=100;
s="200";
c=s/c;
cout << "expect 2 " << c << endl;
c=100;
strcpy(t,"200.0");
c=t/c;
cout << "expect 2 " << c << endl;
c=100;
x("100")=2;
c=c/x("100");
cout << "expect 50 " << c << endl;
c=2;
x("100")=100;
c=x("100")/c;
cout << "expect 50 " << c << endl;

c="now is the time for all good";
cout << "expect is " << c.Extract(5,6) << endl;

cout << "expect 7 " << c.Find("is") << endl;
b="is";
cout << "expect 7 " << c.Find(b) << endl;

c=12.34567;
cout << "expect ......12.34567 " << c.Justify(14) << endl;
cout << "expect 12 " << c.Justify(2,0) << endl;
cout << "expect 12.35 " << c.Justify(5,2) << endl;

c="abcd";
cout << "expect 4 " << c.Length() << endl;
cout << "expect 2 " << c.Length("bc") << endl;
b="bc";
cout << "expect 2 " << c.Length(b) << endl;

c="ABCDEF";
cout << "expect 65 " << c.Ascii() << endl;
cout << "expect 66 " << c.Ascii(2) << endl;

c="aaa.bbb.ccc.ddd.eee.fff";
cout << "expect aaa " << c.Piece(".",1) << endl;
b=".";
cout << "expect aaa " << c.Piece(b,1) << endl;

cout << "expect aaa.bbb " << c.Piece(".",1,2) << endl;
b=".";
cout << "expect aaa.bbb " << c.Piece(b,1,2) << endl;

c="abcdef";
b="wxyz";
a=c || b;
s="123";
strcpy(t,"999");
cout << "concatenate expect abcdefwxyz " << a << endl;
cout << "concatenate expect abcdefwxyz " << (c || b) << endl;
cout << "concatenate expect abcdef123 " << (c || s) << endl;
cout << "concatenate expect abcdef999 " << (c || t) << endl;
cout << "concatenate expect wxyz999 " << (b || 999) << endl;

cout << "concatenate expect 123abcdef " << (s || c) << endl;
cout << "concatenate expect 999abcdef " << (t || c) << endl;

mstring i,j,k;

x().Kill();

for (i=1; i<10; i++) x(i)=i;
cout << "global average expect 5 " << x().Avg() << endl;

for (i=1; i<10; i++) for (j=1; j<6; j++) x(i,j)=j;
cout << "global centroid expect 1 2 3 4 5" << endl;
x().Centroid(y);
for (j=1; j<6; j++) cout << y(j) << " "; cout << endl;

cout << "global count expect 54 " << x().Count() << endl;


GlobalClose;

return 0;
}

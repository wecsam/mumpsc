#include <mumpsc/libmpscpp.h>

global A("A");

int main() {

// gbl004.cpp

mstring i,j;

cout << "this will be slow if using MySQL or PostgreSQL" << endl;

A().Kill();

for (i=0; i<1000; i++)
      for (j=1; j<10; j++) {
                  A(i,j) = j;
                  }

cout << "expect 5 " << A("100").Avg() << endl; // average of nodes below A("100")
cout << "expect 5 " << A().Avg() << endl;      // average of all nodes

GlobalClose;

return 0;
}


#include <mumpsc/libmpscpp.h>
global a("a");

// gbl003.cpp

int main() {

      long i;
      a().Kill();

      a("1") = "now is the time";

cout << "expect error message" << endl; 

try {
      i = a("1");
      }

catch ( ConversionException ce) {
      cout << ce.what() << endl;
      }

cout << "expect error message" << endl; 

try {
      i = a("22");
      }

catch (GlobalNotFoundException nf) {
      cout << nf.what() << endl;
      }

      GlobalClose;

      return 0;
}


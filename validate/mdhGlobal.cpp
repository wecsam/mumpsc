#include <mumpsc/libmpscpp.h>

int main() {

global a("a");
mstring i,j;

 a().Kill();

for (i=0; i<100; i++) a(i)=i;
for (i=0; i<100; i++) cout << a(i) << " "; cout << endl;

i="";
while(1) {
	
	i=a(i).Order(1);
	if (i=="") break;
	cout << i << " ";
	}

cout << endl;

cout << "Max " << a().Max() << endl;

for (i=0; i< 6; i++) for (j=1; j<5; j++) a(i,j)=i;

a(3).Kill();

GlobalClose;

return EXIT_SUCCESS;

}

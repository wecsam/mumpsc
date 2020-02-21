#include <mumpsc/libmpscpp.h>

global mat1("mat1");

int main() {

    mstring i,j,k;

    for (i=0; i<5; i++) {
        mat1(i)=i;
        for (j=0; j<5; j++) {
            mat1(i,j)=j;
            for (k=0; k<5; k++) {
                mat1(i,j,k)=k;
                }
            }
        }

    for (i=0; i<5; i++) {
        cout << mat1(i) << endl;
        for (j=0; j<5; j++) {
            cout << "  " << mat1(i,j) << endl;
            for (k=0; k<5; k++) {
                cout << "    " << mat1(i,j,k);
                }
            cout << endl;
            }
        }

    return 0;
    }

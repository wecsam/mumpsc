#include <stdio.h>

int main(int argc, char*argv[]) {

int a[101] = {0};
int i,j,k;

k= atoi(argv[1]);

for (j=0; j<k; j++) {

	if (scanf("%d",&i)==EOF) break;
	a[i]=a[i]+1;
	}

for (i=0; i<100; i++) printf("%d\n",a[i]);

}

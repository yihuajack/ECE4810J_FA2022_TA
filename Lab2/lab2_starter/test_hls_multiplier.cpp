#include <stdio.h>
unsigned int hls_multiplier(unsigned short int a, unsigned short int b);
int main() {
	unsigned short int a, b;
	unsigned int p;
	a = 2;
	b = 3;
	p = 0;
	printf("initialized variables: a=%d, b=%d \n", a, b);
	p = hls_multiplier(a, b);
	printf("testing hls_multiplier: %d * %d = %d \n", a, b, p);
	return 0;
}

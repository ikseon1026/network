#include <stdio.h>

int main(void)
{
	char a[5];
	int b[5];
	long c[5];
	float d[5];
	double e[5];

	printf("char a[5] : %lu\n", (unsigned long)sizeof(a));
	printf("int b[5] : %lu\n", (unsigned long)sizeof(b));
	printf("long c[5] : %lu\n", (unsigned long)sizeof(c));
	printf("float d[5] : %lu\n", (unsigned long)sizeof(d));
	printf("double e[5] : %lu\n", (unsigned long)sizeof(e));
	
	return 0;
}				

#include <stdio.h>

int main(void)
{
	char a = 'A';
	int b = 1;
	float c = 3.14;
	double d = 5.678;

	void *p;

	printf("void * : %lu\n", (unsigned long)sizeof(p));

	p = &a;
	printf("char : %c\n", *(char *)p);
	
	p = &b;
	printf("int : %d\n", *(int *)p);
	
	p = &c;
	printf("float : %f\n", *(float *)p);
	
	p = &d;
	printf("double : %lf\n", *((double *)p));

	return 0;
}				

#include <stdio.h>

int main(void)
{
	char a = 1;
	char *p, **pp;

	p = &a; 
	pp = &p; 

	printf("&a : %p\n", &a);
	printf("&p : %p\n", &p); 
	printf("&pp : %p\n", &pp);

	printf("a : %d\n", a); 
	printf("*p : %d\n", *p);
	printf("**p : %d\n", **pp);

	**pp = 100;

	printf("a : %d\n", a); 
	printf("*p : %d\n", *p);
	printf("**p : %d\n", **pp);

	return 0;
}

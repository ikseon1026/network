#include <stdio.h>

struct data
{
	unsigned char a:2;
	unsigned char b:2;
	unsigned char c:4;
};

int main(void)
{
	struct data a;

	a.a = 2;
	a.b = 1;
	a.c = 1;

	printf("struct data : %lu\n", (unsigned long)sizeof(struct data));

	printf("a.a : %d\n", a.a);
	printf("a.b : %d\n", a.b);
	printf("a.c : %d\n", a.c);

	return 0;
}	

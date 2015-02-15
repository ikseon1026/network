#include <stdio.h>

struct data
{
	int a;
	int b;
};

int main(void)
{
	struct data a;
	struct data *p;

	a.a = 1;
	a.b = 2;

	p = &a;

	printf("a.a : %d\n", a.a);
	printf("a.b : %d\n", a.b);

	return 0;
}

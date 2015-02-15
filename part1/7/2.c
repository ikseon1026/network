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

	printf("(*p).a : %d\n", (*p).a);
	printf("(*p).b : %d\n", (*p).b);

	return 0;
}

#include <stdio.h>

struct a
{
	int a1;
	int a2;
};

struct b
{
	int b1;
	int b2;
};

struct data
{
	struct a a;
	struct b b;
};

int main(void)
{
	struct data data;

	data.a.a1 = 1;
	data.a.a2 = 2;
	data.b.b1 = 3;
	data.b.b2 = 4;

	printf("data.a.a1 : %d\n", data.a.a1);
	printf("data.a.a2 : %d\n", data.a.a2);
	printf("data.b.b1 : %d\n", data.b.b1);
	printf("data.b.b2 : %d\n", data.b.b2);
	
	return 0;
}				

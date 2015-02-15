#include <stdio.h>

struct data
{
	char a;
	int b;
	float c;
};

int main(void)
{
	struct data a = {'B', 101, 1.2};

	printf("a.a : %c, a.b : %d, a.c : %f\n", a.a, a.b, a.c);
	
	return 0;
}				

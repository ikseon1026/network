#include <stdio.h>

int main(void)
{
	int a = 1, b = 2;
	int c = 3, d = 4;
	int e = 5, f = 6;
	int g = 7;

	a += 1;
	b -= 2;
	c %= 3;
	d /= 4;
	e ^= 5;
	f |= 6;
	g &= 7;

	printf("a += 1 : %d\nb -= 2 : %d\n", a, b);
	printf("c %%= 3 : %d\nd /= 4 : %d\n", c, d);
	printf("e ^= 5 : %d\nf |= 6 : %d\n", e, f);
	printf("g &= 7 : %d\n", g);

	return 0;
}				

#include <stdio.h>

int main(void)
{
	int a = 1;
	int b = 2;

	int c = 3;
	unsigned int d = 3;
	
	printf("0x%08x | 0x%08x = 0x%08x\n", a, b, a | b);
	printf("0x%08x & 0x%08x = 0x%08x\n", a, b, a & b);
	printf("0x%08x ^ 0x%08x = 0x%08x\n", a, b, a ^ b);
	printf("~0x%08x = 0x%08x\n", a, ~a);

	printf("signed int : 0x%08x >> 1 = 0x%08x\n", c, c >> 1);
	printf("signed int : 0x%08x << 1 = 0x%08x\n", c, c << 1);
	printf("signed int : 0x%08x >> 1 = 0x%08x\n", ~c, ~c >> 1);

	printf("unsigned int : 0x%08x >> 1 = 0x%08x\n", d, d >> 1);
	printf("unsigned int : 0x%08x << 1 = 0x%08x\n", d, d << 1);
	printf("unsigned int : 0x%08x >> 1 = 0x%08x\n", ~d, ~d >> 1);

	return 0;
}				

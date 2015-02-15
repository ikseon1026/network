#include <stdio.h>

int main(void)
{
	char *a = "a";
	char b[] = "abcd";
	char c[100] = "1234";

	printf("%s : %lu\n", a, (unsigned long)sizeof(a));
	printf("%s : %lu\n", b, (unsigned long)sizeof(b));
	printf("%s : %lu\n", c, (unsigned long)sizeof(c));
	
	return 0;
}				

#include <stdio.h>

int main(void)
{
	int a, b;

	scanf("%d %d", &a, &b);

	if(a < b) printf("%d < %d\n", a, b);
	else if(a > b) printf("%d > %d\n", a, b);
	else if(a == b) printf("%d == %d\n", a, b);
	else if(a != b) printf("%d != %d\n", a, b);
	else if(a <= b) printf("%d <= %d\n", a, b);
	else if(a >= b) printf("%d >= %d\n", a, b);
	else if(a && b) printf("%d && %d : true\n", a, b);
	else if(a || b) printf("%d || %d : true\n", a, b);
	else printf("Unknown\n");

	return 0;
}				

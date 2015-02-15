#include <stdio.h>

int main(void)
{
	int a, b;

	scanf("%d %d", &a, &b);

	if(a < b) printf("%d < %d : true\n", a, b);
	if(a > b) printf("%d > %d : true\n", a, b);
	if(a == b) printf("%d ==  %d : true\n", a, b);
	if(a != b) printf("%d != %d : true\n", a, b);
	if(a <= b) printf("%d <= %d : true\n", a, b);
	if(a >= b) printf("%d >= %d : true\n", a, b);
	if(a && b) printf("%d && %d : true\n", a, b);
	if(a || b) printf("%d || %d : true\n", a, b);
	if(!a) printf("!%d : true\n", a);

	return 0;
}				

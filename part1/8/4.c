#include <stdio.h>

int plus(int a, int b);
int minus(int a, int b);

int main(void)
{
	int (*function_ptr)(int, int);

	function_ptr = plus;
	printf("%d + %d = %d\n", 1,2,function_ptr(1,2));

	function_ptr = minus;
	printf("%d - %d = %d\n", 5,3,function_ptr(5,3));

	return 0;
}				

int plus(int a, int b)
{
	return a+b;
}
int minus(int a, int b)
{
	return a-b;
}

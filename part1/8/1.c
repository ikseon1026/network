#include <stdio.h>

int calculator(int a, int b, char op);

int main(void)
{
	int a = 10;
	int b = 20;
	char op = '+';
	int result = 0;

	printf("main a : %p b : %p op : %p\n", &a, &b, &op);

	result = calculator(a, b, op);

	printf("%d %c %d = %d\n", a, op, b, result);

	return 0;
}				

int calculator(int a, int b, char op)
{
	int result = 0;

	printf("calculator a : %p b : %p op : %p\n", &a, &b, &op);

	switch(op){
		case '+':
			result = a+b;
			break;
		case '-':
			result = a-b;
			break;
		case '*':
			result = a*b;
			break;	
		case '/':
			result = a/b;
			break;
	}

	return result;
	
}

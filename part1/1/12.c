#include <stdio.h>

int main(void)
{
	int a, b, result;
	char c;

	scanf("%d %c %d", &a, &c, &b);

	switch(c) {
		case '+':
			result = a + b;
			break;
		case '-':
			result = a - b;
			break;
		case '*':
			result = a * b;
			break;
		case '/':	
			result = a / b;
			break;
		default:
			printf("Not allowed\n");
			return 1;
	}

	printf("%d %c %d = %d\n", a, c, b, result);

	return 0;
}				

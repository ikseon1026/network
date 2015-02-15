#include <stdio.h>
#include "cal.h"

int main(void)
{
	char op;
	float a, b, value;

	scanf("%f %c %f", &a, &op, &b);

	switch(op)
	{
		case '+':
			value = add(a, b);
			break;
		case '-':
			value = subtract(a,b);
			break;
		case '/':
			value = divide(a,b);
			break;
		case '*':
			value = multiply(a,b);
			break;
	}

	printf("%f %c %f = %f\n", a, op, b, value);

	return 0;
}				
#include <stdio.h>

int main(void)
{
	int a = 10;
	int b = 4;

	float c = a/b;
	float d = (float)a/b;
	float e = (int)((float)a/b);

	printf("c : %f\n", c);
	printf("d : %f\n", d);
	printf("e : %f\n", e);
	
	return 0;
}

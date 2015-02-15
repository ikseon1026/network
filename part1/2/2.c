#include <stdio.h>

int main(void)
{
	int i;
	char a[5];
	int b[5];

	for(i = 0; i < 5; i += 1) {
		printf("a[%d] : %p\n", i, &a[i]);
	}

	for(i = 0; i < 5; i += 1) {
		printf("b[%d] : %p\n", i, &b[i]);
	}

	return 0;
}

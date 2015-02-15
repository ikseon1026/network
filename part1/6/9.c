#include <stdio.h>

int main(void)
{
	int i;
	char p[][10] = {
		"hello", "hi"
	};

	printf("p : %lu\n", (unsigned long)sizeof(p));

	for(i = 0; i < sizeof(p)/10; i += 1) {
		printf("p[%d] : %s\n", i, p[i]);		
	}

	return 0;
}				

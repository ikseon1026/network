#include <stdio.h>

int main(void)
{
	int i;
	char *p[] = {
		"hello", "hi"
	};

	printf("p : %lu\n", (unsigned long)sizeof(p));

	for(i = 0; i < sizeof(p)/sizeof(char*); i += 1) {
		printf("p[%d] %p : %s\n", i, p[i], p[i]);		
	}

	return 0;
}				

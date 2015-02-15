#include <stdio.h>

int main(void)
{
	int i;
	char buf[] = "abcd";
	char *p = "abcd";
	
	for(i = 0; i < 4; i += 1) {
		printf("%p : %s\n", buf + i, (buf + i));		
	}

	for(i = 0; i < 4; i += 1) {
		printf("%p : %s\n", p, p);		
		p++;
	}

	
	return 0;
}				

#include <stdio.h>

int main(void)
{
	int i;
	char buf[] = "hello";
	char *p = buf;
	
	for(i = 0; i < sizeof(buf) - 1; i += 1) {
		printf("%p : %s\n", p + i, (p + i));		
	}
	
	return 0;
}				

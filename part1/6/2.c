#include <stdio.h>

int main(void)
{
	int i;
	char b[] = "abcd";

	for(i = 0; i < sizeof(b); i += 1) {
		printf("%c[%d]\n", b[i], b[i]);	
	}
	
	return 0;
}				

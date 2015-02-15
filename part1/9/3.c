#include <stdio.h>
#include <string.h>

int main(void)
{
	int i;
	char p[5];

	memset(p, 0x11, 5);
	
	for(i = 0; i < 5; i += 1) {
		printf("p[%d]:%x\n", i, p[i]);
	}
	
	return 0;
}				

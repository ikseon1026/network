#include <stdio.h>

int main(void)
{
	char *buf = "hello";
	buf[0] = 'H';

	printf("%s\n", buf);
	
	return 0;
}				

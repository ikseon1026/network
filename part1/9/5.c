#include <stdio.h>
#include <string.h>

int main(void)
{
	char buf[100];
	char *str = "hello!! world!!";

	memcpy(buf, str, strlen(str) + 1);

	printf("buf : %s\n", buf);	
	
	return 0;
}				

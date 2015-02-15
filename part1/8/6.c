#include <stdio.h>
#include <string.h>

int main(void)
{
	char buf[100];
	char *str = "hello!! world!!";

	strcpy(buf, str);

	printf("%s\n", buf);
		
	return 0;
}				

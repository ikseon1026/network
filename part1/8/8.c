#include <stdio.h>
#include <string.h>

int main(void)
{
	char buf[100] = "hello ";

	strcat(buf, "world!!");

	printf("%s\n", buf);
	
	return 0;
}				

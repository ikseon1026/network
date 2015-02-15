#include <stdio.h>

int main(void)
{
	char buf[1024];

	sprintf(buf, "msg : %s", "hello!!");
	printf("%s\n", buf);
	
	return 0;
}				

#include <stdio.h>

int main(void)
{
	char *buf;

	printf("string : ");
	scanf ("%s", buf);
	printf("buf[%p] : %s\n", buf, buf);	

	return 0;
}

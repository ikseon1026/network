#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(void)
{
	printf("errno : %d\n", errno);
	printf("malloc : %s\n", strerror(errno));	

	return 0;
}				

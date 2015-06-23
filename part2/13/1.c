#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(void)
{
	printf("errno : %d\n", errno);
	perror("malloc");

	return 0;
}				

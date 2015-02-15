#include <stdio.h>

int main(void)
{
#ifndef __linux__
	printf("not linux\n");
#else
	printf("linux\n");
#endif
	
	return 0;
}				

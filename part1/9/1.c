#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	char *ptr = (char *)malloc(10);

	strcpy(ptr, "hello");
	printf("%s\n", ptr);	

	free(ptr);
	
	return 0;
}				

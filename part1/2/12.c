#include <stdio.h>
#define	BUFMAX	2048

int main(void)
{
	char buffer[BUFMAX];

	printf("BUFMAX : %d\n", BUFMAX);	
	printf("buffer size : %lu\n", (unsigned long)sizeof(buffer));

	return 0;
}				

#include <stdio.h>

struct data {
	char *s1;
};

int main(void)
{
	struct data buffer;

	printf("input : ");
	scanf("%s", buffer.s1);	

	printf("buffer.s1 : %s\n", buffer.s1);
	
	return 0;
}				

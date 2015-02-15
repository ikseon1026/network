#include <stdio.h>

struct data {
	char s2[10];
};

int main(void)
{
	struct data buffer;

	printf("input : ");
	scanf("%s", buffer.s2);	

	printf("buffer.s2 : %s\n", buffer.s2);
	
	return 0;
}				

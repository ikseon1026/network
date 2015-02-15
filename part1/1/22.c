#include <stdio.h>

int main(void)
{
	int i;

	for(i=0; i<=5; i++) {
		if(i == 2) continue;

		printf("hello!! world!! [%d]\n", i);
	}	

	return 0;
}				

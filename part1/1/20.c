#include <stdio.h>

int main(void)
{
	int i;

	for(i=0; ; i++) {
		printf("hello!! world!! [%d]\n", i);

		if(i == 2) break;
	}	

	return 0;
}				

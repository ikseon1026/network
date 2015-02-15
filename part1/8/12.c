#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int i = 0;
	
	while(1) {
		i++;
		printf("value : %d\n", i);

		if(i == 5) {
			exit(0);
		}
	}

	return 0;
}				
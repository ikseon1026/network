#include <stdio.h>
#include <ctype.h>

int main()
{
	int count = 0;
	unsigned int i = 0;

	for(i=0; i<256; i++) {
		if(!isprint(i)) continue;

		printf("%d<%c> ", i, i);
		if(!(++count % 10)) printf("\n");
	}
	
	printf("\n");

	return 0;
}
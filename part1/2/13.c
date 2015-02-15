#include <stdio.h>

int main(void)
{
	printf("__LINE__ : %d\n", __LINE__);	
	printf("__DATE__ : %s\n", __DATE__);
	printf("__TIME__ : %s\n", __TIME__);
	printf("__TIMESTAMP__ : %s\n", __TIMESTAMP__);
	printf("__FILE__ : %s\n", __FILE__);

	return 0;
}				

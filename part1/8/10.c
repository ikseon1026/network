#include <stdio.h>

int main(void)
{
	int i;
	char buf[] = {"11:22:33:44:55:66"};
	int mac[6];

	sscanf(buf, "%x:%x:%x:%x:%x:%x", 
		&mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5]);

	for(i = 0; i < 6; i += 1) {
		printf("mac[%d] : %x\n", i, mac[i]);	
	}

	return 0;
}				

#include <stdio.h>

struct protocol
{
	unsigned int a;
	unsigned char b;
	unsigned char c;
	unsigned short d;
};

int main()
{
	int i;
	unsigned char data[] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
	unsigned char *ptr;
	struct protocol *proto;

	ptr = (unsigned char*)data;
	proto = (struct protocol *)ptr;

	printf("struct protocol : %lu\n", (unsigned long)sizeof(struct protocol));

	printf("protocol->a : %x\n", proto->a);		
	printf("protocol->b : %x\n", proto->b);
	printf("protocol->c : %x\n", proto->c);
	printf("protocol->d : %x\n", proto->d);

	for(i=0; i<sizeof(data); i++) {
		printf("%02x ", ptr[i]);

		if((i+1) %16 == 0) printf("\n");
	}		
	printf("\n");

	return 0;
}
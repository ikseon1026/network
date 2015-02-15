#include <stdio.h>

unsigned short datasum(unsigned short *data, int len);

int main()
{
	int i, length;
	unsigned short cksum, sum = 0;
	unsigned char header[] = {
		0x45, 0x00, 0x00, 0x80, 
		0x01, 0x00, 0x00, 0x00, 
		0x80, 0x01, 0x00, 0x00, 
		0x0a, 0x00, 0x01, 0x65, 
		0xa8, 0x7e, 0x3f, 0x01
	};

	length = sizeof(header);

	printf("data : ");
	for(i=0; i<length; i++) {
		printf ( "0x%02x", header[i] );	
		
		if((i+1) != length) printf ( ", " );	
	}
	printf("\n");

	sum = datasum((unsigned short *)header, length);
	cksum = ~sum;

	printf("0x%04x(%u) + 0x%04x(%u) = 0x%04x(%u)\n", 
		sum, sum,cksum, cksum,sum + cksum, sum+cksum);

	return 0;
}

unsigned short datasum(unsigned short *data, int len)
{
	unsigned long sum = 0;

	printf("------------------------------------------\n");

	for(; len > 1; len -=2 ) {
		printf("0x%08lx + 0x%04x = 0x%08lx\n", sum, *data, sum + *data);	
		sum += *data++;
	}

	if(len == 1) {
		unsigned short i = 0;
		*(unsigned char *)(&i) = *(unsigned char *)data;
		sum += i;
	}

	while(sum >> 16) {
		printf("[0x%08lx] : 0x%08lx + 0x%08lx = 0x%08lx\n",sum, 
		(sum & 0xffff), (sum >> 16), (sum & 0xffff) + (sum >> 16));	

		sum = (sum & 0xffff) + (sum >> 16);
	}

	printf("------------------------------------------\n");

	return sum;
}
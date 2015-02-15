#include <stdio.h>
#include "icmp.h"

int main(void)
{
	struct icmphdr icmphdr;

	icmphdr.type = 8;
	icmphdr.code = 0;

	printf("struct icmp : %lu\n", (unsigned long)sizeof(struct icmphdr));

	dump_icmp_header(&icmphdr);

	return 0;
}				
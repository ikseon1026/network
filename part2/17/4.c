#include <stdio.h>
#include "ip.h"

int main(void)
{
	struct ip ip;

	ip.ip_v = 4;
	ip.ip_hl = 5;
	ip.ip_tos = 1;
	ip.ip_len = 10;
	ip.ip_id = 1;
	ip.ip_off = 0;
	ip.ip_ttl = 128;
	ip.ip_p = 6;
	ip.ip_sum = 0;

	ip.ip_src.s_addr = 0x0100007f;
   	ip.ip_dst.s_addr = 0x01010101;

	printf("ip : %lu\n", (unsigned long)sizeof(struct ip));

	dump_ip_header(&ip);

	return 0;
}
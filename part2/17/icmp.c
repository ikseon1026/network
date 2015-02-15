#include <stdio.h>

#ifndef __linux__
	#include <winsock2.h>
#else
	#include <netinet/in.h>
	#include <arpa/inet.h>
#endif

#include "icmp.h"

void dump_icmp_header(struct icmphdr *icmphdr)
{
	printf("[ICMP] [Type : %d] [Code : %d]\n",
		icmphdr->type, icmphdr->code
	);
}

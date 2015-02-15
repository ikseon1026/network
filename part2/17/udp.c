#include <stdio.h>
#include <ctype.h>

#ifndef __linux__
	#include <winsock2.h>
#else
	#include <netinet/in.h>
	#include <arpa/inet.h>
#endif

#include "udp.h"

void dump_udp_header(struct udphdr *udphdr)
{
	int i, cut_size, data_len;
	char databuffer[1024];
	unsigned char *data_ptr;

	data_len = ntohs(udphdr->uh_ulen) - sizeof(struct udphdr);
	data_ptr = (unsigned char *)udphdr + sizeof(struct udphdr);

	cut_size = (data_len > 40)?40:data_len;

	for(i = 0; i < cut_size; i += 1) {
		databuffer[i] = (isprint(data_ptr[i]))?data_ptr[i]:'.';
	}

	databuffer[cut_size] = '\0';

	printf("[UDP] [%d->%d] [len : %d] %s\n",
		ntohs(udphdr->uh_sport), ntohs(udphdr->uh_dport),
		ntohs(udphdr->uh_ulen), databuffer	);	
}

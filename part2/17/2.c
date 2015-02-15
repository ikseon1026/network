#include <stdio.h>
#include <string.h>

#ifndef __linux__
	#include <winsock2.h>
#else
	#include <netinet/in.h>
#endif

#include "ethernet.h"

int main(void)
{
	struct ether_header ether_header;
	int i;

	ether_header.ether_type = htons(ETHERTYPE_IP);

	for(i = 0; i < 6; i += 1) {
		ether_header.ether_dhost[i] = i;
	}

	for(i = 0; i < 6; i += 1) {
		ether_header.ether_shost[i] = i + 0x10;			
	}

	printf("ether_header : %lu\n", (unsigned long)sizeof(struct ether_header));

	dump_ether_header(&ether_header);

	return 0;
}				

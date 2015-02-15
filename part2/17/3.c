#include <stdio.h>
#include <string.h>

#ifndef __linux__
	#include <winsock2.h>
#else
	#include <netinet/in.h>
	#include <arpa/inet.h>
#endif

#include "arp.h"

int main(void)
{
	struct ether_arp ether_arp;
	int src_ip, dst_ip;
	int i;

	ether_arp.arp_hrd = htons(1);
	ether_arp.arp_pro = htons(0x0800);
	ether_arp.arp_hln = 6;
	ether_arp.arp_pln = 4;
	ether_arp.arp_op = htons(ARPOP_REQUEST);

	src_ip = inet_addr("1.2.3.4");
	dst_ip = inet_addr("5.6.7.8");

	memcpy(ether_arp.arp_spa, &src_ip, 4);
	memcpy(ether_arp.arp_tpa, &dst_ip, 4);

	for(i = 0; i < 6; i += 1) {
		ether_arp.arp_sha[i] = i;
	}

	for(i = 0; i < 6; i += 1) {
		ether_arp.arp_tha[i] = i + 0x10;
	}

	printf("ether_arp : %lu\n", (unsigned long)sizeof(struct ether_arp));

	dump_arp_header(&ether_arp);

	return 0;
}				
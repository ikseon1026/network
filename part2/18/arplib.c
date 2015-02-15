#include <stdio.h>
#include <string.h>

#ifndef __linux__
	#include <winsock2.h>
#else
	#include <netinet/in.h>
	#include <arpa/inet.h>
#endif
#include "arplib.h"

void make_ether_header(struct ether_header *ether_header, 
		uint8_t *dest, uint8_t *source, uint16_t type)
{
	memcpy(ether_header->ether_dhost, dest, 6);
	memcpy(ether_header->ether_shost, source, 6);

	ether_header->ether_type = htons(type);
}

void make_arp_header(struct ether_arp *ether_arp, 
		uint8_t *sha, uint32_t spa,
		uint8_t *tha, uint32_t tpa, uint32_t op)
{
	ether_arp->arp_hrd = ntohs(1);
	ether_arp->arp_pro = ntohs(ETHERTYPE_IP);
	ether_arp->arp_hln = 6;
	ether_arp->arp_pln = 4;

	ether_arp->arp_op = htons(op);

	memcpy(ether_arp->arp_sha, sha, 6);
	memcpy(ether_arp->arp_spa, &spa, 4);

	(tha)?
		(memcpy(ether_arp->arp_tha, tha, 6)):
		(memset(ether_arp->arp_tha, 0x00, 6));

	memcpy(ether_arp->arp_tpa, &tpa, 4);
}

void strmac_to_buffer(const char *str, uint8_t *mac)
{
	int i;
	unsigned int tmac[6];

	sscanf(str, "%x:%x:%x:%x:%x:%x",
		&tmac[0], &tmac[1], &tmac[2], &tmac[3], &tmac[4], &tmac[5]);
			
	for(i = 0; i < 6; i += 1) {
		mac[i] = (unsigned char)tmac[i];	
	}
}
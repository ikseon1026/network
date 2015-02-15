#include <stdio.h>
#include <string.h>

#ifndef __linux__ 
	#include <winsock2.h>
	#include <windows.h>
#else
	#include <unistd.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
#endif

#include "icmplib.h"

int main(void)
{
	unsigned char *p;
	unsigned long i = 0;	
	unsigned char dhost[] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66};
	unsigned char shost[] = {0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};

	struct icmp_full_packet icmp_packet;	

	memset(&icmp_packet, 0x00, sizeof(icmp_packet));

	make_ether_header(
		&(icmp_packet.ether_header),dhost, shost, ETHERTYPE_IP);

	make_ip_header(&(icmp_packet.ip), 
		"17.34.51.68", "85.102.119.136", 128, sizeof(struct icmp));

	icmp_packet.icmp.icmp_type = 0xaa;
	icmp_packet.icmp.icmp_code = 0xbb;
	icmp_packet.icmp.icmp_id = htons(0xccdd);
	icmp_packet.icmp.icmp_seq = htons(0xeeff);
	
	icmp_packet.icmp.icmp_cksum = 0;
	icmp_packet.icmp.icmp_cksum = cksum(
			(unsigned short *)&(icmp_packet.icmp), sizeof(struct icmp));

	printf("struct ether_header : %lu\n", 
		(unsigned long)sizeof(struct ether_header));
	printf("struct ip : %lu\n", 
		(unsigned long)sizeof(struct ip));
	printf("struct icmp : %lu\n", 
		(unsigned long)sizeof(struct icmp));
	printf("struct icmp_full_packet : %lu\n\n", 
		(unsigned long)sizeof(struct icmp_full_packet));

	for(i=0, p = (unsigned char *)&icmp_packet; i<sizeof(icmp_packet); i++) {
		printf("%02x ", p[i]);

		if((i+1)%16 == 0) printf("\n");
	}
	printf("\n");

	return 0;
}				

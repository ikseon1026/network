#include <stdio.h>
#include <string.h>
#ifndef __linux__
	#include <winsock2.h>
#else
	#include <unistd.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
#endif

#include "tcplib.h"

int main(void)
{
	struct tcp_packet tcp_packet;
	const char *sip = "17.34.51.68";
	const char *dip = "85.102.119.136";

	unsigned char dm[6];
	unsigned char sm[6];

	unsigned char *ptr;
	int i;

	memset(&tcp_packet, 0x00, sizeof(tcp_packet));

	strmac_to_buffer("11:22:33:44:55:66", dm);
	strmac_to_buffer("aa:bb:cc:dd:ee:ff", sm);

	memcpy(tcp_packet.ether_header.ether_dhost, dm, 6);
	memcpy(tcp_packet.ether_header.ether_shost, sm, 6);
	tcp_packet.ether_header.ether_type = htons(ETHERTYPE_IP);

	make_ip_header(&(tcp_packet.ip), sip, dip, sizeof(struct tcphdr));

	make_tcp_header(&(tcp_packet), sip, htons(0x1111), dip, htons(0x2222),
		htonl(0x11223344), htonl(0x55667788), 0);	

	ptr = (unsigned char *)&tcp_packet;

	printf("struct ether_header : %lu\n", 
		(unsigned long)sizeof(struct ether_header));
	printf("struct ip : %lu\n", (unsigned long)sizeof(struct ip));
	printf("struct tcphdr : %lu\n", 
		(unsigned long)sizeof(struct tcphdr));

	printf("struct tcp_packet : %lu\n\n", 
		(unsigned long)sizeof(struct tcp_packet));

	for(i=0; i<sizeof(tcp_packet); i++) {
		printf("%02x ", ptr[i]);

		if((i+1) %16 == 0) printf("\n");	
	}	

	printf("\n");

	return 0;
}				

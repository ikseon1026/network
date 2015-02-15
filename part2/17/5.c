#include <stdio.h>
#include <string.h>

#ifndef __linux__
	#include <winsock2.h>
#else
	#include <netinet/in.h>
#endif

#include "ip.h"
#include "tcp.h"

#ifndef __linux__
	#pragma pack(push, 1)
#endif
struct packet 
{
	struct ip ip;
	struct tcphdr tcphdr;
	char buffer[100];
}
#ifndef __linux__
	;
	#pragma pack(pop)
#else
__attribute__ ((__packed__));
#endif

int main(void)
{
	struct packet packet;

	strcpy(packet.buffer, "hello!! world!!");

	packet.ip.ip_hl = (sizeof(struct ip) >> 2);
	packet.ip.ip_len = htons(sizeof(struct packet));

	packet.tcphdr.th_off = sizeof(struct tcphdr) >> 2;
	
	packet.tcphdr.th_sport = htons(1234);
	packet.tcphdr.th_dport = htons(80);

	packet.tcphdr.th_seq = htonl(1);
	packet.tcphdr.th_ack = htonl(2);
	
	packet.tcphdr.th_flags = 0;
	packet.tcphdr.th_flags |= TH_SYN;
	packet.tcphdr.th_flags |= TH_ACK;

	printf("tcphdr : %lu\n", (unsigned long)sizeof(struct tcphdr));

	dump_tcp_header(&packet.ip);
		
	return 0;
}				
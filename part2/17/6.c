#include <stdio.h>
#include <string.h>

#ifndef __linux__
	#include <winsock2.h>
#else
	#include <netinet/in.h>
	#include <arpa/inet.h>
#endif

#include "udp.h"

#ifndef __linux__
	#pragma pack(push, 1)
#endif
struct packet
{
	struct udphdr udphdr;
	char data[100];
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

	packet.udphdr.uh_sport = htons(1234);
	packet.udphdr.uh_dport = htons(100);

	packet.udphdr.uh_ulen = htons(sizeof(struct udphdr) + 100);

	strcpy(packet.data, "hello");

	printf("struct udphdr : %lu\n", (unsigned long)sizeof(struct udphdr));

	dump_udp_header(&packet.udphdr);

	return 0;
}
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "icmplib.h"

#define	BUFMAX	4096
#define	WAITTIME 3

enum {ARGV_CMD, ARGV_IP};

int main(int argc, char **argv)
{
	char buffer[BUFMAX];
	struct timeval tv;
	struct icmp icmp_packet;
	struct sockaddr_in addr;
	int sock, len;

	if(argc != 2) {
		printf("usage : %s [IP]\n", argv[ARGV_CMD]);
		return 1;
	}

	if((sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0) {
		perror("socket ");
		return 1;
	}

	memset(&tv, 0x00, sizeof(tv));
	tv.tv_sec = WAITTIME;

	setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

	memset(&addr, 0x00, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(argv[ARGV_IP]);	

	memset(&icmp_packet, 0x00, sizeof(icmp_packet));

	icmp_packet.icmp_type = 8;
	icmp_packet.icmp_code = 0;
	icmp_packet.icmp_id = htons(1);
	icmp_packet.icmp_seq = htons(1);
	icmp_packet.icmp_cksum = 0;

	icmp_packet.icmp_cksum = cksum(
			(unsigned short*)&icmp_packet, sizeof(icmp_packet));

	if(sendto(sock, &icmp_packet, sizeof(icmp_packet), 0, 
			(struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("sendto ");
	}

	while((len = read(sock, buffer, BUFMAX)) > 0) {
		struct ip *ip = (struct ip *)buffer;
		int ip_header_len = ip->ip_hl << 2;

		if(ip->ip_p == IPPROTO_ICMP) {
			struct icmp *icmp = (struct icmp *)(buffer + ip_header_len);

			printf("from : %s\n", inet_ntoa(ip->ip_src));
			printf("ICMP Type : %d\n", icmp->icmp_type);
			printf("ICMP Code : %d\n", icmp->icmp_code);
		}
	}

	close(sock);
	
	return 0;
}
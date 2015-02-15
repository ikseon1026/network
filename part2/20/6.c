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
#define	WAITTIME 2

enum {ARGV_CMD, ARGV_MY_IP, ARGV_TARGET_IP};

struct icmp_packet
{	
	struct ip ip;
	struct icmp icmp;
} __attribute__ ((__packed__));

int main(int argc, char **argv)
{
	int ttl, sock, len, on = 1;
	struct sockaddr_in addr;
	struct icmp_packet icmp_packet;
	struct timeval tv;
	char buffer[BUFMAX];

	if(argc != 3) {
		printf("usage : %s [my ip] [target ip]\n", argv[ARGV_CMD]);
		return 1;
	}

	if((sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0) {
		perror("socket ");
		return 1;
	}

	memset(&tv, 0x00, sizeof(tv));
	tv.tv_sec = WAITTIME;
	if(setsockopt(
		sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0) {
		perror("setsockopt ");
		return 1;
	}

	if(setsockopt(sock, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on)) < 0) {
		perror("setsockopt ");
		return 1;
	}

	memset(&addr, 0x00, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(argv[ARGV_TARGET_IP]);

	memset(&icmp_packet, 0x00, sizeof(icmp_packet));

	icmp_packet.icmp.icmp_type = 8;
	icmp_packet.icmp.icmp_code = 0;
	icmp_packet.icmp.icmp_id = getpid();
	icmp_packet.icmp.icmp_seq = htons(1);

	icmp_packet.icmp.icmp_cksum = 0;
	icmp_packet.icmp.icmp_cksum = 
		cksum((unsigned short *)&icmp_packet.icmp, sizeof(struct icmp));

	for(ttl=1; ttl<=30; ttl++) {
		make_ip_header(
			&icmp_packet.ip, argv[ARGV_MY_IP], 
			argv[ARGV_TARGET_IP], ttl, sizeof(struct icmp));

		if(sendto(sock, &icmp_packet, sizeof(icmp_packet), 0, 
			(struct sockaddr *)&addr, sizeof(addr)) < 0) {

			perror("sendto ");
			return 1;
		}
	
		while((len = read(sock, buffer, BUFMAX)) > 0) {

			struct ip *ip = (struct ip *)(buffer);
			struct icmp *icmp = (struct icmp *)(buffer + (ip->ip_hl << 2));

			printf("[%d] : %s (ICMP type : %d, ICMP code :%d)\n", ttl, 
					inet_ntoa(ip->ip_src),
					icmp->icmp_type, icmp->icmp_code);

			if(!strcmp(inet_ntoa(ip->ip_src), argv[ARGV_TARGET_IP])) {
				if((icmp->icmp_type == 0) && (icmp->icmp_code == 0)) {
					close(sock);
					return 0;
				}
			}
		}
	}

	close(sock);

	return 0;
}				

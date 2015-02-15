#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <pthread.h>
#include "icmplib.h"

#define	BUFMAX	4096
#define	WAITTIME 2

enum {ARGV_CMD, ARGV_START_IP, ARGV_END_IP};

struct icmp_packet
{
	struct icmp icmp;
	char data[10];
} __attribute__ ((__packed__));

void *thread_function(void *p);

int main(int argc, char **argv)
{
	int sock;
	struct icmp_packet icmp_packet;
	struct sockaddr_in addr;
	unsigned int start_ip, end_ip, ip;
	pthread_t thread_id;

	if(argc != 3) {
		printf("usage : %s [start ip] [end ip]\n", argv[ARGV_CMD]);
		return 1;
	}

	if((sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0) {
		perror("socket ");
		return 1;
	}

	memset(&addr, 0x00, sizeof(addr));
	addr.sin_family = AF_INET;

	memset(&icmp_packet, 0x00, sizeof(icmp_packet));

	strcpy(icmp_packet.data, "hello!!");

	icmp_packet.icmp.icmp_type = 8;
	icmp_packet.icmp.icmp_code = 0;
	icmp_packet.icmp.icmp_id = 1;
	icmp_packet.icmp.icmp_seq = 1;
	icmp_packet.icmp.icmp_cksum = 0;

	icmp_packet.icmp.icmp_cksum = cksum(
			(unsigned short*)&icmp_packet, sizeof(icmp_packet));

	start_ip = ntohl(inet_addr(argv[ARGV_START_IP]));
	end_ip = ntohl(inet_addr(argv[ARGV_END_IP]));

	pthread_create(&thread_id, NULL, thread_function, &sock);

	for(ip = start_ip; ip<=end_ip; ip++) {
		addr.sin_addr.s_addr = htonl(ip);

		if(sendto(sock, &icmp_packet, sizeof(icmp_packet), 0, 
				(struct sockaddr *)&addr, sizeof(addr)) < 0) {
			perror(inet_ntoa(addr.sin_addr));
			break;
		}
	}

	sleep(1);

	close(sock);
	
	return 0;
}				

void *thread_function(void *p)
{
	char buffer[BUFMAX];
	int sock, len; 
	
	sock= *((int *)p);

	while((len = read(sock, buffer, BUFMAX)) > 0) {
		struct ip *ip = (struct ip *)buffer;
		int ip_header_len = ip->ip_hl << 2;

		if(ip->ip_p == IPPROTO_ICMP) {
			struct icmp *icmp = (struct icmp *)(buffer + ip_header_len);
			if((icmp->icmp_type == 0) && (icmp->icmp_code == 0)) {
				printf("from : %s\n", inet_ntoa(ip->ip_src));
			}
		}
	}

	return 0;
}

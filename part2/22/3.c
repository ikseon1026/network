#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>

#include "tcplib.h"

#define	STRSIZE 1024
#define	BUFSIZE 4096

enum { ARGV_CMD, ARGV_INTERFACE, ARGV_IP, ARGV_PORT };

int main(int argc, char **argv)
{
	int sock, len, filter_port, pos;
	struct sockaddr_ll	sll;
	struct ifreq ifr;
	unsigned int filter_ip;
	unsigned char buffer[BUFSIZE];
	char str_sip[STRSIZE], str_dip[STRSIZE];
	char flags[STRSIZE];
		
	if(argc != 4) {
		printf("Usage : %s [interface] [ip] [port]\n", argv[ARGV_CMD]);
		return 1;
	}

	if((sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0) {
		perror("socket");
		return 1;
	}

	memset(&ifr, 0x00, sizeof(ifr));

	strcpy(ifr.ifr_name, argv[ARGV_INTERFACE]);
	if(ioctl(sock, SIOCGIFINDEX, &ifr) < 0 ) {
		perror("ioctl ");
		return 1;
	}

	memset(&sll, 0x00, sizeof(sll));
	sll.sll_family = PF_PACKET;
	sll.sll_ifindex = ifr.ifr_ifindex;
	sll.sll_protocol = htons(ETH_P_ALL);

	if(bind(sock, (struct sockaddr *)&sll, sizeof(sll)) < 0) {
		perror("bind");
		return 1;
	}

	filter_ip = inet_addr(argv[ARGV_IP]);
	filter_port = htons(atoi(argv[ARGV_PORT]));

	while((len = read(sock, buffer, BUFSIZE)) >= 0) {
		struct ip *ip = NULL;
		struct tcphdr *tcphdr = NULL;
		struct ether_header *ether_header = (struct ether_header *)buffer;

		if(ntohs(ether_header->ether_type) != ETHERTYPE_IP) continue;

		ip = (struct ip *)(buffer + sizeof(struct ether_header));

		if((ip->ip_p == IPPROTO_TCP) && (
					(ip->ip_src.s_addr == filter_ip) ||
					(ip->ip_dst.s_addr == filter_ip))) {

			tcphdr = (struct tcphdr *)((char *)ip + (ip->ip_hl << 2));

			if(tcphdr->th_dport == filter_port || tcphdr->th_sport == filter_port) {

				pos = 0;

				if((tcphdr->th_flags & TH_SYN) == TH_SYN) flags[pos++] = 'S';
				if((tcphdr->th_flags & TH_FIN) == TH_FIN) flags[pos++] = 'F';
				if((tcphdr->th_flags & TH_RST) == TH_RST) flags[pos++] = 'R';
				if((tcphdr->th_flags & TH_PUSH)==TH_PUSH) flags[pos++] = 'P';
				if((tcphdr->th_flags & TH_ACK) == TH_ACK) flags[pos++] = 'A';
				if((tcphdr->th_flags & TH_URG) == TH_URG) flags[pos++] = 'U';

				flags[pos] = '\0';

				strcpy(str_sip, inet_ntoa(ip->ip_src));
				strcpy(str_dip, inet_ntoa(ip->ip_dst));

				printf("%s:%d->%s:%d "\
					"(seq : %u, flags : %s, len : %d)\n", 
					str_sip, ntohs(tcphdr->th_sport),
					str_dip, ntohs(tcphdr->th_dport), 
					ntohl(tcphdr->th_seq),
					(pos)?flags:"unknown", ntohs(ip->ip_len));	
			}
		}
	}

	close(sock);

	return 0;
}

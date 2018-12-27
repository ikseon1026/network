#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/if_packet.h>
#include <netinet/ether.h>

#define BUFSIZE 2048

int main(int argc, char **argv)
{
	int sock, len, addr_len;
	struct sockaddr_ll sll;
	char buffer[BUFSIZE];
	char *pkttype, *protocol;

	if((sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0) {
		perror("socket");
		return 1;
	}

	addr_len = sizeof(sll);

	while((len = recvfrom(sock, buffer, BUFSIZE, 0, 
		(struct sockaddr *)&sll, &addr_len)) >= 0) {
		switch(sll.sll_pkttype) {
			case PACKET_HOST:
				pkttype = "PACKET_HOST";
				break;
			case PACKET_BROADCAST:
				pkttype = "PACKET_BROADCAST";
				break;
			case PACKET_MULTICAST:
				pkttype = "PACKET_MULTICAST";
				break;
			case PACKET_OTHERHOST:
				pkttype = "PACKET_OTHERHOST";
				break;
			default:
				pkttype = "Unknown";
		}

		switch(ntohs(sll.sll_protocol)) {
			case ETH_P_IP:
				protocol = "IP";
				break;
			case ETH_P_ARP:
				protocol = "ARP";
				break;
			default:
				protocol = "Unknown";
		}

		printf("[%d] [%s] [%s] [len : %d]\n",
			sll.sll_ifindex, pkttype, protocol, len);
	}

	close(sock);

	return 0;
}

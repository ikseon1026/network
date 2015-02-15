#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef __linux__
	#include <winsock2.h>
#else
	#include <netinet/in.h>
	#include <arpa/inet.h>
#endif

#include "tcplib.h"
#include "pcap.h"   

#define	STRSIZE 1024

enum { 
	ARGV_CMD, 
	ARGV_SOURCE_MAC,
	ARGV_DEST_MAC,
	ARGV_SOURCE_IP,
	ARGV_SOURCE_PORT,
	ARGV_TARGET_IP, 
	ARGV_TARGET_PORT,
	ARGV_SEQ
};

int main(int argc, char **argv)
{
	pcap_t *adhandle;
	struct tcp_packet tcp_packet;
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_if_t *alldevs;            
	pcap_if_t *d;                    
	unsigned int seq;
	int i = 0;
	int no;

	if(argc != 8) {
		printf(
			"usage : %s [source mac] [destination mac] "\
			"[source ip] [source port] [target ip] [target port] [seq]\n", 
			argv[ARGV_CMD]);
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
		return -1;
	}

	memset(&tcp_packet, 0x00, sizeof(tcp_packet));
	
	strmac_to_buffer(
		argv[ARGV_SOURCE_MAC], tcp_packet.ether_header.ether_shost);
	strmac_to_buffer(
		argv[ARGV_DEST_MAC], tcp_packet.ether_header.ether_dhost);
	tcp_packet.ether_header.ether_type = htons(ETHERTYPE_IP);

	sscanf(argv[ARGV_SEQ], "%u", &seq);

	make_tcp_header(
			&tcp_packet, 
			argv[ARGV_SOURCE_IP], atoi(argv[ARGV_SOURCE_PORT]), 
			argv[ARGV_TARGET_IP], atoi(argv[ARGV_TARGET_PORT]), 
			seq, 0, TH_RST);

	make_ip_header(
		&(tcp_packet.ip), 
		argv[ARGV_SOURCE_IP], argv[ARGV_TARGET_IP], sizeof(struct tcphdr));

	pcap_sendpacket(adhandle, 
		(unsigned char *)&tcp_packet, sizeof(tcp_packet));

	pcap_freealldevs(alldevs);
	pcap_close(adhandle);

	return 0;
}

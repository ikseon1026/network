#include <stdio.h>
#include <string.h>

#ifndef __linux__
	#include <winsock2.h>
#else
	#include <netinet/in.h>
	#include <arpa/inet.h>
#endif

#include "ethernet.h"
#include "arp.h"
#include "ip.h"
#include "tcp.h"
#include "udp.h"
#include "icmp.h"

#include "pcap.h"   

void packet_handler(u_char *param, 
		const struct pcap_pkthdr *header, const u_char *pkt_data)
{ 
	unsigned char *buffer= (unsigned char *)pkt_data;
	void *header_ptr = buffer + sizeof(struct ether_header);
	struct ether_header *ether_header = (struct ether_header *)buffer;
	struct ip *ip;
	void *next_header_ptr;

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

				ip = (struct ip *)header_ptr;
				next_header_ptr = ((char*)ip) + (ip->ip_hl << 2);

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

int main(int argc, char **argv)
{
	pcap_t *adhandle;
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_if_t *alldevs;            
	pcap_if_t *d;                    
	struct pcap_addr *a;
	int i = 0;
	int no;

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

	pcap_freealldevs(alldevs);

	pcap_loop(adhandle, 0, packet_handler, NULL);

	pcap_close(adhandle);

	return 0;
}

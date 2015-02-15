#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef __linux__ /* for windows */
	#include <winsock2.h>
	#include <windows.h>
	#define CREATE_THREAD(id,function,param) \
		CreateThread(NULL,0,function,param,0,&id);
	#define THREAD_TYPE_RETURN DWORD WINAPI
	#define THREAD_TYPE_PARAM LPVOID
	#define THREAD_TYPE_ID DWORD
	#define SLEEP(x)	Sleep(x*1000)
#else	/* for linux */
	#include <unistd.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <pthread.h>
	#define CREATE_THREAD(id,function,param) \
		pthread_create(&id,NULL,function,param);
	#define THREAD_TYPE_RETURN void*
	#define THREAD_TYPE_PARAM void*
	#define THREAD_TYPE_ID pthread_t
	#define SLEEP(x)	sleep(x)
#endif

#include "pcap.h"
#include "icmplib.h"

#define	STR_IP_LENGTH 1024

enum {
	ARGV_CMD, 
	ARGV_MY_MAC,
	ARGV_GW_MAC,
	ARGV_TARGET_IP
};

void packet_handler(
	u_char *param, 
	const struct pcap_pkthdr *header, const u_char *pkt_data
);

pcap_t *adhandle;
THREAD_TYPE_RETURN thread_function(THREAD_TYPE_PARAM param);

int main(int argc, char **argv)
{
	int ttl, no, i = 0;
	char errbuf[PCAP_ERRBUF_SIZE];
	
	pcap_if_t *alldevs, *d;

	THREAD_TYPE_ID thread_id;

	struct pcap_addr *a;
	struct icmp_full_packet icmp_packet;

	struct in_addr my_ip;
	unsigned char my_mac[6], target_mac[6];

	if(argc != 4) {
		printf("Usage : %s [my mac] [gateway mac] [target IP]\n", argv[0]);
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

	for(a = d->addresses; a; a=a->next) {
		struct sockaddr_in *in_addr
			= (struct sockaddr_in *)a->addr;

		if(a->addr->sa_family == AF_INET) {
			my_ip.s_addr = in_addr->sin_addr.s_addr;
			break;
		}
	}

	CREATE_THREAD(thread_id, thread_function, argv[ARGV_TARGET_IP]);

	memset(&icmp_packet, 0x00, sizeof(icmp_packet));

	strmac_to_buffer(argv[ARGV_GW_MAC], target_mac);
	strmac_to_buffer(argv[ARGV_MY_MAC], my_mac);

	make_ether_header(
		&(icmp_packet.ether_header), target_mac, my_mac, ETHERTYPE_IP);

	icmp_packet.icmp.icmp_type = 8;
	icmp_packet.icmp.icmp_code = 0;
	icmp_packet.icmp.icmp_id = htons(1);
	icmp_packet.icmp.icmp_seq = htons(1);

	icmp_packet.icmp.icmp_cksum = 0;
	icmp_packet.icmp.icmp_cksum = cksum(
			(unsigned short *)&(icmp_packet.icmp), sizeof(struct icmp));

	for(ttl=1; ttl<=30; ttl++) {

		make_ip_header(
				&icmp_packet.ip, inet_ntoa(my_ip), 
				argv[ARGV_TARGET_IP], ttl, sizeof(struct icmp));;

		pcap_sendpacket(
				adhandle, (unsigned char *)&icmp_packet, sizeof(icmp_packet)
				);

		SLEEP(1);
	}

	pcap_freealldevs(alldevs);
	pcap_close(adhandle);

	return 0;
}

THREAD_TYPE_RETURN thread_function(THREAD_TYPE_PARAM param)
{
	pcap_loop(adhandle, 0, packet_handler, (unsigned char *)param);

	return 0;
}

void packet_handler(
	u_char *param, 
	const struct pcap_pkthdr *header, const u_char *pkt_data)
{ 
	unsigned char *buffer = (unsigned char *)pkt_data;
	struct ether_header *ether_header = (struct ether_header *)buffer;

	if(ntohs(ether_header->ether_type) == ETHERTYPE_IP) {

		struct ip *ip = (struct ip *)(buffer + sizeof(struct ether_header));

		if(ip->ip_p == IPPROTO_ICMP) {

			struct icmp *icmp = 
				(struct icmp *)(buffer + (ip->ip_hl << 2) 
					+ sizeof(struct ether_header));

			if(!(icmp->icmp_type == 11 || icmp->icmp_type == 0)) return;

			printf("%s (ICMP type : %d, ICMP code :%d)\n",
					inet_ntoa(ip->ip_src),
					icmp->icmp_type, icmp->icmp_code);

			if(!strcmp(inet_ntoa(ip->ip_src), (char *)param)) {
				exit(0);
			}
		}
	}
}
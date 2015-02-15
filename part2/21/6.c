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
#include "tcplib.h"

#define	STR_IP_LENGTH 1024

enum {
	ARGV_CMD, 
	ARGV_MY_MAC,
	ARGV_DEST_MAC,
	ARGV_TARGET_IP,
	ARGV_START_PORT,
	ARGV_END_PORT
};

void packet_handler(
	u_char *param, 
	const struct pcap_pkthdr *header, const u_char *pkt_data
);

struct param_data
{
	pcap_t *adhandle;
	int start_port;
	int end_port;	
};

THREAD_TYPE_RETURN thread_function(THREAD_TYPE_PARAM param);

int main(int argc, char **argv)
{
	int no, i = 0;
	int port, start_port, end_port;
	char errbuf[PCAP_ERRBUF_SIZE];

	struct tcp_packet packet;
	struct param_data param_data;
	
	pcap_if_t *alldevs, *d;

	THREAD_TYPE_ID thread_id;

	struct pcap_addr *a;

	struct in_addr my_ip;

	if(argc != 6) {
		printf(
			"Usage : %s [my mac] [target mac] [target IP] "\
			"[start port] [end port]\n", 
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

	if(!(param_data.adhandle= 
				pcap_open_live(d->name, 65536, 1,	1000, errbuf))) {
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

	CREATE_THREAD(thread_id, thread_function, &param_data);

	memset(&packet, 0x00, sizeof(packet));

	strmac_to_buffer(
		argv[ARGV_DEST_MAC], packet.ether_header.ether_dhost);
	strmac_to_buffer(
		argv[ARGV_MY_MAC], packet.ether_header.ether_shost);
	packet.ether_header.ether_type = htons(ETHERTYPE_IP);

	param_data.start_port = start_port = atoi(argv[ARGV_START_PORT]);
	param_data.end_port = end_port = atoi(argv[ARGV_END_PORT]);
	
	for(port = start_port; port <=end_port; port += 1) {
	
		make_tcp_header(
				&packet, 
				inet_ntoa(my_ip), rand(), 
				argv[ARGV_TARGET_IP], port, rand(), 0, TH_SYN);

		make_ip_header(&(packet.ip), 
				inet_ntoa(my_ip), argv[ARGV_TARGET_IP], sizeof(struct tcphdr));

		pcap_sendpacket(
			param_data.adhandle, (unsigned char *)&packet, sizeof(packet)
		);
	}

	SLEEP(3);

	pcap_freealldevs(alldevs);
	pcap_close(param_data.adhandle);

	return 0;
}

THREAD_TYPE_RETURN thread_function(THREAD_TYPE_PARAM param)
{
	struct param_data * param_ptr = 
		(struct param_data *)param;

	pcap_loop(
		param_ptr->adhandle, 0, packet_handler, (unsigned char *)param);

	return 0;
}

void packet_handler(
	u_char *param, 
	const struct pcap_pkthdr *header, const u_char *pkt_data)
{ 
	unsigned char *buffer = (unsigned char *)pkt_data;
	struct ether_header *ether_header = (struct ether_header *)buffer;
	struct param_data *param_ptr = (struct param_data *)param;

	if(ntohs(ether_header->ether_type) == ETHERTYPE_IP) {
				
		struct ip *ip = 
			(struct ip *)(buffer + sizeof(struct ether_header));
		struct tcphdr *tcphdr = NULL;

		if(ip->ip_p != IPPROTO_TCP) return;

		tcphdr = (struct tcphdr *)((char *)ip + (ip->ip_hl << 2));

		if((ntohs(tcphdr->th_sport) >=  param_ptr->start_port) && 
			(ntohs(tcphdr->th_sport) <= param_ptr->end_port)) {

			if(((tcphdr->th_flags & TH_SYN) == TH_SYN) && 
					((tcphdr->th_flags & TH_ACK) == TH_ACK)) {

				printf("%s:%d\n", 
					inet_ntoa(ip->ip_src), ntohs(tcphdr->th_sport));
			}
		}
	}
}

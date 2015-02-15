#include <stdio.h>
#include <string.h>
#include <ctype.h>

#ifndef __linux__
	#include <winsock2.h>
#else
	#include <netinet/in.h>
	#include <arpa/inet.h>
#endif

#include "ip.h"
#include "tcp.h"

void dump_tcp_header(void *iphdr)
{
	char flagbuffer[1024], databuffer[1024];

	int i, cut_size, pos = 0;
	int iphdr_len, tcphdr_len, data_len;
	unsigned char *data_ptr;

	struct tcphdr *tcphdr;
	struct ip *ip = (struct ip *)iphdr;

	iphdr_len = ip->ip_hl << 2;

	tcphdr = (struct tcphdr *)((char *)ip + iphdr_len);
	tcphdr_len = tcphdr->th_off << 2;

	data_len = ntohs(ip->ip_len) - tcphdr_len - iphdr_len;
	data_ptr = (unsigned char*)tcphdr + tcphdr_len;

	if(tcphdr->th_flags & TH_FIN)	 flagbuffer[pos++] = 'F';
	if(tcphdr->th_flags & TH_SYN)	 flagbuffer[pos++] = 'S';
	if(tcphdr->th_flags & TH_RST)	 flagbuffer[pos++] = 'R';
	if(tcphdr->th_flags & TH_PUSH)	flagbuffer[pos++] = 'P';
	if(tcphdr->th_flags & TH_ACK)	 flagbuffer[pos++] = 'A';
	if(tcphdr->th_flags & TH_URG)	 flagbuffer[pos++] = 'U';
	flagbuffer[pos] = '\0';

	cut_size = (data_len > 40)?40:data_len;
	for(i = 0; i < cut_size; i += 1) {
		databuffer[i] = (isprint(data_ptr[i]))?data_ptr[i]:'.';
	}
	databuffer[cut_size] = '\0';

	printf("[TCP][%d->%d][seq : %u][ack : %u] [flags : %s] %s\n", 
			ntohs(tcphdr->th_sport), ntohs(tcphdr->th_dport), 
			ntohl(tcphdr->th_seq), ntohl(tcphdr->th_ack), 
			flagbuffer, databuffer);
}

#include <stdio.h>

#ifndef __linux__
	#include <winsock2.h>
#else
	#include <netinet/in.h>
	#include <arpa/inet.h>
#endif

#include "tcplib.h"

#define	 PSEUDO_HEADER_LEN 12

void make_tcp_header(
	struct tcp_packet *packet, 
	const char *src_ip, uint16_t src_port, 
	const char *dst_ip, uint16_t dst_port, 
	uint32_t seq, uint32_t ack, uint8_t flag
){
	packet->tcphdr.th_seq = htonl(seq);
	packet->tcphdr.th_ack = htonl(ack);
	packet->tcphdr.th_sport = ntohs(src_port);
	packet->tcphdr.th_dport = ntohs(dst_port);
	packet->tcphdr.th_off = 5;
	packet->tcphdr.th_flags = flag;
	packet->tcphdr.th_win = htons(8192);
	packet->tcphdr.th_urp = 0;

	packet->ip.ip_ttl = 0;
	packet->ip.ip_p = IPPROTO_TCP;
	packet->ip.ip_src.s_addr = inet_addr(src_ip);
	packet->ip.ip_dst.s_addr = inet_addr(dst_ip);
	packet->ip.ip_sum = ntohs(sizeof(packet->tcphdr));

	packet->tcphdr.th_sum = 0;
	packet->tcphdr.th_sum = 
		cksum((unsigned short *)&(packet->ip.ip_ttl), 
		PSEUDO_HEADER_LEN + sizeof(packet->tcphdr));
}

void make_ip_header(
	struct ip *ip, const char *src_ip, const char *dst_ip, uint16_t datalen
)
{
	ip->ip_v = 4;
	ip->ip_hl = sizeof(struct ip) >> 2;
	ip->ip_id = 100;
	ip->ip_len = htons(sizeof(struct ip) + datalen);
	ip->ip_off = htons(0);

	ip->ip_ttl = 128;
	ip->ip_p = IPPROTO_TCP;
	ip->ip_src.s_addr = inet_addr(src_ip);
	ip->ip_dst.s_addr = inet_addr(dst_ip);
	
	ip->ip_sum = 0;
	ip->ip_sum = cksum((unsigned short *)ip, sizeof(struct ip));
}

uint16_t cksum(uint16_t *data, uint32_t len)
{
	unsigned long sum = 0;

	for(; len > 1; len -=2 ) {
		sum += *data++;

		if(sum & 0x80000000) 
			sum = (sum & 0xffff) + (sum >> 16);
	}

	if(len == 1) {
		unsigned short i = 0;
		*(unsigned char *)(&i) = *(unsigned char *)data;
		sum += i;
	}

	while(sum >> 16)
		sum = (sum & 0xffff) + (sum >> 16);

	return (sum == 0xffff)?sum:~sum;
}

void strmac_to_buffer(const char *str, uint8_t *mac)
{
	int i;
	unsigned int tmac[6];

	sscanf(str, "%x:%x:%x:%x:%x:%x",
		&tmac[0], &tmac[1], &tmac[2], &tmac[3], &tmac[4], &tmac[5]);
			
	for(i = 0; i < 6; i += 1) {
		mac[i] = (unsigned char)tmac[i];	
	}
}
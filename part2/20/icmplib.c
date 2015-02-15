#include <stdio.h>
#include <string.h>

#ifndef __linux__
	#include <winsock2.h>
#else
	#include <netinet/in.h>
	#include <arpa/inet.h>
#endif

#include "icmplib.h"

void make_ether_header(struct ether_header *ether_header, 
		uint8_t *dest, uint8_t *source, uint16_t type)
{
	memcpy(ether_header->ether_dhost, dest, 6);
	memcpy(ether_header->ether_shost, source, 6);

	ether_header->ether_type = htons(type);
}

void make_ip_header(
	struct ip *ip, const char *src_ip, 
	const char *dst_ip, uint32_t ttl, uint32_t datalen)
{
	ip->ip_v = 4;
	ip->ip_hl = sizeof(struct ip) >> 2;
	ip->ip_id = 100;
	ip->ip_len = htons(sizeof(struct ip) + datalen);
	ip->ip_off = htons(0);

	ip->ip_ttl = ttl;
	ip->ip_p = IPPROTO_ICMP;
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
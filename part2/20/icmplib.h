#ifndef _ICMP_H
#define _ICMP_H

#include <stdint.h>

#define	ETHERTYPE_IP		0x0800		/* IP */

#ifndef __linux__
	#pragma pack(push, 1)
#endif
struct ether_header
{
	uint8_t  ether_dhost[6];		/* destination eth addr	*/
	uint8_t  ether_shost[6];		/* source ether addr	*/
	uint16_t ether_type;		/* packet type ID field	*/
}
#ifndef __linux__
	;
	#pragma pack(pop)
#else
__attribute__ ((__packed__));
#endif

#ifndef __linux__
	#pragma pack(push, 1)
#endif
struct ip
{
	uint8_t ip_hl:4;		/* header length */
	uint8_t ip_v:4;		/* version */
	uint8_t ip_tos;			/* type of service */
	uint16_t ip_len;			/* total length */
	uint16_t ip_id;			/* identification */
	uint16_t ip_off;			/* fragment offset field */
#define	IP_RF 0x8000			/* reserved fragment flag */
#define	IP_DF 0x4000			/* dont fragment flag */
#define	IP_MF 0x2000			/* more fragments flag */
#define	IP_OFFMASK 0x1fff		/* mask for fragmenting bits */
	uint8_t ip_ttl;			/* time to live */
	uint8_t ip_p;			/* protocol */
	uint16_t ip_sum;			/* checksum */
	struct in_addr ip_src, ip_dst;	/* source and dest address */
}
#ifndef __linux__
	;
	#pragma pack(pop)
#else
__attribute__ ((__packed__));
#endif

#ifndef __linux__
	#pragma pack(push, 1)
#endif
struct icmp
{
	uint8_t  icmp_type;
	uint8_t  icmp_code;
	uint16_t icmp_cksum;
	uint16_t icmp_id;
	uint16_t icmp_seq;
}
#ifndef __linux__
	;
	#pragma pack(pop)
#else
__attribute__ ((__packed__));
#endif

#ifndef __linux__
	#pragma pack(push, 1)
#endif
struct icmp_full_packet
{
	struct ether_header ether_header;
	struct ip ip;
	struct icmp icmp;
}
#ifndef __linux__
	;
	#pragma pack(pop)
#else
__attribute__ ((__packed__));
#endif

void make_ether_header(struct ether_header *ether_header, 
		uint8_t *dest, uint8_t *source, uint16_t type);

void make_ip_header(
	struct ip *ip, const char *src_ip, const char *dst_ip, 
	uint32_t ttl, uint32_t datalen
);

void strmac_to_buffer(const char *str, uint8_t *mac);

uint16_t cksum(uint16_t *data, uint32_t len);

#endif
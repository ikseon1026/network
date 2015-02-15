#ifndef _TCPLIB_H
#define _TCPLIB_H

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

typedef	uint32_t tcp_seq;

#ifndef __linux__
	#pragma pack(push, 1)
#endif
struct tcphdr
{
	uint16_t th_sport;		/* source port */
	uint16_t th_dport;		/* destination port */
	tcp_seq th_seq;		/* sequence number */
	tcp_seq th_ack;		/* acknowledgement number */
	uint8_t th_x2:4;		/* (unused) */
	uint8_t th_off:4;		/* data offset */
	uint8_t th_flags;
# define TH_FIN	0x01
# define TH_SYN	0x02
# define TH_RST	0x04
# define TH_PUSH	0x08
# define TH_ACK	0x10
# define TH_URG	0x20
	uint16_t th_win;		/* window */
	uint16_t th_sum;		/* checksum */
	uint16_t th_urp;		/* urgent pointer */
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
struct tcp_packet
{
	struct ether_header ether_header;
	struct ip ip;
	struct tcphdr tcphdr;
}
#ifndef __linux__
	;
	#pragma pack(pop)
#else
__attribute__ ((__packed__));
#endif

void make_tcp_header(
	struct tcp_packet *packet, 
	const char *src_ip, uint16_t src_port, 
	const char *dst_ip, uint16_t dst_port, 
	uint32_t seq, uint32_t ack, uint8_t flag
);

void make_ip_header(
	struct ip *ip, const char *src_ip, const char *dst_ip, uint16_t datalen
);

uint16_t cksum(uint16_t *data, uint32_t len);

void strmac_to_buffer(const char *str, uint8_t *mac);

#endif
#include <stdint.h>

typedef uint32_t u_int32_t;
typedef uint16_t u_int16_t;
typedef uint8_t u_int8_t;
typedef	u_int32_t tcp_seq;

/*
 * TCP header.
 * Per RFC 793, September, 1981.
 */
struct tcphdr
{
	union
	{
		struct
		{
			u_int16_t th_sport;		/* source port */
			u_int16_t th_dport;		/* destination port */
			tcp_seq th_seq;		/* sequence number */
			tcp_seq th_ack;		/* acknowledgement number */
			u_int8_t th_x2:4;		/* (unused) */
			u_int8_t th_off:4;		/* data offset */
			u_int8_t th_flags;
# define TH_FIN	0x01
# define TH_SYN	0x02
# define TH_RST	0x04
# define TH_PUSH	0x08
# define TH_ACK	0x10
# define TH_URG	0x20
			u_int16_t th_win;		/* window */
			u_int16_t th_sum;		/* checksum */
			u_int16_t th_urp;		/* urgent pointer */
		};
		struct
		{
			u_int16_t source;
			u_int16_t dest;
			u_int32_t seq;
			u_int32_t ack_seq;
			u_int16_t res1:4;
			u_int16_t doff:4;
			u_int16_t fin:1;
			u_int16_t syn:1;
			u_int16_t rst:1;
			u_int16_t psh:1;
			u_int16_t ack:1;
			u_int16_t urg:1;
			u_int16_t res2:2;
			u_int16_t window;
			u_int16_t check;
			u_int16_t urg_ptr;
		};
	};
};


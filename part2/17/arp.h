#ifndef ARP_H
#define ARP_H

#include <stdint.h>

#define	ARPOP_REQUEST	1		/* ARP request.  */
#define	ARPOP_REPLY	2		/* ARP reply.  */

#ifndef __linux__
	#pragma pack(push, 1)
#endif
struct arphdr
{
	uint16_t ar_hrd;		/* Format of hardware address.  */
	uint16_t ar_pro;		/* Format of protocol address.  */
	uint8_t ar_hln;		/* Length of hardware address.  */
	uint8_t ar_pln;		/* Length of protocol address.  */
	uint16_t ar_op;		/* ARP opcode (command).  */
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
struct	ether_arp 
{
	struct	arphdr ea_hdr;		/* fixed-size header */

	uint8_t arp_sha[6];	/* sender hardware address */
	uint8_t arp_spa[4];	/* sender protocol address */
	uint8_t arp_tha[6];	/* target hardware address */
	uint8_t arp_tpa[4];	/* target protocol address */
}
#ifndef __linux__
	;
	#pragma pack(pop)
#else
__attribute__ ((__packed__));
#endif

#define	arp_hrd	ea_hdr.ar_hrd
#define	arp_pro	ea_hdr.ar_pro
#define	arp_hln	ea_hdr.ar_hln
#define	arp_pln	ea_hdr.ar_pln
#define	arp_op	ea_hdr.ar_op

void dump_arp_header(struct ether_arp *arp);

#endif
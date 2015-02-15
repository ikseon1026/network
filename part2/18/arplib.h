#ifndef _ARPLIB_H
#define _ARPLIB_H

#include <stdint.h>

#define	ETHERTYPE_IP		0x0800		/* IP */
#define	ETHERTYPE_ARP		0x0806		/* Address resolution */

#define	ARPOP_REQUEST	1		/* ARP request.  */
#define	ARPOP_REPLY	2		/* ARP reply.  */

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

#ifndef __linux__
	#pragma pack(push, 1)
#endif
struct arp_packet 
{
	struct ether_header ether_header;
	struct ether_arp ether_arp;
}
#ifndef __linux__
	;
	#pragma pack(pop)
#else
__attribute__ ((__packed__));
#endif

void make_ether_header(struct ether_header *ether_header, 
		uint8_t *dest, uint8_t *source, uint16_t type);

void make_arp_header(struct ether_arp *ether_arp, 
		uint8_t *sha, uint32_t spa,
		uint8_t *tha, uint32_t tpa, uint32_t op);

void strmac_to_buffer(const char *str, uint8_t *mac);

#endif
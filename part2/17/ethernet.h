#ifndef ETHERNET_H
#define ETHERNET_H

#include <stdint.h>

#define	ETHERTYPE_IP		0x0800		/* IP */
#define	ETHERTYPE_ARP		0x0806		/* Address resolution */

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

void dump_ether_header(struct ether_header *ether_header);

#endif

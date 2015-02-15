#include <stdio.h>
#include <string.h>
#include "arplib.h"

int main(void)
{
	int i;
	unsigned char smac[6], dmac[6];
	unsigned int sip, tip;
	unsigned char *ptr;
	struct arp_packet arp_packet;

	ptr = (unsigned char *)&arp_packet;
	memset(&arp_packet, 0x00, sizeof(arp_packet));

	strmac_to_buffer("11:22:33:44:55:66", smac);
	strmac_to_buffer("aa:bb:cc:dd:ee:ff", dmac);

	sip = 0x11223344;
	tip = 0x55667788;

	make_ether_header(
		&(arp_packet.ether_header), dmac, smac, ETHERTYPE_ARP);

	make_arp_header(&(arp_packet.ether_arp), smac, sip, dmac, tip, 1);

	printf("struct ether_header : %lu\n",
		(unsigned long)sizeof(struct ether_header));

	printf("struct ether_arp : %lu\n",
		(unsigned long)sizeof(struct ether_arp));

	printf("struct arp_packet : %lu\n\n",
		(unsigned long)sizeof(struct arp_packet));

	for(i=0; i<sizeof(arp_packet); i++) {
		printf("%02x ", ptr[i]);

		if((i+1) %16 == 0) printf("\n");
	}

	printf("\n");

	return 0;
}				
#include <stdio.h>

#include "ethernet.h"

void dump_ether_header(struct ether_header *ether_header)
{
	unsigned char *smac = ether_header->ether_shost;
	unsigned char *dmac = ether_header->ether_dhost;

	printf("[ETHERNET] "\
		"%02x:%02x:%02x:%02x:%02x:%02x ->"\
		"%02x:%02x:%02x:%02x:%02x:%02x\n",
		smac[0], smac[1], smac[2], smac[3], smac[4], smac[5],
		dmac[0], dmac[1], dmac[2], dmac[3], dmac[4], dmac[5]);		
}

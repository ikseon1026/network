#include <stdio.h>
#include "pcap.h"

int main(void)
{
	pcap_if_t *alldevs;            
	pcap_if_t *d;                    
	int i = 0;

	char errbuf[PCAP_ERRBUF_SIZE];
       
	if(pcap_findalldevs(&alldevs, errbuf) < 0) {
		printf("pcap_findalldevs error\n");
		return 1;
	}
   
	for(d=alldevs; d; d=d->next)
	{
		printf("0x%p : %d. %s",d, ++i, d->name);

		if(d->description) printf(" (%s)", d->description);
		printf("\n");
	}
       
	pcap_freealldevs(alldevs);

	return 0;
}

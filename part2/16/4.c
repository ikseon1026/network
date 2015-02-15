#include <stdio.h>
#include <string.h>

#ifndef __linux__
	#include <winsock2.h>
#else
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
#endif

#include "pcap.h"

int main(void)
{
	pcap_if_t *alldevs;
	pcap_if_t *d;
	struct pcap_addr *a;
	int i = 0;
	int no;

	char errbuf[PCAP_ERRBUF_SIZE];
   
	if(pcap_findalldevs(&alldevs, errbuf) < 0) {
		printf("pcap_findalldevs error\n");
		return 1;
	}
   
	for(d=alldevs; d; d=d->next) {
		printf("%d :  %s\n",++i, d->name);
	}
   
	printf("number : ");	
	scanf("%d", &no);

	if(!(no > 0 && no <= i)) {
		printf("number error\n");
		return 1;
	}

	for(d=alldevs, i=0; d; d=d->next) {
		if(no == ++i)  break;
	}

	printf("name : %s\n", d->name);
	if(d->description) 
		printf("description : %s\n", d->description);

	for(a = d->addresses; a; a=a->next) {
		struct sockaddr_in *in_addr
			= (struct sockaddr_in *)a->addr;

		switch(a->addr->sa_family) {
			case AF_INET:
				printf("address : %s\n", inet_ntoa(in_addr->sin_addr));
				break;
		}	
	}

	pcap_freealldevs(alldevs);

	return 0;
}

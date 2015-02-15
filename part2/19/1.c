#include <stdio.h>

#ifndef __linux__
	#include <winsock2.h>
#else
	#include <netinet/in.h>
	#include <arpa/inet.h>
#endif

enum {ARGV_CMD, ARGV_START_IP, ARGV_END_IP};

int main(int argc, char **argv)
{
	unsigned int ip, start_ip, end_ip;
	struct in_addr addr;

	if(argc != 3) {
		printf("usage : %s [start ip] [end ip]\n", argv[ARGV_CMD]);
		return 1;
	}
	
	start_ip = ntohl(inet_addr(argv[ARGV_START_IP]));
	end_ip = ntohl(inet_addr(argv[ARGV_END_IP]));
		
	for(ip = start_ip; ip <=end_ip; ip++) {
		addr.s_addr = htonl(ip);

		printf("%s : (%u)\n", inet_ntoa(addr), ip);	
	}

	return 0;
}

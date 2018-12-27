#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <net/if.h>

enum {ARGV_CMD, ARGV_INTERFACE};

int main(int argc, char **argv)
{
	int sock;
	struct ifreq ifr;
	unsigned char *mac = NULL;

	if(argc != 2) {
		printf("%s [Interface name]\n", argv[ARGV_CMD]);
		return 1;
	}

	memset(&ifr, 0x00, sizeof(ifr));
	strcpy(ifr.ifr_name, argv[ARGV_INTERFACE]);

	int fd=socket(AF_UNIX,SOCK_DGRAM,0);

	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket ");
		return 1;
	}

	if (ioctl(fd,SIOCGIFHWADDR,&ifr) < 0) {
		perror("ioctl ");
		return 1;
	}

	mac = ifr.ifr_hwaddr.sa_data;

	printf("%s : %02x:%02x:%02x:%02x:%02x:%02x\n",
		ifr.ifr_name, mac[0], mac[1], mac[2], mac[3],
		mac[4], mac[5]);

	close(sock);
	return 0;
}				

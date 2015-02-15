#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ether.h>

#define	BUFSIZE 2048

int main(int argc, char **argv)
{
	int sock, len;
	char buffer[BUFSIZE];

	if((sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0) {
		perror("socket");
		return 1;
	}

	while((len = read(sock, buffer, BUFSIZE)) >= 0) {
		printf("length : %d\n", len);
	}

	close(sock);

	return 0;
}

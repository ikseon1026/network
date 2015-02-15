#include <stdio.h>

#ifndef __linux__
	#include <winsock2.h>
#else
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
#endif

int main(void)
{
	struct in_addr a, b;

	a.s_addr = inet_addr("1.2.3.4");
	b.s_addr = inet_addr("5.6.7.8");

	printf("a : %s, b : %s\n", inet_ntoa(a), inet_ntoa(b));

	printf("a : %s\n", inet_ntoa(a));
	printf("b : %s\n", inet_ntoa(b));

	return 0;
}				

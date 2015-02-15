#include <stdio.h>
#include <string.h>

#ifndef __linux__
	#include <winsock2.h>
	#include <windows.h>
	#define perror(msg) winperror(msg)

	void winperror(char *msg);
#else
	#include <unistd.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
#endif

#define	PORT	1234

int main(void)
{
	int sock;
	struct sockaddr_in addr, client_addr;
	char recv_buffer[1024];
	int recv_len;
	int addr_len;

#ifndef __linux__
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

	if((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket ");
		return 1;
	}

	memset(&addr, 0x00, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(PORT);

	if(bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("bind ");
		return 1;
	}

	printf("waiting for messages\n");

	addr_len = sizeof(client_addr);
	if((recv_len = recvfrom(sock, recv_buffer, 1024, 0,
		(struct sockaddr *)&client_addr, &addr_len)) < 0) {
		perror("recvfrom ");
		return 1;
	}

	recv_buffer[recv_len] = '\0';
	
	printf("ip : %s\n", inet_ntoa(client_addr.sin_addr));
	printf("received data : %s\n", recv_buffer);

	sendto(sock, recv_buffer, strlen(recv_buffer), 0, 
		(struct sockaddr *)&client_addr, sizeof(client_addr));

#ifndef __linux__
	closesocket(sock);
	WSACleanup();
#else
	close(sock);
#endif

	return 0;
}				

#ifndef __linux__
void winperror(char *msg)
{
	LPVOID lpMsgBuf;

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER|
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);

	printf("%s : %s\n", msg, lpMsgBuf);

	LocalFree(lpMsgBuf);
}
#endif

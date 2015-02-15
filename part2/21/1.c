#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

enum {ARGV_CMD, ARGV_IP, ARGV_PORT};

int main(int argc, char **argv)
{
	int sock;
	struct sockaddr_in addr;

#ifndef __linux__
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

	if(argc != 3) {
		printf("usage : %s [ip] [port]\n", argv[ARGV_CMD]);
		return 1;
	}

	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket ");
		return 1;
	}

	memset(&addr, 0x00, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(argv[ARGV_IP]);
	addr.sin_port = htons(atoi(argv[ARGV_PORT]));

	if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("connect ");
	}else{ 
		printf("%s:%s opend\n", argv[ARGV_IP], argv[ARGV_PORT]);
	}

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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#ifndef __linux__
	#include <winsock2.h>
	#include <windows.h>
	#define perror(msg) winperror(msg)

	void winperror(char *msg);
#else
	#include <unistd.h>
	#include <fcntl.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
#endif

enum {ARGV_CMD, ARGV_IP, ARGV_PORT};

int connect_timeout(
	int sock, struct sockaddr *addr, unsigned long len, int sec);

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

	if(connect_timeout(sock, (struct sockaddr *)&addr, sizeof(addr), 1) < 0) {
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

int connect_timeout(
	int sock, struct sockaddr *addr, unsigned long len, int sec)
{
	fd_set fread, fwrite;
	struct timeval tv;
	int res;
	int sock_error = 0;
	unsigned int errsize;
	unsigned long nonblock = 1;

#ifndef __linux__
	if(ioctlsocket(sock, FIONBIO, &nonblock) < 0) {
		perror("ioctlsocket ");
		return -1;
	}
#else
	if(fcntl(sock, F_SETFL, O_NONBLOCK) < 0) {
		perror("fcntl ");
		return -1;
	}
#endif

	FD_ZERO(&fread);
	FD_ZERO(&fwrite);

	FD_SET(sock, &fread);
	FD_SET(sock, &fwrite);

	tv.tv_sec = 1;
	tv.tv_usec = 0;

	if(connect(sock, addr, len) < 0) {
#ifndef __linux__
		if(WSAGetLastError() != WSAEWOULDBLOCK) return -1;
#else
		if(errno != EINPROGRESS) return -1;
#endif
	}

	if((res = select(sock+1, &fread, &fwrite, NULL, &tv)) < 0) {
		perror("select ");
		return -1;
	}

	if(res == 0) { // time expired
		return -1; 
	}

	if(FD_ISSET(sock, &fread) || FD_ISSET(sock, &fwrite)) {
		errsize = sizeof(sock_error);

		if(getsockopt(
			sock, SOL_SOCKET, SO_ERROR, (void *)&sock_error, &errsize) < 0) {
			perror("getsockopt");
			return -1;
		}

		if(!sock_error) {  // no socket error
			return 0;
		}
	}

	return -1;
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

#include <stdio.h>

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

int main(void)
{
	int sock;
	unsigned int sendsize = 0;
	unsigned int recvsize = 0;
	unsigned int optlen;

#ifndef __linux__
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket ");
		return 1;
	}	
	
	optlen = sizeof(sendsize);
	getsockopt(sock, SOL_SOCKET, SO_SNDBUF, (char*)&sendsize, &optlen);

	optlen = sizeof(recvsize);
	getsockopt(sock, SOL_SOCKET, SO_RCVBUF, (char*)&recvsize, &optlen);

	printf("sendsize : %u\n", sendsize);
	printf("recvsize : %u\n", recvsize);

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

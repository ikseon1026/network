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
	struct sockaddr_in addr;
	char buffer[1024];
	const char *msg = "hello!! world!!";
	int recv_len;

#ifndef __linux__
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket ");
		return 1;
	}

	memset(&addr, 0x00, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(PORT);

	if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("connect ");
		return 1;
	}

	if(send(sock, msg, strlen(msg), 0) < 0){
		perror("send ");
		return 1;
	}

	if((recv_len = recv(sock, buffer, 1024, 0)) < 0) {
		perror("recv ");
		return 1;
	}

	buffer[recv_len] = '\0';

	printf("received data : %s\n", buffer);

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

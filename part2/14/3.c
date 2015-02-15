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

#define	PORT	8080

int main(void)
{
	int sock, client_sock;
	struct sockaddr_in addr, client_addr;
	char buffer[1024];
	int len, addr_len, recv_len;

	const char *http_response = 
		"HTTP/1.1 200 OK\r\n"
		"Content-Type: text/html\r\n\r\n"
		"<html><body>\r\n"
		"<h1>Hello World!!</h1>\r\n"
		"</body></html>";

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
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(PORT);

	if(bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("bind ");
		return 1;
	}

	if(listen(sock, 5) < 0) {
		perror("listen ");
		return 1;
	}	

	addr_len = sizeof(client_addr);

	printf("waiting for client\n");

	while((client_sock = accept(sock, 
		(struct sockaddr *)&client_addr, &addr_len)) > 0) {
		printf("client ip : %s\n", inet_ntoa(client_addr.sin_addr));	

		if((recv_len = recv(client_sock, buffer, 1024, 0)) < 0){
			perror("recv ");
			break;
		}
		buffer[recv_len] = '\0';

		printf("%s\n", buffer);

		send(client_sock, http_response, strlen(http_response), 0);

		printf("%s\n", http_response);

#ifndef __linux__
		closesocket(client_sock);
#else
		close(client_sock);
#endif
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

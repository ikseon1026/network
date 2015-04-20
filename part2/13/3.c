#include <stdio.h>

#ifndef __linux
	#include <winsock2.h>
	#include <windows.h>
	#define perror(msg) winperror(msg)

	void winperror(char *msg);
#endif

int main(void)
{
	perror("hello");
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

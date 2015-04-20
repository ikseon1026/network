#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

int main(void)
{
	LPVOID lpMsgBuf;

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER|
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);

	printf("WSAGetLastError : %d\n", WSAGetLastError());
	printf("lpMsgBuf : %s\n", lpMsgBuf);

	LocalFree(lpMsgBuf);

	return 0;
}
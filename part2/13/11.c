#include<stdio.h>
#include<windows.h>

DWORD WINAPI thread_function(LPVOID param){
	while(1) {
		printf("%s\n", (char*)param);
		Sleep(1000);
	}
}

int main(void)
{
	DWORD thread_id;
	char *msg = "hi"; 

	CreateThread(NULL, 0, thread_function, msg, 0, &thread_id);

	while(1) {
		printf("%s\n", "hello!!");
		Sleep(1000);
	}

	return 0;
}

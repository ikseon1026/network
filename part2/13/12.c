#include <stdio.h>

#ifndef __linux__ /* for windows */
	#include <windows.h>
	#define CREATE_THREAD(id,function,param) \
		CreateThread(NULL,0,function,param,0,&id);
	#define THREAD_TYPE_RETURN DWORD WINAPI
	#define THREAD_TYPE_PARAM LPVOID
	#define THREAD_TYPE_ID DWORD
	#define SLEEP(x)	Sleep(x*1000)
#else	/* for linux */
	#include <pthread.h>
	#include <unistd.h>
	#define CREATE_THREAD(id,function,param) \
		pthread_create(&id,NULL,function,param);
	#define THREAD_TYPE_RETURN void*
	#define THREAD_TYPE_PARAM void*
	#define THREAD_TYPE_ID pthread_t
	#define SLEEP(x)	sleep(x)
#endif

THREAD_TYPE_RETURN thread_function(THREAD_TYPE_PARAM param)
{
	while(1) {
		printf("%s\n", (char*)param);
		SLEEP(1);
	}

	return 0;
}

int main(void)
{
	THREAD_TYPE_ID thread_id;
	char *msg = "hi"; 

	CREATE_THREAD(thread_id, thread_function, msg);

	while(1) {
		printf("%s\n", "hello!!");
		SLEEP(1);
	}

	return 0;
}				

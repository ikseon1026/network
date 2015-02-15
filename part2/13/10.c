#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *thread_function(void *param)
{
	while(1) {
		printf("%s\n", (char*)param);
		sleep(1);
	}
}

int main(void)
{
	pthread_t thread_id;

	char *msg = "hi";

	pthread_create(&thread_id, NULL, thread_function, msg);

	while(1) {
		printf("hello!\n");
		sleep(1);
	}

	return 0;
}				

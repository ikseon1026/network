#include <stdio.h>
#include <string.h>

void changeme(char *str);

int main(void)
{
	char a[] = "hello world";

	printf("before [%p] : %s\n", a, a);

	changeme(a);

	printf("after [%p] : %s\n", a, a);
	
	return 0;
}				

void changeme(char *str)
{
	int i;

	printf("&str : %p\n", &str);

	for(i = 0; i < strlen(str); i += 1) {
		printf("[%p] : %c -> %c\n", (str+i), *(str+i), *(str+i)+1);
		(*(str+i))++;
	}
}

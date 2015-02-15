#include <stdio.h>

int main(void)
{
	int i;
	char str[] = "hello";

	printf("%s\n", str);

	for(i = 0; i < sizeof(str)/sizeof(char); i++) {
		printf("str[%d] : %c [ %d]\n", i, str[i], str[i]);
	}

	return 0;
}				

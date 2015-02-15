#include <stdio.h>
#include <string.h>

int main(void)
{
	const char *s1 = "helloworld";
	const char *s2 = "hello";

	if(!memcmp(s1, s2, 5)) {
		printf("%c %c %c %c %c\n", s1[0], s1[1], s1[2], s1[3], s1[4]);
		printf("%c %c %c %c %c\n", s2[0], s2[1], s2[2], s2[3], s2[4]);
	}
	
	return 0;
}				

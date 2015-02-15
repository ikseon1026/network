#include <stdio.h>
#include <string.h>

int main(void)
{
	char p1[] = "hello";
	char p2[] = "hello";

	if(p1 == p2) {
		printf("p1 == p2\n");
	}else {
		printf("p1 : %p\n", p1);
		printf("p2 : %p\n", p2);
	}

	if(!strcmp(p1, p2)) {
		printf("%s == %s\n", p1, p2);
	}
	
	return 0;
}				

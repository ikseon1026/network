#include <stdio.h>

int main(void)
{
	printf("char : %c %c \n", 'a', 65);
	printf("hex : %x\n", 100);
	printf("dec : %d\n", 100);
	printf("octal : %o\n", 100);
	printf("space : %10d \n", 1234);
	printf("0 : %010d \n", 1234);
	printf("float : %4.2f %E \n", 1.234, 1.234);
	printf("string : %s \n", "Hello!! World!!");	

	return 0;
}				

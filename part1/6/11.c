#include <stdio.h>

int main(void)
{
	int a;	
	char buf[10];

	printf("number : ");
	scanf("%d", &a);
	printf("a[%p] : %d\n",&a, a);

	printf("string : ");
	scanf ("%s", buf);
	printf("buf[%p] : %s\n", buf, buf);	

	return 0;
}

#include <stdio.h>

#ifndef __linux__
	#pragma pack(push, 1)
#endif
struct data
{
	char a;
	int b;
} 
#ifndef __linux__
	;
	#pragma pack(pop)
#else
	__attribute__((packed));
#endif

int main(void)
{
	printf("data : %lu Byte\n", (unsigned long)sizeof(struct data));

	return 0;
}	

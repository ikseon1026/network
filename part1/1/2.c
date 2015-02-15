#include <stdio.h>

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef short int int16_t;
typedef unsigned short int uint16_t;

int main(void)
{
	int8_t a = 1;
	uint8_t b = 2;
	int16_t c = 3;
	uint16_t d = 4;

	printf("int8_t(signed char) : %lu\n", (unsigned long)sizeof(a));
	printf("uint8_t(unsigned char) : %lu\n", (unsigned long)sizeof(b));
	printf("int16_t(short int) : %lu\n", (unsigned long)sizeof(c));
	printf("uint16_t(unsigned short int) : %lu\n", (unsigned long)sizeof(d));

	return 0;
}				
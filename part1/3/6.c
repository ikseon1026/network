#include <stdio.h>

struct data
{
	union {
		struct {
			char data_a;
			int data_b;
		};

		struct {
			char a;
			int b;
		};
	};
};

int main(void)
{
	struct data data;

	data.a = 1;	
	data.data_b = 2;

	printf("data.data_a : %d\n", data.data_a);
	printf("data.data_b : %d\n", data.data_b);

	printf("data.a : %d\n", data.a);	
	printf("data.b : %d\n", data.b);	

	return 0;
}

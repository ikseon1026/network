#include <stdio.h>

struct data
{
	char a;
	int b;
};

int main(void)
{
	struct data data_type_var;

	printf("char : %lu Byte\n", (unsigned long)sizeof(char));
	printf("int : %lu Byte\n", (unsigned long)sizeof(int));
	printf("struct data : %lu Byte\n", (unsigned long)sizeof(struct data));

	data_type_var.a = 'A';
	data_type_var.b = 100;

	printf("data_type_var.a : %c\n", data_type_var.a);
	printf("data_type_var.b : %d\n", data_type_var.b);

	return 0;
}	

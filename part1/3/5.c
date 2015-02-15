#include <stdio.h>

union data 
{
	char a;
	int b;
};

int main(void)
{
	union data data_type_var;

	printf("union data : %luByte\n", (unsigned long)sizeof(union data));
	printf("union data a : %luByte\n", (unsigned long)sizeof(data_type_var.a));
	printf("union data b : %luByte\n", (unsigned long)sizeof(data_type_var.b));

	data_type_var.b = 0x11223344;

	printf("data_type_var.a : %x\n", data_type_var.a);
	printf("data_type_var.b : %x\n", data_type_var.b);

	data_type_var.a = 0x55;

	printf("data_type_var.a : %x\n", data_type_var.a);
	printf("data_type_var.b : %x\n", data_type_var.b);
	
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "functions.h"

int main()
{
	short* code = NULL;
	int all_bits;
	printf("Enter the lenght of the code: ");
	scanf("%d", &all_bits);

	CustomCode(code, all_bits);

	return 0;
}
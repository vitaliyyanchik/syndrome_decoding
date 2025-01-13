#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void EnterCode(short* code, int all_bits)
{
	for (int i = 0; i < all_bits; ++i)
	{
		scanf("%hd", &code[i]);
	}
}

int ControlBitsCounter(int all_bits)
{
	int control_bits = 0;
	for (int i = 1; i < all_bits; ++i)
	{
		if ((1 << (i - 1)) < all_bits && all_bits < (1 << i))
		{
			control_bits = i;
			break;
		}
	}

	return control_bits;
}

void CalculateSyndrome(short* code, int all_bits, short* syndrome, int control_bits)
{
	int pos = 0;
	for (int i = 0; i < control_bits; ++i) // цикл, що відповідає за заповнення масиву, який відповідає за синдром коду
	{
		pos = 1 << i;
		for (int j = 0; j < all_bits; ++j) //цикл, що відповідає за проходження по всьому коду Геммінга
		{
			if ((j+1) & pos) //якщо поточний індекс (у двійковому представленні) біта має одиницю на відповідній позиції,
				// що дорівнює номеру контрольного біта, 
				//який використовується для обрахунку поточного синдрому
			{
				syndrome[i] ^= code[j];
			}
		}
	}
}

int FindError(short* syndrome, int control_bits) //переводить синдром, який є позицією пошкодженого біта, з двійкової у десяткову систему
{
	int faulty_bit = 0;
	for (int i = 0; i < control_bits; ++i)
	{
		if (syndrome[i])
		{
			faulty_bit += 1 << i;
		}
	}

	return faulty_bit;
}

int CorrectCode(short* code, int all_bits, short* syndrome, int control_bits)
{
	int error = FindError(syndrome, control_bits);
	if (!error)
	{
		printf("\nHere is no errors!");
		return 0;
	}

	if (error > all_bits)
	{
		printf("\nHere is more than two errors! Impossible to correct!");
		return -1;
	}

	printf("\nError was in %d bit", error);
	code[error - 1] ^= 1;
	return 1;
}

void PrintCode(short* code, int all_bits)
{
	for (int i = 0; i < all_bits; ++i)
	{
		printf("%hd ", code[i]);
	}
}

void CustomCode(short* code, int all_bits)
{
	code = (short*)calloc(all_bits, sizeof(short));
	if (!code)
	{
		printf("Memory allocation failed for code!");
		return;
	}

	printf("Enter your code: ");
	EnterCode(code, all_bits);
	printf("Your code: \n");
	PrintCode(code, all_bits);

	int control_bits = ControlBitsCounter(all_bits);
	short* syndrome = (short*)calloc(control_bits, sizeof(short));
	if (!syndrome)
	{
		printf("Memory allocation failed for syndrome!");
		free(code);
		return;
	}
	CalculateSyndrome(code, all_bits, syndrome, control_bits);
	
	int res = CorrectCode(code, all_bits, syndrome, control_bits);
	if (res > 0)
	{
		printf("\nCorrected code: \n");
		PrintCode(code, all_bits);
	}
	
	free(syndrome);
	free(code);
}
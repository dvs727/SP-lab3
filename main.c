#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_OF_ELEMENTS 4

int main()
{
	srand(time(0));

	int* mas = (int*)malloc(NUM_OF_ELEMENTS);

	mas[0] = 50;
	mas[3] = 51;
	mas[1] = 49;
	mas[2] = 53;

	for (int i = 0; i < NUM_OF_ELEMENTS; ++i){
		//mas[i] = 10 + rand() % 89;
		printf("%u ", mas[i]);
	}
	printf("\n");

	int idx_of_min = 0, idx_of_max = 0;
	int min, max;
	
	asm(
		".intel_syntax noprefix\n\t"
		"mov	r11d, [rax]\n\t"
		"mov 	edx, r11d\n\t"
		"mov 	ecx, r11d\n\t"
		"mov 	r10d, 0\n\t"
		"jmp	COMPARE\n\t"
		"LOOP:\n\t"
		"mov 	r11d, [rax + r10 * 4]\n\t"
		"cmp	r11d, ecx\n\t"
		"jle	SEARCH_FOR_MAX\n\t"
		"mov 	edi, r10d\n\t"
		"mov	r11d, r11d\n\t"
		"mov 	ecx, r11d\n\t"
		"SEARCH_FOR_MAX:\n\t"
		"cmp	r11d, edx\n\t"
		"jge	INCREMENT\n\t"
		"mov 	esi, r10d\n\t"
		"mov	r11d, r11d\n\t"
		"mov	edx, r11d\n\t"
		"INCREMENT:\n\t"
		"add 	r10d, 1\n\t"
		"COMPARE:\n\t"
		"cmp 	r10d, 3\n\t"
		"jle	LOOP\n\t"
		: "=c" (max), "=D" (idx_of_max), "=d" (min), "=S" (idx_of_min)
		: "a" (mas), "b" (NUM_OF_ELEMENTS), "c" (max), "D" (idx_of_max),"d" (min), "S" (idx_of_min)
		:
	);

/*
	min = mas[0];
	max = mas[0];

	for (int i = 0; i < NUM_OF_ELEMENTS; ++i){
		int elem = mas[i];
		if(elem > max){
			idx_of_max = i;
			max = elem;
		}
		if(elem < min){
			idx_of_min = i;
			min = elem;
		}
	}
*/

	printf("Минимальное значение: %u\n", min);
	printf("Позиция минимального значения: %u\n", idx_of_min);
	printf("Максимальное значение: %u\n", max);
	printf("Позиция максимального значения: %u\n", idx_of_max);

	return 0;
}

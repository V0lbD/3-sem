#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef enum check_correct {
	degree_incorrect,
	malloc_error,
	ok
} check_correct;

check_correct convert(char** result, long int number, long int degree) // если не передавать в функцию указатель, а делать через return, то как реализовать проверку входных данных?
{
	if (degree < 1 || degree > 5) {
		return degree_incorrect;
	}
	if (number == 0) {
		*result = (char*)malloc(sizeof(char) * 2); // 2, т.к. нужно вывести "0\0"
		if ((*result) == NULL) {
			return malloc_error;
		}

		(*result)[0] = '0';
		(*result)[1] = '\0';
		return ok;
	}
	int flag = 0;
	if (number < 0) {
		flag = 1;
		number = -number;
	}

	int counter = 0, i = 0;
	char* buf = (char*)malloc(sizeof(long int) * 8 + 1);
	char* tmp = buf; // для удаления ненужных символов
	char* begin = buf; // для free

	if (buf == NULL) {
		return malloc_error;
	}

	buf[sizeof(long int) * 8] = '\0';
	buf += sizeof(long int) * 8 - 1;

	while (number != 0) { // обработать number == 0
		long int bin = 0;
		bin = number & ((1 << degree) - 1);
		if (bin < 10) {
			*buf = (char)(bin + 48);
		}
		else if (bin > 9 && bin < 33) {
			*buf = (char)(bin + 55);
		}

		number >>= degree;
		buf--;
		counter++;
	}

	if (!(tmp = (char*)malloc(sizeof(char) * (counter + (flag == 1 ? 2 : 1)))))
	{
		free(begin);
		return malloc_error;
	}
	else if (flag == 1)
	{
		tmp[0] = '-';
	}

	tmp[counter + flag] = '\0';

	for (i = 0 + flag; i < counter + flag; i++) {
		tmp[i] = buf[i + 1 - flag]; // strncpy
	}

	(*result) = tmp;
	free(begin);

	return ok;
}

int main()
{
	char* result = NULL;
	long int number = 0, degree = 0;
	check_correct res;

	printf("Please, enter a number and a degree:\n");

	if (scanf("%li%li", &number, &degree) != 2) {
		printf("You have entered something wrong!\n");
		return -1;
	}

	res = convert(&result, number, degree);

	switch (res) {
	case degree_incorrect:
		printf("Your degree is not right!\n");
		break;

	case malloc_error:
		printf("Not enough memory!\n");
		break;

	default:
		printf("Your result is %s\n", result);
		break;
	}

	free(result);

	return 0;
}
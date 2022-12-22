#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

long int combination(int n, int k)
{
	if (k == 0 || k == n)
	{
		return 1;
	}

	return combination(n - 1, k - 1) * n / k;
}

void implementation_of_combinations(int k, int l, int actual_k, int actual_l, int number, int* arr, long int* counter, int digit)
{
	if (actual_l > l) {
		return;
	}

	if (k - actual_k < l - actual_l) {
		return;
	}

	number |= (digit << actual_k);

	if (actual_k == k && actual_l == l) {
		arr[*counter] = number;
		(*counter)++;
		return;
	}

	if (actual_k == k && actual_l != l) {
		return;
	}

	actual_k++;
	implementation_of_combinations(k, l, actual_k, actual_l + 1, number, arr, counter, 1);
	implementation_of_combinations(k, l, actual_k, actual_l, number, arr, counter, 0);

}

void exactly(int k, int l, int** arr, long int* size, char* status)
{
	if (l == 0) {
		*size = 1;
		(*arr) = (int*)malloc(sizeof(int) * (*size));
		if ((*arr) == NULL) {
			*status = 'n';
			return;
		}

		(*arr)[0] = 0;
		return;
	}

	*size = combination(k - 1, l - 1);

	(*arr) = (int*)malloc(sizeof(int) * (*size));
	if ((*arr) == NULL) {
		*status = 'n';
		return;
	}

	int number = 0;
	number |= (1 << k - 1);

	int actual_k = 0, actual_l = 0;
	long int counter = 0;

	implementation_of_combinations(k - 2, l - 1, actual_k, actual_l + 1, number, *arr, &counter, 1);
	implementation_of_combinations(k - 2, l - 1, actual_k, actual_l, number, *arr, &counter, 0);
}

void exactly_in_a_row(int k, int l, int** arr, long int* size, char* status)
{
	if (l == 0) {
		*size = 1;
		(*arr) = (int*)malloc(sizeof(int) * (*size));
		if ((*arr) == NULL) {
			*status = 'n';
			return;
		}

		(*arr)[0] = 0;
		return;
	}

	*size = 1;
	(*arr) = (int*)malloc(sizeof(int) * (*size));

	if ((*arr) == NULL) {
		*status = 'n';
		return;
	}

	int number = 0, i = 0;

	for (i = k - 1; i > k - 1 - l; i--) {
		number |= (1 << i);
	}

	(*arr)[0] = number;
}

int main()
{
	printf("1 - exactly l units in a number with k bits;\n");
	printf("2 - exactly l units in a row in a number with k bits.\n");
	printf("Your choice: ");

	int choice = 0;
	if (scanf("%d", &choice) != 1) {
		printf("You have entered something wrong!\n");
		return -1;
	}

	switch (choice) {
	case 1:
	{
		int k = 0;
		printf("k = ");
		if (scanf("%d", &k) != 1) {
			printf("You have entered wrong k!\n");
			return -3;
		}

		if (k > 32) {
			printf("You have entered too big k!\n");
			return -4;
		}

		if (k < 1) {
			printf("You have entered too small k!\n");
			return -4;
		}

		int l = 0;
		printf("l = ");
		if (scanf("%d", &l) != 1) {
			printf("You have entered wrong l!\n");
			return -5;
		}

		if (l > 32) {
			printf("You have entered too big l!\n");
			return -6;
		}

		if (l < 1) {
			printf("You have entered too small l!\n");
			return -6;
		}


		if (l > k) {
			printf("Your l is greater than k!\n");
			return -7;
		}

		int* result = NULL;
		int size = 0;
		char status = 'y';

		exactly(k, l, &result, &size, &status);

		if (status == 'n') {
			printf("Memory was not allocated!\n");
			return -8;
		}
		else {
			printf("Your numbers is:\n");
			int i = 0;
			for (i = 0; i < size; i++) {
				printf("%d ", result[i]);
			}

			free(result);
		}

		break;
	}

	case 2:
	{
		int k = 0;
		printf("k = ");
		if (scanf("%d", &k) != 1) {
			printf("You have entered wrong k!\n");
			return -3;
		}

		if (k > 32) {
			printf("You have entered too big k!\n");
			return -4;
		}

		if (k < 1) {
			printf("You have entered too small k!\n");
			return -4;
		}

		int l = 0;
		printf("l = ");
		if (scanf("%d", &l) != 1) {
			printf("You have entered wrong l!\n");
			return -5;
		}

		if (l > 32) {
			printf("You have entered too big l!\n");
			return -6;
		}

		if (l < 0) {
			printf("You have entered too small l!\n");
			return -6;
		}

		if (l > k) {
			printf("Your l is greater than k!\n");
			return -7;
		}


		int* result = NULL;
		long int size = 0;
		char status = 'y';

		exactly_in_a_row(k, l, &result, &size, &status);

		if (status == 'n') {
			printf("Memory was not allocated!\n");
			return -8;
		}
		else {
			printf("Your numbers is:\n");
			int i = 0;
			for (i = 0; i < size; i++) {
				printf("%d ", result[i]);
			}

			free(result);
		}

		break;
	}

	default:
		printf("You have entered a wrong number!\n");
		return -2;
	}

	return 0;
}
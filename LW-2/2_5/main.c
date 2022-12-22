#define _CRT_SECURE_NO_WARNINGS
#define SIZE 10
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generation_arr(double arr[], int size, double A, double B)
{
    for (int i = 0; i < size; i++) {
        arr[i] = (double)rand() / RAND_MAX * (B - A) + A;
        // arr[i] = A + rand() % (int)(B - A + 1); // для проверки вывода
    }
}

double* max_element(double arr[], int size)
{
    double* res = &arr[0];
    res = &arr[0];
    int i = 0;

    for (i = 0; i < size; i++) {
        if (arr[i] > *res) {
            res = &arr[i];
        }
    }

    return res;
}

double* min_element(double arr[], int size)
{
    double* res = &arr[0];
    int i = 0;

    for (i = 0; i < size; i++) {
        if (arr[i] < *res) {
            res = &arr[i];
        }
    }

    return res;
}

void swap(double* number_1, double* number_2) {
    double tmp = *number_1;
    *number_1 = *number_2;
    *number_2 = tmp;
}

void printing(double arr[], int size)
{
    for (int i = 0; i < size; i++) {
        printf("%.3f ", arr[i]);
    }
    printf("\n");
}
int counter_of_unique(double arr[], int size)
{
    int i = 0, j = 0;
    double tmp = arr[0];

    for (i = 1; i < size; i++) {
        for (j = i; j < size; j++) {
            if (arr[i] == arr[j] && j != i) {
                arr[j] = tmp;
            }
        }
    } // заменили повторяющиеся элементы на первый

    int counter = 1;

    for (i = 1; i < size; i++) {
        if (arr[i] != tmp) {
            counter++;
        }
    }

    return counter;
}

void new_arr_of_unique(double arr[], int size, double* new_arr)
{
    int i = 0, j = 1;
    new_arr[0] = arr[0];
    for (i = 1; i < size; i++) {
        if (arr[i] != arr[0]) {
            new_arr[j] = arr[i];
            j++;
        }
    }
}

int main()
{
    srand(time(NULL));
    int size = SIZE;
    double A = 0., B = 0.;

    printf("Enter the range boundaries:\n");
    if (scanf("%lf%lf", &A, &B) != 2) {
        printf("You have entered something wrong!\n");
        return -1;
    }

    if (A > B) {
        printf("You have mixed up the order of the numbers!\n");
        return -2;
    }

    double arr[SIZE]; // про то, почему нельзя объявлять в компиляторах от Microsoft статические массивы никак иначе, кроме константных размеров https://qna.habr.com/q/690167
    generation_arr(arr, size, A, B);
    printf("Your generated array:\n");
    printing(arr, size);
    int choice = 0;

    printf("Print 1 if you want to swap the minimum and maximum elements of the array;\n");
    printf("Print 2 if you want to create a new array that contains the unique elements of the original array in the order defined by the original array.\n\n");
    printf("Your choice: ");
    if (scanf("%d", &choice) != 1) {
        printf("You have entered something wrong!\n");
        return -3;
    }

    switch (choice) {
    case 1:
    {
        double* max = max_element(arr, size);
        double* min = min_element(arr, size);
        swap(max, min);

        printf("Your changed array:\n");
        printing(arr, size);

        break;
    }

    case 2:
    {
        double arr_copy[SIZE];
        int i = 0;

        for (i = 0; i < size; i++) {
            arr_copy[i] = arr[i];
        } // создали копию исходного массива

        int new_size = counter_of_unique(arr_copy, size);
        double* new_arr = (double*)malloc(new_size * sizeof(double));

        if (new_arr == NULL) {
            printf("Failed to allocate memory!\n");
            return -4;
        }

        new_arr_of_unique(arr_copy, size, new_arr);

        printing(new_arr, new_size);

        break;
    }

    default:
        printf("You have entered something wrong!\n");
        return -3;
    }

    return 0;
}
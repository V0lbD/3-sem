#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void printing(float arr[], int size)
{
    for (int i = 0; i < size; i++) {
        printf("%.3f ", arr[i]);
    }
    printf("\n");
}

int main(void)
{
    srand(time(NULL));
    int size1 = 0, size2 = 0;

    scanf("%d%d", &size1, &size2);

    float A[size1];
    float B[size2];

    for (int i = 0; i < size1; i++) {
        A[i] = (float)RAND_MAX / 2 - rand() + (float)rand() / RAND_MAX;
    }

    for (int i = 0; i < size2; i++) {
        B[i] = (float)RAND_MAX / 2 - rand() + (float)rand() / RAND_MAX;
    }

    float C[size1];

    for (int i = 0; i < size1; i++) {
        if (i < size2) {
            C[i] = A[i] + B[i];
        }
        else {
            C[i] = A[i] + B[size2 - 1];
        }
    }

    printf("Array 'A': ");
    printing(A, size1);

    printf("Array 'B': ");
    printing(B, size2);

    printf("Array 'C': ");
    printing(C, size1);

    return 0;
}
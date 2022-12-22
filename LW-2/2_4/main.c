#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

typedef enum calc_responses {
    calc_ok,
    calc_even_sqrt_of_negative
} calc_responses;

calc_responses average_geometric(double* str, int n, ...) {
    int i = 0, counter = 0;
    double result = 0, multi = 1;
    va_list factor;
    va_start(factor, n);

    for (i = 0; i < n; i++) {
        multi *= va_arg(factor, double);
        counter++;
    }
    va_end(factor);

    if (counter % 2 == 0 && multi < 0) {
        return calc_even_sqrt_of_negative;
    }
    else {
        result = pow(multi, 1.0 / (double)counter);
        *str = result;
    }

    return calc_ok;
}

double bin_pow(double number, long int degree) { // бинарное возведение в степень https://e-maxx.ru/algo/binary_pow
    if (number == 0 && degree <= 0) {
        return INT_MAX;
    }

    if (number == 1) {
        return 1;
    }

    if (degree == 0) {
        return 1;
    }

    if (degree % 2 == 1 && degree > 0) {
        return bin_pow(number, degree - 1) * number;
    }

    if (degree % 2 == 0 && degree > 0) {
        double tmp = bin_pow(number, degree / 2);
        return tmp * tmp;
    }

    if (degree % 2 == -1 && degree < 0) {
        return bin_pow(number, degree + 1) / number;
    }

    if (degree % 2 == 0 && degree < 0) {
        double tmp = bin_pow(number, degree / 2);
        return tmp * tmp;
    }
}

int main() {
    printf("If you want to calculate the average geometric, press 1;\n");
    double n1 = 3, n2 = 9, n3 = 27;

    printf("If you want to exponentiate recursively, press 2 and enter the number and degree separated by a space.\n\n");
    char choice = getchar();
    double number = 0., result_of_1 = 0., result_of_2 = 0.;
    long int degree = 0;
    calc_responses check_1;

    switch (choice) {
    case '1':
        check_1 = average_geometric(&result_of_1, 3, n1, n2, n3);
        switch (check_1) {
        case calc_even_sqrt_of_negative:
            printf("Negative under root!\n");
            break;
        case calc_ok:
            printf("The average geometric of 3, 9, 27 is: %.3lf\n", result_of_1);
            break;
        }
        break;
    case '2':
        printf("Print number and degree:\n");
        int t = scanf("%lf%ld", &number, &degree); // бороться ли с переполнением при записи?
        if (t != 2) {
            printf("You have entered something wrong!\n");
            return -2;
        }
        result_of_2 = bin_pow(number, degree);

        if (result_of_2 == INT_MAX) { // как иначе вернуть ошибку о делении нуля? (если через calc_responses, то как реализовать рекурсию?)
            printf("You can't divide by zero!");
            return -1;
        }
        else { // как исправлять случай переполнения при подсчёте степени? (f.e. 111 ^ 100))
            printf("\nYour exponent: %.3lf", result_of_2);
        }
        break;
    default:
        printf("You have entered something wrong!\n");
    }

    return 0;
}

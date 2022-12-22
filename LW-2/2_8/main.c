#include <stdio.h>
#include <math.h>

double function(double x)
{
    return (x - 5) * (x - 5) - 5;
}

double dichotomy(double x1, double x2, int acc) // лучше передавать функцию function аргументом, не вызывать в программе (чтобы не зависеть от названия функции)
{
    double point = pow(10, -acc);
    double x = (x1 + x2) / 2;

    while (fabs(function(x1) - function(x2)) > point) {
        if (function(x) * function(x1) < 0) {
            x2 = x;
        }
        else if (function(x) * function(x1) > 0) {
            x1 = x;
        }
        else {
            break;
        }

        x = (x1 + x2) / 2;
    }

    return x;
}

int main()
{
    double x1 = 0, x2 = 0;
    int acc = 0;

    scanf("%lf %lf %d", &x1, &x2, &acc);
    if (function(x1) == 0) {
        printf("The root is %.*lf", acc, x1);
    }
    else if (function(x2) == 0) {
        printf("The root is %.*lf", acc, x2);
    }
    else if (function(x1) * function(x2) > 0) {
        printf("Critical error!");
    }
    else {
        printf("The root is %.*lf", acc, dichotomy(x1, x2, acc));
    }
}
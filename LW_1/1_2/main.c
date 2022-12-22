#include <stdio.h>
#include <math.h>

#define EPS 0.00001

double from_string_to_double(char* str)
{
    int counter = 0;
    int flag_of_negative = 0, flag_of_point = 0;
    int counter_of_digit_after_point = 0;
    char ch = str[counter];

    while (ch != '\0') {
        if (flag_of_point == 1) {
            counter_of_digit_after_point++;
        }
        
        if (ch == '-') {
            flag_of_negative++;
        }
        
        if (ch == '.') { // разделитель для вещественных - точка
            flag_of_point++;
        }

        counter++;
        ch = str[counter];
    }

    double res = 0., degree = 1;
    int i = 0;

    for (i = counter - 1; i >= 0; i--) {
        if (str[i] == '-') {
            res *= -1;
        }
        else if (str[i] != '.') {
            res += degree * ((int)str[i] - 48);
            degree *= 10;
        }
    }

    degree = 1;
    if (flag_of_point != 0) {
        for (i = 0; i < counter_of_digit_after_point; i++) {
            degree *= 10;
        }

        res /= degree;
    }
    
    return res;
}
void roots_of_the_quadratic_equation(double a, double b, double discriminant, double* root_1, double* root_2)
{
    *root_1 = (-b - sqrt(discriminant)) / (2 * a);
    *root_2 = (-b + sqrt(discriminant)) / (2 * a);
}

void main(int argc, char** argv) {

    if (argc < 4) {
        printf("You have entered too few arguments!\n");
        return -1;
    }

    if ((*(argv[1]) == '-' || *(argv[1]) == '/') && *(argv[1] + 2) == '\0') {
        if (*(argv[1] + 1) == 'q') {
            if (argc != 5) {
                printf("You have entered wrong number of arguments!\n");
                return -3;
            }

            double coefficient_a = from_string_to_double(argv[2]);
            double coefficient_b = from_string_to_double(argv[3]);
            double coefficient_c = from_string_to_double(argv[4]);
            double root_1 = 0., root_2 = 0.;

            if (coefficient_a == 0) {
                if (coefficient_b == 0) {
                    if (coefficient_c == 0) {
                        printf("The equation 0 = 0 has infinite number of roots\n");
                    }
                    else {
                        printf("The equation %lf = 0 doesn't have roots\n", coefficient_c);
                    }
                }
                else {
                    root_1 = (-coefficient_c) / coefficient_b;
                    printf("1 root of the equation %lfx + (%lf) = 0 is %lf\n", coefficient_b, coefficient_c, root_1);
                }
            }
            else {
                double discriminant = coefficient_b * coefficient_b - 4 * coefficient_a * coefficient_c;

                if (discriminant < 0) {
                    printf("The quadratic equation %lfx^2 + (%lf)x + (%lf) = 0 doesn't have real roots\n", coefficient_a, coefficient_b, coefficient_c);
                }
                else if (discriminant == 0) {
                    root_1 = (-coefficient_b) / 2*coefficient_a;
                    printf("Only 1 root of the quadratic equation %lfx^2 + (%lf)x + (%lf) = 0 is %lf \n", coefficient_a, coefficient_b, coefficient_c, root_1);
                }
                else {
                    roots_of_the_quadratic_equation(coefficient_a, coefficient_b, discriminant, &root_1, &root_2);
                    printf("2 roots of the quadratic equation %lfx^2 + (%lf)x + (%lf) = 0 is %lf, %lf", coefficient_a, coefficient_b, coefficient_c, root_1, root_2);
                }
            }
        }
        else if (*(argv[1] + 1) == 'm') {
            if (argc != 4) {
                printf("You have entered wrong number of arguments!\n");
                return -3;
            }

            double number_1 = from_string_to_double(argv[2]);
            double number_2 = from_string_to_double(argv[3]);

            if (((double)(int)number_1 != number_1) || ((double)(int)number_2 != number_2)) {
                printf("Your numbers is not integer!\n");
            }
            else {
                int int_number_1 = (int)number_1;
                int int_number_2 = (int)number_2;

                if (int_number_2 == 0) {
                    printf("Second number is zero!\n");
                }
                else {
                    if (int_number_1 % int_number_2 == 0) {
                        printf("The first number is a multiple of the second.\n");
                    }
                    else {
                        printf("The first number is not a multiple of the second.\n");
                    }
                }
            }
        }
        else if (*(argv[1] + 1) == 't') {
            if (argc != 5) {
                printf("You have entered wrong number of arguments!\n");
                return -3;
            }

            double a = from_string_to_double(argv[2]);
            double b = from_string_to_double(argv[3]);
            double c = from_string_to_double(argv[4]);

            double eps = EPS;
            if (a <= eps || b <= eps || c <= eps) {
                printf("A triangle cannot be with a non-positive side!\n");
            }
            else if ((abs(a * a + b * b - c * c) < eps) || (abs(a * a - b * b + c * c) < eps) || (abs(- a * a + b * b + c * c) < eps)) {
                printf("It can be a right triangle!\n");
            }
            else {
                printf("It can't be a right triangle.\n");
            }
        }
        else {
            printf("Your flag is incorrect!\n");
            return -2;
        }
    }
    else {
        printf("Your flag is incorrect!\n");
        return -2;
    }

    return 0;
}
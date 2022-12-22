#include <stdio.h>

unsigned int from_string_to_unsigned_int(char* str)
{
    int counter = 0;
    char ch = str[counter];

    while (ch != '\0') {
        counter++;
        ch = str[counter];
    }

    int degree = 1;
    unsigned int res = 0;
    for (int i = counter - 1; i >= 0; i--) {
        res += degree * ((int)str[i] - 48);
        degree *= 10;
    }

    return res;
}

int is_prime(unsigned int n) 
{
    if (n == 2 || n == 3) {
        return 1;
    }

    if (n <= 1 || n % 2 == 0 || n % 3 == 0) {
        return 0;
    }

    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return 0;
        }
    }

    return 1;
}

void all_degrees(int number, int degree) 
{
    printf("All powers of the number %d from 1 to the %d: ", number, degree);
    unsigned int tmp = number;

    if (number == 1) {
        for (int i = 1; i <= degree; i++) {
            printf("1 ");
        }
    }
    else {
        for (int i = 1; i <= degree; i++) {
            printf("%d ", number);
            number *= tmp;
        }
    }

    printf("\n");
}

unsigned long long factorial(int number) 
{
    unsigned long long result = 1;
    
    for (int i = number; i > 1; i--) {
        result *= i;
    }

    return result;
}

void main(int argc, char** argv) {
    if (argc != 3) {
        printf("Error: found %d arguments. Needs exactly 2", argc - 1);
        return -1;
    }

    // нужно ли проводить валидацию введённого числа?

    unsigned int number = 0;

    if ((*(argv[2]) == '-' || *(argv[2]) == '/') && *(argv[2] + 2) == '\0')  {
        if (*(argv[2] + 1) == 'h') { 
            number = from_string_to_unsigned_int(argv[1]);
            if (number > 100 || number == 0) {
                printf("There are no numbers within 100 that are divisibles of this.\n");
            }
            else {
                printf("Your numbers is: ");
                for (int i = number; i <= 100; i += number) {
                    printf("%d ", i);
                }
            }
        }
        else if (*(argv[2] + 1) == 'p') {
            number = from_string_to_unsigned_int(argv[1]);
            if (is_prime(number)) {
                printf("The number %d is prime.\n", number);
            }
            else {
                printf("The number %d is not prime.\n", number);
            }
        }
        else if (*(argv[2] + 1) == 's') {
            char* tmp = argv[1];
            printf("The digits of your number is ");
            while (*tmp != '\0') {
                printf("%c ", *tmp);
                tmp++;
            }
        }
        else if (*(argv[2] + 1) == 'e') {
            number = from_string_to_unsigned_int(argv[1]);
            if (number > 10) {
                printf("Your number is too big!\n");
            }
            else if (number == 0) {
                printf("Your number is too small!\n");
            }
            else {
                for (int i = 1; i < 10; i++) {
                    all_degrees(i, number);
                }
            }
        }
        else if (*(argv[2] + 1) == 'a') {
            number = from_string_to_unsigned_int(argv[1]);
            printf("Your answer: %d", (number * (number + 1)) / 2);
        }
        else if (*(argv[2] + 1) == 'f') {
            number = from_string_to_unsigned_int(argv[1]);
            printf("The factorial of %d is %lld", number, factorial(number));
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
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef enum scan_responses {
    scan_realloc_error,
    scan_ok,
    scan_incorrect_ptr
} scan_responses;

scan_responses str_scan(char** new_str)
{
    if (*new_str == NULL) return scan_incorrect_ptr;

    char* buf = *new_str, * tmp = NULL, ch = 0;
    int size = 16, actual_size = 0;

    while (!isspace(ch = getchar())) {
        if (actual_size >= size - 1) {
            size *= 2;
            if (!(tmp = (char*)realloc((*new_str), size))) {
                return scan_realloc_error;
            }
            buf = tmp + actual_size;
            (*new_str) = tmp;
        }

        *buf = ch;
        buf++;
        actual_size++;
    }
    (*new_str)[actual_size] = '\0';
    size = actual_size + 1;

    if (!(tmp = (char*)realloc((*new_str), size))) {
        return scan_realloc_error;
    }

    (*new_str) = tmp;

    return scan_ok;
}

void str_reverse(char* str, unsigned long long length)
{
    char tmp;
    int i;
    for (i = 0; i < length / 2; i++) {
        tmp = str[i];
        str[i] = str[length - i - 1];
        str[length - i - 1] = tmp;
    }
}

void str_to_up(char* str, unsigned long long length)
{
    int i = 0;
    for (i = 1; i < length; i += 2) {
        str[i] = toupper(str[i]);
    }
}

void str_special_sort(char* str, unsigned long long length)
{
    char dig[length], let[length], sym[length];
    int i = 0, counter_dig = 0, counter_let = 0, counter_sym = 0;

    for (i = 0; i < length; i++) {
        if (isdigit(str[i])) {
            dig[counter_dig] = str[i];
            counter_dig++;
        }
        else if (isalpha(str[i])) {
            let[counter_let] = str[i];
            counter_let++;
        }
        else {
            sym[counter_sym] = str[i];
            counter_sym++;
        }
    }

    strcpy(str, dig);
    strcpy(str + counter_dig, let);
    strcpy(str + counter_dig + counter_let, sym);
}

void concatenation(char* str1, char* str2)
{
    str1 = strcat(str1, str2);
}

int main()
{
    int size = 16;
    char* str = (char*)malloc(sizeof(char) * size);
    char* flag = (char*)malloc(sizeof(char) * size);
    scan_responses scan_s = str_scan(&str);
    switch (scan_s) {
    case scan_realloc_error:
        free(str);
        return -2;
    case scan_incorrect_ptr:
        return -1;
    default:
        break;
    }

    scan_s = str_scan(&flag);
    switch (scan_s) {
    case scan_realloc_error:
        free(str);
        free(flag);
        return -2;
    case scan_incorrect_ptr:
        return -1;
    default:
        break;
    }

    unsigned long long int length = strlen(str);
    if (!strcmp(flag, "-l")) {
        printf("The length of the string is %llu\n", length);
    }
    else if (!strcmp(flag, "-r")) {
        str_reverse(str, length);
        printf("The reversed string is %s\n", str);
    }
    else if (!strcmp(flag, "-u")) {
        str_to_up(str, length);
        printf("Changed string is %s", str);
    }
    else if (!strcmp(flag, "-n")) {
        str_special_sort(str, length);
        printf("Special sorted string is %s", str);
    }
    else if (!strcmp(flag, "-c")) {
        char* str2 = (char*)malloc(sizeof(char) * size);
        scan_s = str_scan(&str2);
        switch (scan_s) {
        case scan_realloc_error:
            free(str);
            free(flag);
            free(str2);
            return -2;
        case scan_incorrect_ptr:
            return -1;
        default:
            break;
        }

        concatenation(str, str2);
        printf("Concatenation string is %s", str);

        free(str2);
    }
    else {
        printf("GO AWAY!");
    }

    free(str);
    free(flag);
    return 0;
}
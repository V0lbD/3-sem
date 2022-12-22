#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int power_of_10(int degree)
{
    int res = 1;
    while (degree > 0) {
        res *= 10;
        degree--;
    }

    return res;
}

int main(int argc, char** argv) 
{
    int i = 0;
    if (argc > 4) {
        printf("You have entered too many arguments!\n");
        return -1;
    }

    if (argc < 3) {
        printf("You have entered too few arguments!\n");
        return -2;
    }

    if ((*(argv[1]) == '-' || *(argv[1]) == '/') && 
        (*(argv[1] + 2) == '\0') || (*(argv[1] + 1) == 'n') && (*(argv[1] + 3) == '\0')) {
        int flag_of_new_file = 0;
        if (*(argv[1] + 1) == 'n') {
            flag_of_new_file++;
        }

        if (argc == 4 && flag_of_new_file == 0) {
            printf("You have entered name of output file but the wrong flag!\n");
            return -4;
        }

        FILE* fin = NULL;
        FILE* fout = NULL;

        if ((fin = fopen(argv[2], "r")) == NULL) {
            printf("There is no file with that name!\n");
            return -5;
        }

        if (argc == 4 && flag_of_new_file == 1) {
            if ((fout = fopen(argv[3], "w+")) == NULL) {
                printf("There is no access to the file with the specified name!\n");
                fclose(fin);
                return -6;
            }
        }
        
        if (argc == 3 && flag_of_new_file == 1) {
            int counter_of_symbols_in_name_in_file = 0;
            
            i = 0;
            while (*(argv[2] + i) != '\0') {
                counter_of_symbols_in_name_in_file++;
                i++;
            }
            char* name_of_out_file = (char*)malloc(sizeof(char) * (counter_of_symbols_in_name_in_file + 4 + 1));
            if (name_of_out_file == NULL) {
                printf("Memory allocation error\n");
                fclose(fin);
                return -9;
            }

            for (i = 0; i < counter_of_symbols_in_name_in_file - 4; i++) {
                name_of_out_file[i] = *(argv[2] + i);
            }
            name_of_out_file[counter_of_symbols_in_name_in_file - 4] = 'o';
            name_of_out_file[counter_of_symbols_in_name_in_file - 3] = 'u';
            name_of_out_file[counter_of_symbols_in_name_in_file - 2] = 't';
            name_of_out_file[counter_of_symbols_in_name_in_file - 1] = '_';
            name_of_out_file[counter_of_symbols_in_name_in_file] = '.';
            name_of_out_file[counter_of_symbols_in_name_in_file + 1] = 't';
            name_of_out_file[counter_of_symbols_in_name_in_file + 2] = 'x';
            name_of_out_file[counter_of_symbols_in_name_in_file + 3] = 't';
            name_of_out_file[counter_of_symbols_in_name_in_file + 4] = '\0';

            if ((fout = fopen(name_of_out_file, "w+")) == NULL) {
                printf("There is no access to the file with the specified name!\n");
                fclose(fin);
                free(name_of_out_file);
                return -7;
            }
            free(name_of_out_file);
        }

        if (*(argv[1] + 1) == 'd' || *(argv[1] + 2) == 'd') {
            char ch = ' ';
            if (flag_of_new_file == 0) {
                if ((fout = fopen("crazy_out.txt", "w+")) == NULL) {
                    printf("Cannot create a replacement file!\n");
                    fclose(fin);
                    return -8;
                }

                while ((ch = fgetc(fin)) != EOF) {
                    if (!(ch >= '0' && ch <= '9')) {
                        fputc(ch, fout);
                    }
                }

                int counter_of_symbols_in_name_in_file = 0; // создание копии имени входного файла
                i = 0;
                while (*(argv[2] + i) != '\0') {
                    counter_of_symbols_in_name_in_file++;
                    i++;
                }

                char* copy_name_of_in_file = (char*)malloc(sizeof(char) * (counter_of_symbols_in_name_in_file + 1));
                if (copy_name_of_in_file == NULL) {
                    printf("Memory allocation error\n");
                    fclose(fin);
                    fclose(fout);
                    return -9;
                }

                copy_name_of_in_file[counter_of_symbols_in_name_in_file] = '\0';
                for (i = 0; i < counter_of_symbols_in_name_in_file; i++) {
                    copy_name_of_in_file[i] = *(argv[2] + i);
                }
                
                char oldfilename[] = "crazy_out.txt";

                fclose(fin);
                fclose(fout);
                
                if (remove(argv[2])) {
                    printf("Failed to delete file!\n");
                    free(copy_name_of_in_file);
                    return -10;
                }
                
                if (rename(oldfilename, copy_name_of_in_file)) {
                    printf("Failed to rename file!\n");
                    free(copy_name_of_in_file);
                    return -11;
                }

                free(copy_name_of_in_file);
            }
            else if (flag_of_new_file == 1) {
                while ((ch = fgetc(fin)) != EOF) {
                    if ((!(ch >= '0' && ch <= '9')) && (fout != NULL)) {
                        fputc(ch, fout);
                    }
                }

                fclose(fin);
                fclose(fout);
            }
        }
        else if (*(argv[1] + 1) == 'i' || *(argv[1] + 2) == 'i') {
            char ch = ' ';
            if (flag_of_new_file == 0) {
                if ((fout = fopen("crazy_out.txt", "w+")) == NULL) {
                    printf("Cannot create a replacement file!\n");
                    fclose(fin);
                    return -8;
                }

                int counter = 0;
                while (ch != EOF) {
                    ch = getc(fin);
                    while (ch != '\n' && ch != EOF) {
                        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
                            counter++;
                        }
                        ch = getc(fin);
                    }
                    
                    if (counter == 0) {
                        putc('0', fout);
                        putc('\n', fout);
                    }
                    else {
                        int tmp = counter;
                        int length = 0;
                        while (tmp > 0) {
                            length++;
                            tmp /= 10;
                        }

                        int pow_10 = 0;
                        while (counter > 0) {
                            pow_10 = power_of_10(length - 1);
                            fputc((char)(counter / pow_10 + 48), fout);
                            counter = counter - pow_10 * (counter / pow_10);
                            length--;
                        }
                        fputc('\n', fout);
                    }
                }

                int counter_of_symbols_in_name_in_file = 0; // создание копии имени входного файла
                i = 0;
                while (*(argv[2] + i) != '\0') {
                    counter_of_symbols_in_name_in_file++;
                    i++;
                }

                char* copy_name_of_in_file = (char*)malloc(sizeof(char) * (counter_of_symbols_in_name_in_file + 1));
                if (copy_name_of_in_file == NULL) {
                    printf("Memory allocation error\n");
                    fclose(fin);
                    fclose(fout);
                    return -9;
                }

                copy_name_of_in_file[counter_of_symbols_in_name_in_file] = '\0';
                for (i = 0; i < counter_of_symbols_in_name_in_file; i++) {
                    copy_name_of_in_file[i] = *(argv[2] + i);
                }

                char oldfilename[] = "crazy_out.txt";

                fclose(fin);
                fclose(fout);

                if (remove(argv[2])) {
                    printf("Failed to delete file!\n");
                    free(copy_name_of_in_file);
                    return -10;
                }

                if (rename(oldfilename, copy_name_of_in_file)) {
                    printf("Failed to rename file!\n");
                    free(copy_name_of_in_file);
                    return -11;
                }

                free(copy_name_of_in_file);
            }
            else if (flag_of_new_file == 1) {
                int counter = 0;
                while (ch != EOF) {
                    ch = getc(fin);
                    while (ch != '\n' && ch != EOF) {
                        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
                            counter++;
                        }
                        ch = getc(fin);
                    }

                    if (counter == 0) {
                        putc('0', fout);
                        putc('\n', fout);
                    }
                    else {
                        int tmp = counter;
                        int length = 0;
                        while (tmp > 0) {
                            length++;
                            tmp /= 10;
                        }

                        int pow_10 = 0;
                        while (counter > 0) {
                            pow_10 = power_of_10(length - 1);
                            fputc((char)(counter / pow_10 + 48), fout);
                            counter = counter - pow_10 * (counter / pow_10);
                            length--;
                        }
                        fputc('\n', fout);
                    }
                }

                fclose(fin);
                fclose(fout);
            }
        }
        else if (*(argv[1] + 1) == 's' || *(argv[1] + 2) == 's') {
            char ch = ' ';
            if (flag_of_new_file == 0) {
                if ((fout = fopen("crazy_out.txt", "w+")) == NULL) {
                    printf("Cannot create a replacement file!\n");
                    fclose(fin);
                    return -8;
                }

                int counter = 0;
                while (ch != EOF) {
                    ch = getc(fin);
                    while (ch != '\n' && ch != EOF) {
                        if (!(ch >= 'a' && ch <= 'z') && !(ch >= 'A' && ch <= 'Z') && !(ch >= '0' && ch <= '9') && ch != ' ') {
                            counter++;
                        }
                        ch = getc(fin);
                    }

                    if (counter == 0) {
                        putc('0', fout);
                        putc('\n', fout);
                    }
                    else {
                        int tmp = counter;
                        int length = 0;
                        while (tmp > 0) {
                            length++;
                            tmp /= 10;
                        }

                        int pow_10 = 0;
                        while (counter > 0) {
                            pow_10 = power_of_10(length - 1);
                            fputc((char)(counter / pow_10 + 48), fout);
                            counter = counter - pow_10 * (counter / pow_10);
                            length--;
                        }
                        fputc('\n', fout);
                    }
                }

                int counter_of_symbols_in_name_in_file = 0; // создание копии имени входного файла
                i = 0;
                while (*(argv[2] + i) != '\0') {
                    counter_of_symbols_in_name_in_file++;
                    i++;
                }

                char* copy_name_of_in_file = (char*)malloc(sizeof(char) * (counter_of_symbols_in_name_in_file + 1));
                if (copy_name_of_in_file == NULL) {
                    printf("Memory allocation error\n");
                    fclose(fin);
                    fclose(fout);
                    return -9;
                }

                copy_name_of_in_file[counter_of_symbols_in_name_in_file] = '\0';
                for (i = 0; i < counter_of_symbols_in_name_in_file; i++) {
                    copy_name_of_in_file[i] = *(argv[2] + i);
                }

                char oldfilename[] = "crazy_out.txt";

                fclose(fin);
                fclose(fout);

                if (remove(argv[2])) {
                    printf("Failed to delete file!\n");
                    free(copy_name_of_in_file);
                    return -10;
                }

                if (rename(oldfilename, copy_name_of_in_file)) {
                    printf("Failed to rename file!\n");
                    free(copy_name_of_in_file);
                    return -11;
                }

                free(copy_name_of_in_file);
            }
            else if (flag_of_new_file == 1) {
                int counter = 0;
                while (ch != EOF) {
                    ch = getc(fin);
                    while (ch != '\n' && ch != EOF) {
                        if (!(ch >= 'a' && ch <= 'z') && !(ch >= 'A' && ch <= 'Z') && !(ch >= '0' && ch <= '9') && ch != ' ') {
                            counter++;
                        }
                        ch = getc(fin);
                    }

                    if (counter == 0) {
                        putc('0', fout);
                        putc('\n', fout);
                    }
                    else {
                        int tmp = counter;
                        int length = 0;
                        while (tmp > 0) {
                            length++;
                            tmp /= 10;
                        }

                        int pow_10 = 0;
                        while (counter > 0) {
                            pow_10 = power_of_10(length - 1);
                            fputc((char)(counter / pow_10 + 48), fout);
                            counter = counter - pow_10 * (counter / pow_10);
                            length--;
                        }
                        fputc('\n', fout);
                    }
                }

                fclose(fin);
                fclose(fout);
            }
        }
        else if (*(argv[1] + 1) == 'a' || *(argv[1] + 2) == 'a') {
            char ch = ' ';
            if (flag_of_new_file == 0) {
                if ((fout = fopen("crazy_out.txt", "w+")) == NULL) {
                    printf("Cannot create a replacement file!\n");
                    fclose(fin);
                    return -8;
                }

                int ascii_code_of_letter = 0;
                while (ch != EOF) {
                    ch = getc(fin);
                    while (ch != '\n' && ch != EOF) {
                        if (!(ch >= '0' && ch <= '9')) {
                            ascii_code_of_letter = (int)ch;
                            int tmp = ascii_code_of_letter;
                            int length = 0;
                            while (tmp > 0) {
                                length++;
                                tmp /= 10;
                            }

                            int pow_10 = 0;
                            while (ascii_code_of_letter > 0) {
                                pow_10 = power_of_10(length - 1);
                                fputc((char)(ascii_code_of_letter / pow_10 + 48), fout);
                                ascii_code_of_letter = ascii_code_of_letter - pow_10 * (ascii_code_of_letter / pow_10);
                                length--;
                            }
                        }
                        else {
                            fputc(ch, fout);
                        }

                        ch = getc(fin);
                    }

                    fputc('\n', fout);
                }

                int counter_of_symbols_in_name_in_file = 0; // создание копии имени входного файла
                i = 0;
                while (*(argv[2] + i) != '\0') {
                    counter_of_symbols_in_name_in_file++;
                    i++;
                }

                char* copy_name_of_in_file = (char*)malloc(sizeof(char) * (counter_of_symbols_in_name_in_file + 1));
                if (copy_name_of_in_file == NULL) {
                    printf("Memory allocation error\n");
                    fclose(fin);
                    fclose(fout);
                    return -9;
                }

                copy_name_of_in_file[counter_of_symbols_in_name_in_file] = '\0';
                for (i = 0; i < counter_of_symbols_in_name_in_file; i++) {
                    copy_name_of_in_file[i] = *(argv[2] + i);
                }

                char oldfilename[] = "crazy_out.txt";

                fclose(fin);
                fclose(fout);

                if (remove(argv[2])) {
                    printf("Failed to delete file!\n");
                    free(copy_name_of_in_file);
                    return -10;
                }

                if (rename(oldfilename, copy_name_of_in_file)) {
                    printf("Failed to rename file!\n");
                    free(copy_name_of_in_file);
                    return -11;
                }

                free(copy_name_of_in_file);
            }
            else if (flag_of_new_file == 1) {
                int counter = 0;
                int ascii_code_of_letter = 0;
                while (ch != EOF) {
                    ch = getc(fin);
                    while (ch != '\n' && ch != EOF) {
                        if (!(ch >= '0' && ch <= '9')) {
                            ascii_code_of_letter = (int)ch;
                            int tmp = ascii_code_of_letter;
                            int length = 0;
                            while (tmp > 0) {
                                length++;
                                tmp /= 10;
                            }

                            int pow_10 = 0;
                            while (ascii_code_of_letter > 0) {
                                pow_10 = power_of_10(length - 1);
                                fputc((char)(ascii_code_of_letter / pow_10 + 48), fout);
                                ascii_code_of_letter = ascii_code_of_letter - pow_10 * (ascii_code_of_letter / pow_10);
                                length--;
                            }
                        }
                        else {
                            fputc(ch, fout);
                        }

                        ch = getc(fin);
                    }

                    fputc('\n', fout);
                }

                fclose(fin);
                fclose(fout);
            }
        }
        else if (*(argv[1] + 1) == 'f' || *(argv[1] + 2) == 'f') {
            char ch = ' ';
            if (flag_of_new_file == 0) {
                if ((fout = fopen("crazy_out.txt", "w+")) == NULL) {
                    printf("Cannot create a replacement file!\n");
                    fclose(fin);
                    return -8;
                }

                int counter_of_lexemes = 1;
                int ascii_code_of_letter = 0;
                while (ch != EOF) {
                    ch = getc(fin);
                    while (ch != '\n' && ch != EOF) {
                        if (ch >= 'A' && ch <= 'Z' && (counter_of_lexemes % 2 == 0) && (counter_of_lexemes % 5 != 0)) {
                            fputc(ch - ('a' - 'A'), fout);
                        }
                        else if (counter_of_lexemes % 5 == 0 && ch != ' ') {
                            ascii_code_of_letter = (int)ch;
                            int tmp = ascii_code_of_letter;
                            int length = 0;
                            while (tmp > 0) {
                                length++;
                                tmp /= 10;
                            }

                            int pow_10 = 0;
                            while (ascii_code_of_letter > 0) {
                                pow_10 = power_of_10(length - 1);
                                fputc((char)(ascii_code_of_letter / pow_10 + 48), fout);
                                ascii_code_of_letter = ascii_code_of_letter - pow_10 * (ascii_code_of_letter / pow_10);
                                length--;
                            }
                        }
                        else {
                            putc(ch, fout);
                        }

                        ch = getc(fin);
                        if (ch == ' ' || ch == '\n') {
                            counter_of_lexemes++;
                        }
                    }

                    fputc('\n', fout);
                }

                int counter_of_symbols_in_name_in_file = 0; // создание копии имени входного файла
                i = 0;
                while (*(argv[2] + i) != '\0') {
                    counter_of_symbols_in_name_in_file++;
                    i++;
                }

                char* copy_name_of_in_file = (char*)malloc(sizeof(char) * (counter_of_symbols_in_name_in_file + 1));
                if (copy_name_of_in_file == NULL) {
                    printf("Memory allocation error\n");
                    fclose(fin);
                    fclose(fout);
                    return -9;
                }

                copy_name_of_in_file[counter_of_symbols_in_name_in_file] = '\0';
                for (i = 0; i < counter_of_symbols_in_name_in_file; i++) {
                    copy_name_of_in_file[i] = *(argv[2] + i);
                }

                char oldfilename[] = "crazy_out.txt";

                fclose(fin);
                fclose(fout);

                if (remove(argv[2])) {
                    printf("Failed to delete file!\n");
                    free(copy_name_of_in_file);
                    return -10;
                }

                if (rename(oldfilename, copy_name_of_in_file)) {
                    printf("Failed to rename file!\n");
                    free(copy_name_of_in_file);
                    return -11;
                }

                free(copy_name_of_in_file);
            }
            else if (flag_of_new_file == 1) {
                int counter = 0;
                int ascii_code_of_letter = 0;
                int counter_of_lexemes = 1;
                while (ch != EOF) {
                    ch = getc(fin);
                    while (ch != '\n' && ch != EOF) {
                        if (ch >= 'A' && ch <= 'Z' && (counter_of_lexemes % 2 == 0) && (counter_of_lexemes % 5 != 0)) {
                            fputc(ch + ('a' - 'A'), fout);
                        }
                        else if (counter_of_lexemes % 5 == 0 && ch != ' ') {
                            ascii_code_of_letter = (int)ch;
                            int tmp = ascii_code_of_letter;
                            int length = 0;
                            while (tmp > 0) {
                                length++;
                                tmp /= 10;
                            }

                            int pow_10 = 0;
                            while (ascii_code_of_letter > 0) {
                                pow_10 = power_of_10(length - 1);
                                fputc((char)(ascii_code_of_letter / pow_10 + 48), fout);
                                ascii_code_of_letter = ascii_code_of_letter - pow_10 * (ascii_code_of_letter / pow_10);
                                length--;
                            }
                        }
                        else {
                            putc(ch, fout);
                        }

                        ch = getc(fin);
                        if (ch == ' ' || ch == '\n') {
                            counter_of_lexemes++;
                            counter_of_lexemes = counter_of_lexemes % 15;
                        }
                    }

                    fputc('\n', fout);
                }

                fclose(fin);
                fclose(fout);
            }
        }
        else {
            printf("Your flag is incorrect!\n");
            fclose(fin);
            fclose(fout);
            return -3;
        }
    }
    else {
        printf("Your flag is incorrect!\n");
        return -3;
    }

    return 0;
}
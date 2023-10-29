#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

// Функция для подсчета длины строки
int count_length(char* str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

// Функция для переворачивания строки
char* reverse_string(char* str) {
    int length = count_length(str);
    char* reversed = (char*)malloc((length + 1) * sizeof(char));
    if (reversed == NULL){
        printf("Memory does not allocate for function reverse_string.\n");
        return 0;
    }
    for (int i = 0; i < length; i++) {
        reversed[i] = str[length - i - 1];
    }
    reversed[length] = '\0';
    return reversed;
}

// Функция для преобразования нечетных символов в верхний регистр
char* uppercase_odd_chars(char* str) {
    int length = count_length(str);
    char* uppercase = (char*)malloc((length + 1) * sizeof(char));
    if (uppercase == NULL){
        printf("Memory does not allocate for function uppercase_odd_chars.\n");
        return 0;
    }
    for (int i = 0; i < length; i++) {
        if (i % 2 == 0) {
            uppercase[i] = str[i];
        } else {
            uppercase[i] = str[i] >= 'a' && str[i] <= 'z' ? str[i] - 32 : str[i];
        }
    }
    uppercase[length] = '\0';
    return uppercase;
}

    int str_len(char const *str) {
        int i = 0, res = 0;
        char c = str[0];
        while (c != '\0') {
            res++;
            c = str[i];
            i++;
        }
        return res;
    }

// Функция для получения новой строки с символами в определенном порядке
char* rearrange_chars(char *str){
    int length = str_len(str);
    char* new_str = (char*) calloc(length + 1, sizeof(char));
    if (new_str == NULL){
        printf("Memory does not allocate for function rearrange_chars\n");
        return 0;
    }
    int n = 0;
    for (int i = 0; i < length; ++i) {
        if(isdigit(str[i])){
            new_str[n] = str[i];
            n++;
        }
    }
    for (int i = 0; i < length; ++i) {
        if(isalpha(str[i])){
            new_str[n] = str[i];
            n++;
        }
    }
    for (int i = 0; i < length; ++i) {
        if(!isdigit(str[i]) && !isalpha(str[i])){
            new_str[n] = str[i];
            n++;
        }
    }
    new_str[n] = '\0';
    return new_str;
}


// Функция для конкатенации строк в псевдослучайном порядке
char* concatenate_strings(int argc, char* argv[], unsigned int seed) {
    srand(seed);
    int total_length = 0;
    for (int i = 2; i < argc; i++) {
        total_length += count_length(argv[i]);
    }
    char* concatenated = (char*)malloc((total_length + 1) * sizeof(char));
    if (concatenated == NULL){
        printf("Memory does not allocate for function concatenate_strings(concatenated).\n");
        return 0;
    }
    int index = 0;
    int* indices = (int*)malloc((argc - 2) * sizeof(int));
    if (concatenated == NULL){
        printf("Memory does not allocate for function concatenate_strings(indices).\n");
        return 0;
    }
    for (int i = 0; i < argc - 2; i++) {
        indices[i] = i;
    }
    for (int i = argc - 2; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }
    for (int i = 0; i < argc - 2; i++) {
        int length = count_length(argv[indices[i] + 2]);
        for (int j = 0; j < length; j++) {
            concatenated[index++] = argv[indices[i] + 2][j];
        }
    }
    concatenated[total_length] = '\0';
    free(indices);
    return concatenated;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: ./lab11 <-flag> string <strings for flag '-c'>\n");
        return 1;
    }

    char flag = argv[1][1];
    char* str = argv[2];

    switch (flag) {
        case 'l':
            printf("Length of the string: %d\n", count_length(str));
            break;
        case 'r':
            printf("Reversed string: %s\n", reverse_string(str));
            break;
        case 'u':
            printf("Uppercase odd characters: %s\n", uppercase_odd_chars(str));
            break;
        case 'n':
            printf("Rearranged characters: %s\n", rearrange_chars(str));
            break;
        case 'c':
            if (argc < 4) {
                printf("Not enough additional arguments for -c flag\n");
                return 1;
            }
            unsigned int seed = (unsigned int)time(NULL);
            printf("Concatenated strings: %s\n", concatenate_strings(argc, argv, seed));
            break;
        default:
            printf("Invalid flag\n");
            return 1;
    }

    return 0;
}

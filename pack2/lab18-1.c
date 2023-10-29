#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int range_checker(char* str, int radix){
    int flag = 0;
    if (str[0] == '-'){
        flag = 1;
    }
    if (radix <= 10){
        for (int i = 0; i < strlen(str) - flag; ++i) {
            if (str[i + flag] - '0' >= radix){
                return 0;
            }
        }
    }
    else{
        for (int i = 0; i < strlen(str) - flag; ++i){
            if (!isdigit(str[i + flag]) && (str[i + flag] - 'A' >= radix - 10)){
                return 0;
            }
        }
    }
    return 1;
}

char letter(long long int number, int radix){
    if (number % radix >= 10){
        return (char)('A' + (int)(number % radix - 10));
    }
    return (char)('0' + (int)(number % radix));
}

int str_max(char* str1, char* str2){
    return (int) strlen(strlen(str1) > strlen(str2) ? str1 : str2);
}

char* add_zeros(char* str, int n){
    int length = (int)strlen(str) + n;
    char* res = (char*) calloc(length, sizeof(char));
    if (res == NULL){
        printf("Memory does not allocate for function add_zero\n");
        return NULL;
    }
    for (int i = 0; i < length; ++i) {
        if (i < n){
            res[i] = '0';
        }
        else{
            res[i] = str[i - n];
        }
    }
    return res;
}

char* delete_leading_zeros(char *number){
    int length = (int)strlen(number);
    int index = 0;
    for (int i = 0; i < length; ++i) {
        if (number[i] != '0'){
            index = i;
            break;
        }
    }
    int new_length = length - index;
    char* res = calloc(new_length + 1, sizeof(char));
    if (res == NULL){
        printf("Memory does not allocate for function delete_leading_zeros\n");
        return NULL;
    }
    strncpy(res, number + index, new_length);
    res[new_length] = '\0';
    return res;
}

int number_get_int(char c){
    c = (char)toupper(c);
    if (c >= 'A' && c <= 'Z'){
        return c - 'A' + 10;
    }
    return c - '0';
}

char* str_sum(char* prev_res, char* str, int radix){
    int length = str_max(prev_res, str) + 1;
    prev_res = add_zeros(prev_res, length - (int)strlen(prev_res));
    if (prev_res == NULL){
        return NULL;
    }
    str = add_zeros(str, length - (int)strlen(str));
    if (str == NULL){
        free(prev_res);
        return NULL;
    }
    char* res = (char*)calloc(length + 1, sizeof(char));
    if (res == NULL){
        free(str);
        free(prev_res);
        printf("Memory does not allocate for function str_sum\n");
        return NULL;
    }
    int next = 0;
    for (int i = length - 1; i >= 0 ; --i) {
        int n1 = number_get_int(prev_res[i]);
        int n2 = number_get_int(str[i]);
        res[i] = letter((n1 + n2 + next) % radix, radix);
        next = (n1 + n2 + next) / radix;
    }
    free(prev_res);
    free(str);
    res[length] = '\0';
    res = delete_leading_zeros(res);
    return res;
}

int final_sum(char* res, int n, int coef, ...){
    if (n < 2 || n > 36){
        printf("Radix must be in range [2, 36]\n");
        exit(0);
    }
    va_list str;
    va_start(str, coef);
    if (coef == 0) {
        printf("No numbers provided.\n");
        exit(0);
    }
    for (int i = 0; i < coef; ++i) {
        char* temp = va_arg(str, char*);
        if (range_checker(temp, n) == 0){
            printf("Number is greater than radix\n");
            exit(0);
        }
        char* temp_res = str_sum(res, temp, n);
        if (temp_res == NULL){
            printf("Memory does not allocate for function action\n");
            return 0;
        }
        strcpy(res, temp_res);
        free(temp_res);
    }
    return 1;
}

int main(){
    char res[BUFSIZ] = "0";
    final_sum(res, 36, 4, "0A1", "002F", "0023U", "00AKHXV");
    printf("Sum: %s\n", res);
    return 0;
}

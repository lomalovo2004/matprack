//worked
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

int findmax_absolute(long long* numbers, int count) {
    long long max = llabs(numbers[0]);
    for (int i = 1; i < count; i++) {
        if (llabs(numbers[i]) > max) {
            max = llabs(numbers[i]);
        }
    }
    return max;
}

void conver_to_radix(long long number, int radix, char* result) {
    int index = 0;
    if (number < 0) {
        result[index++] = '-';
        number = -number;
    }

    while (number > 0) {
        int remainder = number % radix;
        if (remainder < 10) {
            result[index] = remainder + '0';
        } else {
            result[index] = remainder - 10 + 'A';
        }
        number /= radix;
        index++;
    }
    result[index] = '\0';
    int length = strlen(result);
    for (int i = 0; i < length / 2; i++) {
        char temp = result[i];
        result[i] = result[length - i - 1];
        result[length - i - 1] = temp;
    }
}


void remove_leading_zeros(char* str) {

    int len = strlen(str);
    if (len <= 1) {
        return;
    }
    int i = 0;
    while (str[i] == '0') {
        i++;
    }
    if (i > 0) {
        int j = 0;
        while (i < len) {
            str[j++] = str[i++];
        }
        str[j] = '\0';
    }
}


int main() {
    int radix;
    printf("Enter the radix in range [2; 36]: ");
    scanf("%d", &radix);

    if (radix < 2 || radix > 36) {
        printf("The radix must be in range [2; 36]\n");
        return 1;
    }

    long long* numbers = NULL;
    int count = 0;

    char** number_strings = NULL;

    printf("Enter numbers in the radix number system %d (enter \"Stop\" to finish program): \n", radix);
    char input[100];
    int numbers_entered = 0;
    while (1) {
        scanf("%s", input);
        if (strcmp(input, "Stop") == 0) {
            if (numbers_entered == 0) {
                printf("Numbers were not entered\n");
                return 0;
            }
            break;
        }

        int valid = 1;

        for (int i = 0; i < strlen(input); i++) {
            if (input[i] >= '0' && input[i] <= '9') {
                if (input[i] - '0' >= radix) {
                    valid = 0;
                    break;
                }
            } else if (input[i] >= 'A' && input[i] <= 'Z') {
                if (input[i] - 'A' + 10 >= radix) {
                    valid = 0;
                    break;
                }
            } else if (input[i] == '-' && i == 0) {
                continue;
            } else {
                valid = 0;
                break;
            }
        }
        if (!valid) {
            printf("Error: number is greater than radix\n");
            continue;
        }

        long long number = strtoll(input, NULL, radix);
        numbers = (long long*)realloc(numbers, (count + 1) * sizeof(long long));
        if (numbers == NULL){
            printf("Memmory does not allocated\n");
            return 1;
        }
        numbers[count] = number;
        number_strings = (char**)realloc(number_strings, (count + 1) * sizeof(char*));
        number_strings[count] = (char*)malloc(100 * sizeof(char));
        if (number_strings == NULL){
            printf("Memmory does not allocated\n");
            return 1;
        }
        strcpy(number_strings[count], input);
        count++;
        numbers_entered = 1;
    }

    long long max_absolute = findmax_absolute(numbers, count);

    int max_index = 0;
    for (int i = 1; i < count; i++) {
        if (llabs(numbers[i]) == max_absolute) {
            max_index = i;
            break;
        }
    }

    char* max_radix = (char*)malloc(100 * sizeof(char));
    
    if (max_radix == NULL){
        printf("Memmory does not allocated\n");
        return 1;
    }
    
    conver_to_radix(numbers[max_index], radix, max_radix);
    printf("The original number, which is the maximum modulo: %s\n", number_strings[max_index]);



    printf("Maximum modulo number: %lld\n", max_absolute);
    char result[BUFSIZ];


    if (number_strings[max_index][0] == '0'){
        printf("String representation in radix number system 9: 0\n");
        printf("String representation in radix number system 18: 0\n");
        printf("String representation in radix number system 27: 0\n");
        printf("String representation in radix number system 36: 0\n");
    }

    else if (number_strings[max_index][0] == '-' && number_strings[max_index][1] == '0'){
        printf("String representation in radix number system 9: 0\n");
        printf("String representation in radix number system 18: 0\n");
        printf("String representation in radix number system 27: 0\n");
        printf("String representation in radix number system 36: 0\n");
    }

    else if (number_strings[max_index][0] == '-'){
        conver_to_radix(max_absolute, 9, result);
        remove_leading_zeros(result);
        printf("String representation in radix number system 9: -%s\n", result);
        conver_to_radix(max_absolute, 18, result);
        remove_leading_zeros(result);
        printf("String representation in radix number system 18: -%s\n", result);
        conver_to_radix(max_absolute, 27, result);
        remove_leading_zeros(result);
        printf("String representation in radix number system 27: -%s\n", result);
        conver_to_radix(max_absolute, 36, result);
        remove_leading_zeros(result);
        printf("String representation in radix number system 36: -%s\n", result);
    }

    else if (number_strings[max_index][0] != '-'){
        conver_to_radix(max_absolute, 9, result);
        remove_leading_zeros(result);
        printf("String representation in radix number system 9: %s\n", result);
        conver_to_radix(max_absolute, 18, result);
        remove_leading_zeros(result);
        printf("String representation in radix number system 18: %s\n", result);
        conver_to_radix(max_absolute, 27, result);
        remove_leading_zeros(result);
        printf("String representation in radix number system 27: %s\n", result);
        conver_to_radix(max_absolute, 36, result);
        remove_leading_zeros(result);
        printf("String representation in radix number system 36: %s\n", result);
    }

    free(numbers);
    for (int i = 0; i < count; i++) {
        free(number_strings[i]);
    }
    free(number_strings);

    free(max_radix);

    return 0;
}
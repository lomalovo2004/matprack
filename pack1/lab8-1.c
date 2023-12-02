#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: lab8-1 input_file output_file\n");
        return 1;
    }
    
    FILE* input_file = fopen(argv[1], "r");
    FILE* output_file = fopen(argv[2], "w");
    
    if (input_file == NULL || output_file == NULL) {
        printf("Error opening files\n");
        fclose(input_file);
        fclose(output_file);
        return 1;
    }
    
    char *number;
    number = malloc(sizeof(char));
    if (number == NULL){
        printf("Memmory does not allocate\n");
        fclose(input_file);
        fclose(output_file);
        return 1;
    }
    
    while (fscanf(input_file, "%s", number) != EOF) {
        int min_radix = 2;
        int len = strlen(number);
        int error = 0;
        
        
        for (int i = 0; i < len; i++) {
            if (isdigit(number[i])) {
                int digit = number[i] - '0';
                if (digit >= min_radix) {
                    min_radix = digit + 1;
                }
            } else if (isalpha(number[i])) {
                int digit = toupper(number[i]) - 'A' + 10;
                if (digit >= min_radix) {
                    min_radix = digit + 1;
                }
            }
        }

        long decimal_number = strtol(number, NULL, min_radix);

        int count = 0;
        while(number[count + 1]) count++;
        
        while (*number == '0' && count != 0){
            count = count - 1;
            ++number;
        }
        char *number1, temp;
        temp = strlen(number);
        number1 = malloc(temp + 1);
        if (number1 == NULL){
            printf("Memmory does not allocated\n");
            fclose(input_file);
            fclose(output_file);
            return 1;
        }
        strcpy(number1, number);


        if (decimal_number == 0 && strcmp(number, "0") != 0) {
            error = 1;
        }


        if (error == 1) {
            fprintf(output_file, "%s Error: radix of this number is not in range [2; 36]\n", number1);
        }
        else{
            fprintf(output_file, "%s %d %ld\n", number1, min_radix, decimal_number);
        }
    }
    
    fclose(input_file);
    fclose(output_file);
    printf("Program completed successfully\n");
    return 0;
}

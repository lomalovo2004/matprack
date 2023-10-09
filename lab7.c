#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void writeToFile(char* filename, char* file1, char* file2, char* file3) {
    FILE* output = fopen(filename, "w");
    if (output == NULL) {
        printf("Error opening output file\n");
        return;
    }

    FILE* input1 = fopen(file1, "r");
    FILE* input2 = fopen(file2, "r");
    FILE* input3 = fopen(file3, "r");
    if (input1 == NULL || input2 == NULL || input3 == NULL) {
        printf("Error opening input files\\n");
        fclose(output);
        return;
    }

    char lexeme[100];
    int count1 = 0, count2 = 0, count3 = 0;
    int position = 1;

    while (1) {
        if (position % 2 == 1) {
            if (fscanf(input2, "%s", lexeme) != EOF) {
                fprintf(output, "%s ", lexeme);
                count2++;
            } else {
                break;
            }
        } else {
            if (fscanf(input3, "%s", lexeme) != EOF) {
                fprintf(output, "%s ", lexeme);
                count3++;
            } else {
                break;
            }
        }

        position++;
    }

    rewind(input1);
    while (fscanf(input1, "%s", lexeme) != EOF) {
        fprintf(output, "%s ", lexeme);
        count1++;
    }

    fclose(input1);
    fclose(input2);
    fclose(output);
}

void transformFile(char* filename, char* input) {
    FILE* output = fopen(filename, "w");
    if (output == NULL) {
        printf("Error opening output file\n");
        return;
    }

    FILE* input_file = fopen(input, "r");
    if (input_file == NULL) {
        printf("Error opening input files\n");
        fclose(output);
        return;
    }

    char lexeme[100];
    int count = 0;

    while (fscanf(input_file, "%s", lexeme) != EOF) {
        if (count % 10 == 9) {
            for (int i = 0; i < strlen(lexeme); i++) {
                if (isalpha(lexeme[i])) {
                    lexeme[i] = tolower(lexeme[i]);
                    lexeme[i] = '0' + (tolower(lexeme[i]) - 'a');
                }
            }
        } else if (count % 2 == 1) {
            for (int i = 0; i < strlen(lexeme); i++) {
                if (isalpha(lexeme[i])) {
                    lexeme[i] = tolower(lexeme[i]);
                }
            }
        } else if (count % 5 == 4) {
            int num = atoi(lexeme);
            sprintf(lexeme, "%o", num);
        }

        fprintf(output, "%s ", lexeme);
        count++;
    }

    fclose(input_file);
    fclose(output);
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        printf("Need more arguments\n");
        return 1;
    }

    char* flag = argv[1];
    char* filename = argv[2];

    if (strcmp(flag, "-r") == 0) {
        if (argc != 5) {
            printf("Invalid quantity arguments for flag -r\n");
            return 1;
        }

        char* file1 = argv[2];
        char* file2 = argv[3];
        char* file3 = argv[4];
        writeToFile(filename, file1, file2, file3);
    } 
    else if (strcmp(flag, "-a") == 0) {
        if (argc != 4) {
            printf("Invalid quantity arguments for flag -a\n");
            return 1;
        }

        char* input = argv[3];
        transformFile(filename, input);
    } 
    else {
        printf("Invalid flag\n");
        return 1;
    }

    printf("Program completed successfully\n");
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void delete_digits(FILE *input, FILE *output) {
    int c;
    while ((c = fgetc(input)) != EOF) {
        if (!isdigit(c)) {
            fputc(c, output);
        }
    }
}

void count_letters(FILE *input, FILE *output) {
    char line[1000];
    while (fgets(line, sizeof(line), input)) {
        int count = 0;
        for (int i = 0; line[i] != '\0'; i++) {
            if (isalpha(line[i])) {
                count++;
            }
        }
        fprintf(output, "Number of letters: %d\n", count);
        fputs(line, output);
    }
}

void count_non_letters(FILE *input, FILE *output) {
    char line[1000];
    while (fgets(line, sizeof(line), input)) {
        int count = 0;
        for (int i = 0; line[i] != '\0'; i++) {
            if (!isalpha(line[i]) && !isdigit(line[i]) && !isspace(line[i])) {
                count++;
            }
        }
        fprintf(output, "Number of non-letters: %d\n", count);
        fputs(line, output);
    }
}

void replace_non_digits(FILE *input, FILE *output) {
    char line[1000];
    while (fgets(line, sizeof(line), input)) {
        for (int i = 0; line[i] != '\0'; i++) {
            if (!isdigit(line[i])) {
                fprintf(output, "%02X", line[i]);
            } else {
                fputc(line[i], output);
            }
        }
        fputs("\n", output);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <flag> <input_file> [output_file]\n", argv[0]);
        return 1;
    }

    char *flag = argv[1];
    char *input_file = argv[2];
    char *output_file;

    if (argc > 3) {
        output_file = argv[3];
    } else {
        output_file = malloc(strlen(input_file) + 5);
        strcpy(output_file, "out_");
        strcat(output_file, input_file);
    }

    FILE *input = fopen(input_file, "r");
    FILE *output = fopen(output_file, "w");

    if (input == NULL || output == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    if (strcmp(flag, "-d") == 0) {
        delete_digits(input, output);
    } else if (strcmp(flag, "-i") == 0) {
        count_letters(input, output);
    } else if (strcmp(flag, "-s") == 0) {
        count_non_letters(input, output);
    } else if (strcmp(flag, "-a") == 0) {
        replace_non_digits(input, output);
    } else {
        printf("Invalid flag.\n");
        return 1;
    }

    fclose(input);
    fclose(output);

    return 0;
}

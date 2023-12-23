#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int convertToBase4(int decimal) {
    int base4 = 0, i = 1;

    while (decimal != 0) {
        base4 += (decimal % 4) * i;
        decimal /= 4;
        i *= 10;
    }

    return base4;
}


void writeToFileR(char* outputFilePath, char* file1Path, char* file2Path) {
    FILE* outputFile = fopen(outputFilePath, "w");
    FILE* file1 = fopen(file1Path, "r");
    FILE* file2 = fopen(file2Path, "r");

    if (file1 == NULL){
        printf("Error opening fiel1\n");
        return;
    }
    if (file2 == NULL){
        printf("Error opening fiel2\n");
        return;
    }
    if (outputFile == NULL){
        printf("Error opening output file\n");
        return;
    }
    

    char word1[BUFSIZ];
    char word2[BUFSIZ];
    while (fscanf(file1, "%s", word1) == 1 && fscanf(file2, "%s", word2) == 1) {
        fprintf(outputFile, "%s %s ", word1, word2);
    }

    while (fscanf(file1, "%s", word1) == 1) {
        fprintf(outputFile, "%s ", word1);
    }

    while (fscanf(file2, "%s", word2) == 1) {
        fprintf(outputFile, "%s ", word2);
    }

    fclose(outputFile);
    fclose(file1);
    fclose(file2);
}


void writeToFileA(char* outputFilePath, char* inputFilePath) {
    FILE* outputFile = fopen(outputFilePath, "w");
    FILE* inputFile = fopen(inputFilePath, "r");
    char word[BUFSIZ];
    int count = 0;

    while (fscanf(inputFile, "%s", word) == 1) {
        count++;
        if (count % 10 == 0) {
            for (int i = 0; word[i] != '\0'; i++) {
                if (isalpha(word[i])) {
                    word[i] = tolower(word[i]);
                    int ascii =  word[i];
                    int base4 = convertToBase4(ascii);
                    if (base4 > 3333){
                        base4 = 3333;
                    }
                    fprintf(outputFile, "%04d", base4);
                } else {
                    fprintf(outputFile, "%c", word[i]);
                }
            }
            fprintf(outputFile, " ");
        }
 
        else if (count % 2 == 0) {
            for (int i = 0; word[i] != '\0'; i++) {
                if (isalpha(word[i])) {
                    word[i] = tolower(word[i]);
                }
                fprintf(outputFile, "%c", word[i]);
            }
            fprintf(outputFile, " ");
        } 
        else if (count % 5 == 0) {
            for (int i = 0; word[i] != '\0'; i++) {
                fprintf(outputFile, "%o", word[i]);
            }
            fprintf(outputFile, " ");
        } 
        else {
            fprintf(outputFile, "%s ", word);
        }
    }

    fclose(outputFile);
    fclose(inputFile);
}


int main(int argc, char* argv[]) {
    if (argc !=4 && argc != 5) {
        printf("Not enough arguments\n");
        return 1;
    }

    if (strcmp(argv[1], "-r") == 0) {
        writeToFileR(argv[4], argv[2], argv[3]);
    } else if (strcmp(argv[1], "-a") == 0) {
        writeToFileA(argv[3], argv[2]);
    } else {
        printf("Invalid option\n");
        return 1;
    }

    return 0;
}
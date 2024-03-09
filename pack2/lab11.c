#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>


int count_length(char* str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

char* reverse_string(char* str) {
    int length = count_length(str);
    char* reversed = (char*)malloc((length + 1) * sizeof(char));
    if (reversed == NULL){
        printf("Memory does not allocated\n");
        return 0;
    }
    for (int i = 0; i < length; i++) {
        reversed[i] = str[length - i - 1];
    }
    reversed[length] = '\0';
    return reversed;
}


char* uppercase_odd_chars(char* str) {
    int length = count_length(str);
    char* uppercase = (char*)malloc((length + 1) * sizeof(char));
    if (uppercase == NULL){
        printf("Memory does not allocated\n");
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


char* rearrange_chars(char *str){
    int length = str_len(str);
    char* new_str = (char*) calloc(length + 1, sizeof(char));
    if (new_str == NULL){
        printf("Memory does not allocated\n");
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


void copy_string(char* dest, char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

char* concatenate_strings(int argc, char* argv[], unsigned int seed) {
    int total_length = 0;
    for (int i = 3; i < argc; i++) {
        total_length += count_length(argv[i]);
    }

    char* result = (char*)malloc((total_length + 1) * sizeof(char));

    int current_index = 0;
    srand(seed);

    while (argc - 3 > 0) {
        int random_index = rand() % (argc - 3) + 3;

        int currentLength = count_length(argv[random_index]);

        copy_string(result + current_index, argv[random_index]); 
        current_index += currentLength;
        argc--;

        for (int i = random_index; i < argc; i++) {
            argv[i] = argv[i + 1];
            
        }
    }
    result[current_index] = '\0'; 

    return result;
}



void Usage()
{
    printf("Usage:\n./lab11 -l | -r | -u | -n 'string'\n./lab11 -c <unsigned int seed> 'string 1' 'string 2' ('string 3' .... 'string N)'\n");
}


int main(int argc, char* argv[]) {
    if (argc < 3) {
        Usage();
        return 1;
    }

    char flag = argv[1][1];
    char* str = argv[2];
    unsigned int seed;

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
            if (argc < 5) {
                printf("Error: Not enough additional arguments for flag -c\n");
                Usage();
                return 1;
            }
            
            if ((seed = atoi(argv[2])) == 0){
                printf("Error: Not enough additional arguments for flag -c\n");
                Usage();
                return 1;
            }
            char* concatenated_string = concatenate_strings(argc, argv, seed);
            printf("Concatenated strings: %s\n", concatenated_string);
            free(concatenated_string);
            break;
        default:
            printf("Error: Invalid flag\n");
            Usage();
            return 1;
    }

    return 0;
}


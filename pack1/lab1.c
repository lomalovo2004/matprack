#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

int Prime_or_not(int num) {
    if (num < 2) {
        return 0;
    }

    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return 0;
        }
    }
    
    return 1;
}


void Multiples(int num, char* multiples) {
    int found = 0;
    int count = 0;
    
    for (int i = 1; i <= 100; i++) {
        if (i % num == 0) {
            found = 1;
            int length = 0;
            int temp = i;
            while (temp != 0)
            {
                temp /= 10;
                length++;
            }
            int temp2 = i;
            for (int j = count + length - 1; j >= count; j--)
            {
                multiples[j] = '0' + (temp2 % 10);
                temp2 /= 10;
            }
            count += length;
            multiples[count++] = ' ';
        }
    }
    
    if (found) {
        multiples[count++] = '\n';
        multiples[count] = '\0';
    } else {
        strcpy(multiples, "No multiples found.\n");
    }
}

void Digits(int num, char* digits_str) {
    if (num == 0) {
        strcpy(digits_str, "Digits: 0\n");
        return;
    }
    
    int digits[10];
    int count = 0;
    
    while (num > 0) {
        digits[count] = num % 10;
        num /= 10;
        count++;
    }
    
    for (int i = count - 1; i >= 0; i--)
    {
        digits_str[count - i - 1] = '0' + digits[i];
    }
    
    digits_str[count++] = '\n';
    digits_str[count] = '\0';
}

void Degrees(int num, char* degrees) 
{
    if (num > 10) {
        strcpy(degrees, "Number should be less than or equal to 10.\n");
        return;
    }
    
    int count = 0;
    
    for (int i = 1; i <= num; i++) {
        for (int j = 1; j <= 10; j++) {
            int product = i * j;
            int length = 0;
            int temp = product;
            while (temp != 0)
            {
                temp /= 10;
                length++;
            }
            int temp2 = product;
            for (int k = count + length - 1; k >= count; k--)
            {
                degrees[k] = '0' + (temp2 % 10);
                temp2 /= 10;
            }
            count += length;
            degrees[count++] = ' ';
        }
        degrees[count - 1] = '\n';
    }
    degrees[count] = '\0';
}

int Sum(int num) {

int sum = 0;
    
    for (int i = 1; i <= num; i++) {
        sum += i;
    }
    
    return sum;
}

int Factorial(int num) {
    int factorial = 1;
    
    for (int i = 2; i <= num; i++) {
        factorial *= i;
    }
    
    return factorial;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: program_name number flag\n");
        return 1;
    }
    

    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Invalid input. Use non-negative integer.\n");
            return 1;
        }
    }


    errno = 0;
    long int number = strtol(argv[1], NULL, 10);
    if (errno != 0 || number > INT_MAX)
    {
        printf("Inlavid input. Number is quite big.\n");
        return 1;
    }
    int num = (int)number;
    char flag = argv[2][1];

switch (flag) {
        case 'h': {
            char multiples[1000];
            Multiples(number, multiples);
            printf("Multiples: %s", multiples);
            break;
        }
        case 'p': {
            if (Prime_or_not(number)) {
                printf("Number is prime.\n");
            } else {
                printf("Number is composite.\n");
            }
            break;
        }
        case 's': {
            char digits_str[10 * sizeof(int)];
            Digits(number, digits_str);
            printf("Digits: ");
            for (int i = 0; i < 10; i++)
            {
                printf("%c ", digits_str[i]);
            }
            printf("\n");
            break;
        }
        case 'e': {
            char degrees[1000];
            Degrees(number, degrees);
            printf("Degrees:\n%s", degrees);
            break;
        }
        case 'a': {
            int sum = Sum(number);
            printf("Sum: %d\n", sum);
            break;
        }
        case 'f': {
            int factorial = Factorial(number);
            printf("Factorial: %d\n", factorial);
            break;
        }
        default:
            printf("Invalid flag.\n");
            break;
    }
    
    return 0;

}

//неправильно переводит
#include <stdio.h>
#include <stdarg.h>

typedef enum{
    OK = 1,
    INVALID
} EXIT_CODE;

EXIT_CODE finite_representation(int base, int count, ...) {
    va_list args;
    va_start(args, count);

    if (count < 1){
        return INVALID;
    }

    if (base <= 0){
        return INVALID;
    }

    for (int i = 0; i < count; i++) {
        double decimal = va_arg(args, double);
        double fraction = decimal - (int)decimal;
        
        int converted_fraction = 0;
        double power = 1.0 / base;

        for (int j = 0; j < 10; j++) {
            power /= base;
            converted_fraction *= base;
            int digit = (int)(fraction / power);
            converted_fraction += digit;
            fraction -= digit * power;
        }
        
        if (converted_fraction == 0 || converted_fraction == base - 1) {
            printf("%f does not have a finite representation in base %d system\n", decimal, base);
           
        } else {
            printf("%f has a finite representation in base %d system\n", decimal, base);
        }
    }
    va_end(args);
    return OK;
}

int main() {
    double fraction1 = 0.5;
    double fraction2 = 0.457;
    double fraction3 = 0.576;
    int base = 8;
    int result = finite_representation(base, 3, fraction1, fraction2, fraction3);
    if (result == INVALID){
        printf("Count must be greater 1 or greater and base must be greater than 0\n");
    }
    return 0;
}
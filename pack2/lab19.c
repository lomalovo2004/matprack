#include <stdio.h>
#include <stdarg.h>

int finite_representation(int base, int count, ...) {
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; i++) {
        double decimal = va_arg(args, double);
        double fraction = decimal - (int)decimal;
        // Преобразование десятичной дроби в систему счисления с заданным основанием
        int converted_fraction = 0;
        double power = 1.0 / base;

        for (int j = 0; j < 10; j++) {
            power /= base;
            converted_fraction *= base;
            int digit = (int)(fraction / power);
            converted_fraction += digit;
            fraction -= digit * power;
        }
        // Проверка наличия бесконечной последовательности нулей или девяток
        if (converted_fraction == 0 || converted_fraction == base - 1) {
            va_end(args);
            return 0;
        }
    }
    va_end(args);
    return 1;
}

int main() {
    double fraction1 = 0.25;
    double fraction2 = 2.457;
    double fraction3 = 0.5;
    int base = 3;
    int result = finite_representation(base, 3, fraction1, fraction2, fraction3);
    if (result) {
        printf("All fractions have finite representation in base %d system.\n", base);
    } else {
        printf("One or some fractions do not have finite representation in base %d system\n", base);
    }
    return 0;
}
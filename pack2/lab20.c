#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

typedef enum {
    OK,
    INVALID_ARGUMENTS,
    BAD_ALLOC
} EXIT_CODE;

EXIT_CODE polynom_decomposition (double EPS, double a, double** res, int degree, ...) {
    double coefficient;
    int derivative_coef = 1, deg;
    long long int factorial = 1;

    if (degree > 20) {
        return INVALID_ARGUMENTS;
    }

    double* new_coefficients = (double*)calloc((degree + 1), sizeof(double));
    if (new_coefficients == NULL) {
        return BAD_ALLOC;
    }

    va_list(ptr);
    va_start(ptr, degree);

    deg = 0;
    for (int n = 0; n <= degree; n++) {
        coefficient = va_arg(ptr, double);

        int k = deg;
        while (k >= 0) {
            if (fabs(coefficient) < EPS) {
                break;
            } else {
                new_coefficients[deg - k] += coefficient * pow(a, k) * derivative_coef;
            }

            if (k > 1) {
                derivative_coef *= k;
            }
            k--;
        }
        derivative_coef = 1;
        deg++;
    }

    va_end(ptr);

    for (int i = 2; i <= degree; i++) {
        factorial *= i;
        new_coefficients[i] /= 1.0 * factorial;
    }

    *res = new_coefficients;
    return OK;
}

int main () {
    double *new_coefficients;
    int st;

    double EPS = __DBL_EPSILON__;
    int degree = 4;  
    double a = 1.0;

    if ((st = polynom_decomposition(EPS, a, &new_coefficients, degree, -1.0, 5.0, -3.0, 0.0, 1.0)) == INVALID_ARGUMENTS) {
        printf("Invalid arguments\n");
        return INVALID_ARGUMENTS;
    } else if (st == BAD_ALLOC) {
        printf("Memory does not allocated\n");
        return BAD_ALLOC;
    }

    for (int i = 0; i <= degree; i++) {
        printf("%f\n", new_coefficients[i]);
    }

    free(new_coefficients);
    return OK;
}
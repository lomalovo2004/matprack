#include <stdio.h>
#include <math.h>
#include <stdlib.h>

long double calculate_e_limit(long double epsilon) {
    return powl(1 + epsilon, 1 / epsilon);
}

long double calculate_e_series(long double epsilon) {
    long double e = 1.0;
    long double term = 1.0;
    int n = 1;

    while (fabsl(term) > epsilon) {
        term /= n;
        e += term;
        n++;
    }

    return e;
}

long double calculate_e_equation(long double epsilon) {
    long double e = 1.0;
    int n = 1;

    while (fabsl(logl(e) - 1) > epsilon) {
        e = powl(1 + epsilon, n);
        n++;
    }
    
    return e;
}

long double calculate_pi_limit(long double epsilon) {
    return powl(4 / (1 + epsilon), 1 / epsilon);
}

long double calculate_pi_series(long double epsilon) {
    long double pi = 0.0;
    long double term = 1.0;
    int n = 0;

    while (fabsl(term) > epsilon) {
        term = (n % 2 == 0) ? 1.0 / (2 * n + 1) : -1.0 / (2 * n + 1);
        pi += term;
        n++;
    }

    return 4 * pi;
}

long double calculate_pi_equation(long double epsilon) {
    long double pi = 0.0;
    int n = 0;

    while (fabsl(pi - atanl(1) * 4) > epsilon) {
        pi = 4 * atanl(1 / powl(1 + epsilon, n));
        n++;
    }

    return pi;
}

long double calculate_ln2_limit(long double epsilon) {
    return powl(1 + epsilon, 1 / epsilon) - 1;
}

long double calculate_ln2_series(long double epsilon) {
    long double ln2 = 0.0;
    long double term = 1.0;
    int n = 1;

    while (fabsl(term) > epsilon) {
        term = 1.0 / n;
        ln2 += term;
        n++;
    }

    return ln2;
}

long double calculate_ln2_equation(long double epsilon) {
    long double ln2 = 0.0;
    int n = 1;

    while (fabsl(logl(2) - ln2) > epsilon) {
        ln2 = logl(powl(1 + epsilon, n));
        n++;
    }

    return ln2;
}

long double calculate_2_limit(long double epsilon) {
    return powl(1 + epsilon, 1 / epsilon);
}

long double calculate_2_series(long double epsilon) {
    long double two = 0.0;
    long double term = 1.0;
    int n = 0;

    while (fabsl(term) > epsilon) {
        term = powl(-1, n) / powl(2, n);
        two += term;
        n++;
    }

    return two;
}

long double calculate_2_equation(long double epsilon) {
    long double two = 0.0;
    int n = 0;

    while (fabsl(2 - two) > epsilon) {
        two = powl(1 + epsilon, n);
        n++;
    }

    return two;
}

long double calculate_gamma_limit(long double epsilon) {
    return 1 - logl(epsilon);
}

long double calculate_gamma_series(long double epsilon) {
    long double gamma = 0.0;
    long double term = 1.0;
    int n = 1;

    while (fabsl(term) > epsilon) {
        term = 1.0 / n;
        gamma += term;
        n++;
    }

    return gamma;
}

int main() {
    long double epsilon;

    printf("Введите значение epsilon: ");
    scanf("%Lf", &epsilon);

    printf("Number\t\tLimit\t\tSeries\t\tEquation\n");
    printf("e\t\t%.6Lf\t%.6Lf\t%.6Lf\n", calculate_e_limit(epsilon), calculate_e_series(epsilon), calculate_e_equation(epsilon));
    printf("pi\t\t%.6Lf\t%.6Lf\t%.6Lf\n", calculate_pi_limit(epsilon), calculate_pi_series(epsilon), calculate_pi_equation(epsilon));
    printf("ln2\t\t%.6Lf\t%.6Lf\t%.6Lf\n", calculate_ln2_limit(epsilon), calculate_ln2_series(epsilon), calculate_ln2_equation(epsilon));
    printf("2\t\t%.6Lf\t%.6Lf\t%.6Lf\n", calculate_2_limit(epsilon), calculate_2_series(epsilon), calculate_2_equation(epsilon));
    printf("gamma\t\t%.6Lf\t%.6Lf\t%.6Lf\n", calculate_gamma_limit(epsilon), calculate_gamma_series(epsilon), calculate_gamma_series(epsilon));

    return 0;
}
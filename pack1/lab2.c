#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>


long double factorial(long double n)
{
    if (n == 0 || n == 1) return 1;
    return n * factorial(n - 1);
}


long double calculate_e_limit(long double epsilon) {
    long double  n = 1;
    long double prev = 0;
    // Формула e = (1 + 1/n)^n
    long double current = 2; 
    // максимальное количество приближений к пределу
    int max_n = 200;

    do
    {
        if (n == max_n) {break;};

        prev = current;
        n++;
        current = pow((1 + 1/n), n);

    } while (epsilon < fabsl(prev - current));

    return current;
}

long double calculate_e_series(long double epsilon) {
    long double prev_summ = 0;
    int n = 0;
    // Формула e = Σ(n=0 -> ∞) 1/n!
    long double current_sum = 1;

    // Формула e = Σ(n=0 -> ∞) 1/n!
     while (fabsl(current_sum) > epsilon) {
        current_sum = 1/factorial(n);
        prev_summ += current_sum;
        n++;
    }

    return prev_summ;
}

long double calculate_e_equation(long double epsilon) {
    long double x = 1.0;
    long double diff = 1.0;
    
    // Уравнение ln x = 1
    while (diff > epsilon) {
        long double ex = logl(x);
        diff = fabsl(ex - 1);
        
        if (ex > 1) {
            x -= epsilon;
        } else {
            x += epsilon;
        }
    }
    
    return x;
}


long double calculate_pi_limit(long double epsilon)
{
    long double current_limit = 4.0;
    long double prev_limit = 0.0;
    int n = 2;
    do
    {
        prev_limit = current_limit;
        current_limit = current_limit * (4.0 * n * ( n - 1.0)) / pow(2.0 * n - 1.0, 2);
        n++;
    } while (fabsl(prev_limit - current_limit) >= epsilon);
    return current_limit;
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
    long double  n = 1;
    long double prev = 0;
    // Формула ln 2 = lim(n->∞) n * (2^1/n - 1)
    long double current = 1; 
    int max_n = 200;

    do
    {
        if (n == max_n) {break;};

        prev = current;
        n++;
        current = n * (pow(2, 1/n) - 1);

    } while (epsilon < fabsl(prev - current));

    return current;
}

long double calculate_ln2_series(long double epsilon) {
    long double prev_summ = 0;
    int n = 1;
    // Формула ln 2 = Σ(n=1 -> ∞) (-1)^1/n / n 
    long double current_sum = 1;

     while (fabsl(current_sum) > epsilon) {
        current_sum = powl(-1.0, n-1) / n;
        prev_summ += current_sum;
        n++;
    }

    return prev_summ;
}

// 
long double calculate_ln2_equation(long double epsilon) {
    long double x = 0.0;
    long double diff = 1.0; 

    // Уравнение e^x = 2
    while (diff > epsilon) {
        long double ex = expl(x);
        diff = fabsl(ex - 2);
        
        if (ex > 2) {
            x -= epsilon;
        } else {
            x += epsilon;
        }
    }
    
    return x;
}


long double calculate_sqrt2_limit(long double epsilon) {
    long double  n = 0;
    long double prev = 0;
    long double current = -0.5; 
    int max_n = 200;

    do
    {
        if (n == max_n) {break;};

        prev = current;
        n++;
        current = (2.0 * prev - pow(prev, 2.0) + 2)/2;

    } while (epsilon < fabsl(prev - current));

    return current;
}

long double calculate_sqrt2_series(long double epsilon) {
    long double pr = 1.0;
    int k = 2;
    epsilon = epsilon + 1;
    // Формула sqrt2 = П(k=2 -> ∞) 2^(2^-k)
    long double term = powl(2, powl(2, -k));
 
    while (fabsl(term) > epsilon) {
        pr *= term;
        k++;
        term = powl(2, powl(2, -k));
    }

    return pr;
}


long double calculate_sqrt2_equation(long double epsilon) {
    long double x = 1.0;
    long double diff = 1.0;
    int c = 0; 
    int max_n = 10000000;

    // Уравнение x^2 = 2 
    while (diff > epsilon) {
        long double ex = powl(x, 2);
        diff = fabsl(ex - 2);
        
        if (ex > 2) {
            x -= epsilon;
        } else {
            x += epsilon;
        }
        
        c++; 
        if (c == max_n){break;}
    }
    return x;
}


long double sum_n(int n)
{
    long double sum = 1;
    for (int i = 2; i <= n; i++)
    {
        sum += 1.0/i;
    }

    return sum;
    
}

long double calculate_gamma_limit(long double epsilon)
{
    long double prev = 0;
    long double current = 1;
    int n = 1;
    int max_n = 200;

    do
    {
        if (n == max_n) {break;};

        prev = current;
        n *= 2;
        current = sum_n(n) - log(n);

    } while (fabsl(prev - current) > epsilon);

    return current;
  
}

long double calculate_gamma_series(long double epsilon)
{
    long double prev = 0;
    long double current = 0.5;
    int k = 2;
    long double l = 0;

    do
    {
        prev = current;
        k++;
        l = sqrtl(k);
        if (fmodl(l,1.0) == 0)
            {
                k++;
                l = (int)powl(k, 1.0/2.0);
            }
        current += 1.0/powl((int)l,2.0) - 1.0/k;


    } while (fabsl(prev - current) > epsilon);

    return current - powl(M_PI,2)/6;
    
}


bool not_simple(int n)
{
    if (n > 3)
    {
        if (n % 2 == 0)
            return true;
        for (int i = 3; i <= sqrtl(n); i+=2)
        {
            if (n % i == 0)
                return true;
        }
    }
    return false;
}


long double calculate_gamma_equation(long double epsilon)
{
    int p = 2;
    long double current = log(2) * 0.5;
    long double prev = 0;
    long double product = 0.5;

    do
    {
        prev = current;
        do
        {
            p++;
        } while (not_simple(p));
        product *= (p - 1.0)/p;
        current = logl(p) * product;
        

    } while (fabsl(prev - current) > epsilon);
    return (-log(current));
 
}



int main() {
    long double epsilon;
    printf("Введите значение epsilon: ");
    scanf("%Lf", &epsilon);

    if (epsilon < 0 || epsilon > 1){
        printf("Epsilon must be gteater than 0 and smaller than 1\n");
        return 0;
    }


    printf("Number\t\tLimit\t\tSeries\t\tEquation\n");
    printf("e\t\t%.6Lf\t%.6Lf\t%.6Lf\n", calculate_e_limit(epsilon), calculate_e_series(epsilon), calculate_e_equation(epsilon));
    printf("pi\t\t%.6Lf\t%.6Lf\t%.6Lf\n", calculate_pi_limit(epsilon), calculate_pi_series(epsilon), calculate_pi_equation(epsilon));
    printf("ln2\t\t%.6Lf\t%.6Lf\t%.6Lf\n", calculate_ln2_limit(epsilon), calculate_ln2_series(epsilon), calculate_ln2_equation(epsilon));
    printf("sqr2\t\t%.6Lf\t%.6Lf\t%.6Lf\n", calculate_sqrt2_limit(epsilon), calculate_sqrt2_series(epsilon), calculate_sqrt2_equation(epsilon));
    printf("gamma\t\t%.6Lf\t%.6Lf\t%.6Lf\n", calculate_gamma_limit(epsilon), calculate_gamma_series(epsilon), calculate_gamma_equation(epsilon));

    return 0;
}
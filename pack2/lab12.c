#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <math.h>

typedef enum{
    OK = 0,
    INVALID
} EXIT_CODE;




EXIT_CODE geometric_mean (double* result, int count, ...)
{

    if (count < 1){
        return INVALID;
    }

    *result = 1;

    va_list args;

    va_start(args, count);

    for (int i = 0; i < count; i++)
    {

        double temp = va_arg(args, double);
        *result *= temp;

    }


    va_end(args);
    *result = pow(*result, 1.0 / count);


    return OK;

}


double grade(double base, int exponent)
{
    if (exponent == 0)
        return 1.0;
    else if (exponent < 0)
        return 1.0 / grade(base, -exponent);
    else if (exponent % 2 == 0)
    {
        double temp = grade(base, exponent / 2);
        return temp * temp;
    }
    else
    {
        double temp = grade(base, (exponent - 1) / 2);
        return base * temp * temp;
    }
}



int main()
{
    double res = 0;
    int a = geometric_mean(&res, 3, (double) 3, (double) 3, (double) 9);

    if (a == INVALID){
        printf("Count must 1 or greater\n");
    }
    else{
        printf("Average geometric mean: %.2f\n", res);
    }


    double result = grade(2.0, 5);
    printf("Grade: %.2f\n", result);
    
    result = grade(2.0, -3);
    printf("Grade: %.2f\n", result);
    
    return 0;
}
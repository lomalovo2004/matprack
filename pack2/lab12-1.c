#include <stdio.h>
#include <stdarg.h>
#include <math.h>

double geometric_mean(int count, ...)
{
    va_list args;
    double product = 1.0;
    
    va_start(args, count);
    
    for (int i = 0; i < count; i++)
    {
        double num = va_arg(args, double);
        product *= num;
    }
    
    va_end(args);
    
    return pow(product, 1.0 / count);
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
    double mean = geometric_mean(3, 2.0, 4.0, 8.0);
    printf("Average geometric mean: %.2f\n", mean);
    
    double result = grade(2.0, 5);
    printf("Grade: %.2f\n", result);
    
    result = grade(2.0, -3);
    printf("Grade: %.2f\n", result);
    
    return 0;
}

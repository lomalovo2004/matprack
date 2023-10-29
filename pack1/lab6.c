#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

#define OK 0
#define INVALID_INPUT 1
#define OVERFLOWED 2

int is_double(const char* s)
{
    int dot_count = 0;
    int digit_count = 0;
    int i = 0;

    if (s[i] == '-')
    {
        i++;
    }

    for (; s[i] != '\0'; i++)
    {
        if (s[i] == '.')
        {
            dot_count++;
        }
        else if (isdigit(s[i]))
        {
            digit_count++;
        }
        else
        {
            return 0;
        }
    }

    return dot_count <= 1 && digit_count > 0;
}

int integral_A(double epsilon, double *result)
{   
    unsigned long long step = 1;
    double part = 1;
    double current = log(2);
    double prev = log(2);
    
    do
    {
       if (step > ULLONG_MAX / 2)
       {
        return OVERFLOWED;
       }

       prev = current;
       step *= 2;
       part /= 2;
       current = 0;
       double x;

       for (int i = step; i > 0; i--)
       {
            x = 1.0 * i / step;
            current += log(1.0 + x)/ x * part;
       }

    } while (fabs(current - prev) >= epsilon);
    *result = current;
    return OK;
}

int integral_B(double epsilon, double *result)
{
    unsigned long long step = 1;
    double part = 1;
    double prev, current = exp(-0.5);

    do
    {
        if (step > ULLONG_MAX / 2)
        {
            return OVERFLOWED;
        }

        prev = current;
        step *= 2;
        part /= 2;
        current = 0;
        double x;

        for (int i = step; i > 0; i--)
        {
            x = 1.0 * i / step;
            current += exp(x * x * -0.5) * part;
        }
        

    } while (fabs(prev - current) >= epsilon);
    *result = current;
    return OK;
}

int integral_C(double epsilon, double* result)
{
    unsigned long long step = 1;
    double part = 1;
    double prev, current = 0;

    do
    {
        if (step > ULLONG_MAX / 2)
        {
            return OVERFLOWED;
        }
        
        prev = current;
        step *= 2;
        part /= 2;
        current = 0;
        double x;

        for (int i = 0; i < step; i++)
        {
            x = 1.0 * i / step;
            current += log(1.0 / (1.0 - x)) * part;
        }

    } while (fabs(prev - current) >= epsilon);
    *result = current;
    return OK;
    
}

int integral_D(double epsilon, double* result)
{
    unsigned long long step = 1;
    double part = 1;
    double prev, current = 1;

    do
    {
        if (step > ULLONG_MAX / 2)
        {
            return OVERFLOWED;
        }
        
        prev = current;
        step *= 2;
        part /= 2;
        current = 0;
        double x;

        for (int i = step; i > 0; i--)
        {
            x = 1.0 * i / step;
            current += pow(x, x) * part;

}
        
    } while (fabs(prev - current) >= epsilon);
    *result = current;
    return OK;
}


int main(int argc, char* argv[])
{   
    if (argc != 2 || !is_double(argv[1]))
    {
        return 1;
    }

    double epsilon = atof(argv[1]);
    if (epsilon <= 0)
    {
        printf("Epsilon must be greater than 0\n");
        return 1;
    }
    int length = strlen(argv[1]);
    double result;

    if (integral_A(epsilon, &result) == OK)
    {
        printf("Integral A %.*f\n", length, result);
    }
    else
        printf("There is an overflow\n");
    
    if (integral_B(epsilon, &result) == OK)
    {
        printf("Integral B %.*f\n", length, result);
    }
    else
        printf("There is an overflow\n");
    
    if (integral_C(epsilon, &result) == OK)
    {
        printf("Integral C %.*f\n", length, result);
    }
    else
        printf("There is an overflow\n");
    
    if (integral_D(epsilon, &result) == OK)
    {
        printf("Integral D %.*f\n", length, result);
    }
    else
        printf("There is an overflow\n");

    return 0;
}

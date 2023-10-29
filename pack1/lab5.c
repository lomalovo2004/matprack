#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

double sumA(double epsilon, double x)
{
    int s = 0;
    double sum = 0;
    double element = 1;
    do
    {
        sum += element;
        ++s;
        element *= x/s;
        
    } while (fabs(element) >= epsilon);
    return sum;
    
}

double sumB(double epsilon, double x)
{
    int s = 0;
    double sum = 0;
    double element = 1;

    do
    {
       sum += element;
       ++s;
       element *= (-1.0 * x * x) / (2 * s * (2 * s - 1.0));

    } while (fabs(element) >= epsilon);

    return sum;
    
}

double sumC(double epsilon, double x)
{
    int s = 0;
    double sum = 0;
    double element = 1;
    do
    {
        sum += element;
        ++s;
        element *= (9.0 * s * s * x * x) / (9.0 * s * s - 9.0 * s + 2.0);
    } while (fabs(element) >= epsilon);
    return sum;
}

double sumD(double epsilon, double x)
{
    int s = 1;
    double sum = 0;
    double element = -1.0 * x * x / 2.0;
    do
    {
        sum += element;
        ++s;
        element *= (-1.0 * x * x * (2.0 * s - 1)) / (2.0 * s);
        
    } while (fabs(element) >= epsilon);

    return sum;
    
}

int main(int argc, char* argv[])
{
    if (argc < 3) {
        printf("Usage: %s <epsilon> <x>\n", argv[0]);
        return 1;
    }

    double epsilon = atof(argv[1]);
    double x = atof(argv[2]);

    int length = strlen(argv[1]) - 2;
    printf("epsilon = %.*f\n", length, epsilon);
    printf("sum A %.*f\n", length, sumA(epsilon, x));
    printf("sum B %.*f\n", length, sumB(epsilon, x));
    if (fabs(x) < 1)
    {
        printf("sum C %.*f\n", length, sumC(epsilon, x));
        printf("sum D %.*f\n", length, sumD(epsilon, x));
    }
    else 
    {
        printf("x must be in range (-1;1)\n");
    }

    return 0;
}

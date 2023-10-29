#include <stdio.h>
#include <math.h>

double eq_1(double x){
    return exp(x) + 4.2 + x;
}

double eq_2(double x){
    return log(x) - x + 32 + sin(pow(x, 4));
}

double eq_3(double x){
    return sqrt(x) + x - 10;
}

double eq_4(double x){
    return cos(exp(x)) + log(x);
}

double equation(double left_border, double right_border, double epsilon, double (*function)(double)){
    double central;
    while (fabs(left_border - right_border) > epsilon){
        central = (left_border + right_border) / 2;
        if (fabs(function(central)) < epsilon){
            return central;
        }
        if (function(central) > epsilon){
            right_border = central;
        }
        else {
            left_border = central;
        }
    }
    return (left_border + right_border) / 2;
}

int main(){
    printf("Equation№1: %f\n", equation(0.0, 1.0, 0.00001, eq_1));
    printf("Equation№2: %f\n", equation(-10.0, 54.8, 0.00001, eq_2));
    printf("Equation№3: %f\n", equation(-100.0, 100.0, 0.00001, eq_3));
    printf("Equation№4: %f\n", equation(-12.0, 37.9, 0.00001, eq_4));
    return 0;
}
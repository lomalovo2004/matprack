#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void quadratic_equation(double a, double b, double c) {
    double discriminant = b * b - 4 * a * c;
    
    if (discriminant > 0) {
        double root1 = (-b + sqrt(discriminant)) / (2 * a);
        double root2 = (-b - sqrt(discriminant)) / (2 * a);
        
        printf("Roots: %.2f, %.2f\n", root1, root2);
    } 
    else if (discriminant == 0) {
        double root = -b / (2 * a);
        
        printf("Root: %.2f\n", root);
    } 
    else {
        printf("No real roots\n");
    }
}

void permutations(double a, double b, double c, double epsilon) {
    quadratic_equation(a, b, c);
    quadratic_equation(a, c, b);
    quadratic_equation(b, a, c);
    quadratic_equation(b, c, a);
    quadratic_equation(c, a, b);
    quadratic_equation(c, b, a);
}

void check_divisibility(int num1, int num2) {
    if (num2 == 0){
        printf("It is impossible to divide by 0\n");
        return;
    }
    
    if (num2 != 0 && num1 % num2 == 0) {
        printf("%d is divisible by %d\n", num1, num2);
    } 
    else {
        printf("%d is not divisible by %d\n", num1, num2);
    }
}

void check_triangle(double a, double b, double c) {
    if (a > 0 && b > 0 && c > 0) {
        if (fabs(a * a + b * b - c * c) < 0.0001 && fabs(a * a + c * c - b * b) < 0.0001 && fabs(b * b + c * c - a * a) < 0.0001) {
            printf("The given lengths can form a right triangle\n");
        } else {
            printf("The given lengths cannot form a right triangle\n");
        }
    } 
    else {
        printf("Invalid side lengths\n");
    }
}



int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("No flag provided\n");
        return 1;
    }
    
    char flag = argv[1][1];
    
    switch (flag) {
        case 'q':
            if (argc != 6) {
                printf("Invalid number of parameters for flag -q\n");
                return 1;
            }
            
            double epsilon;
            double coefficients[3];
            
            if (sscanf(argv[2], "%lf", &epsilon) != 1 ||
                sscanf(argv[3], "%lf", &coefficients[0]) != 1 ||
                sscanf(argv[4], "%lf", &coefficients[1]) != 1 ||
                sscanf(argv[5], "%lf", &coefficients[2]) != 1) {
                printf("Invalid parameter type for flag -q\n");
                return 1;
            }
            
            permutations(coefficients[0], coefficients[1], coefficients[2], epsilon);
            break;
            
        case 'm':
            if (argc != 4) {
                printf("Invalid number of parameters for flag -d\n");
                return 1;
            }
            
            int num1;
            int num2;
            
            if (sscanf(argv[2], "%d", &num1) != 1 || sscanf(argv[3], "%d", &num2) != 1) {
                printf("Invalid parameter type for flag -d\n");
                return 1;
            }
            

            if (floor(num1) != num1 || floor(num2) != num2) {
                printf("Invalid parameter type for flag -m\n");
                return 1;
            }

            check_divisibility(num1, num2);
            break;
            
        case 't':
            if (argc != 6) {
                printf("Invalid number of parameters for flag -t\n");
                return 1;
            }
            
            double side1;
            double side2;
            double side3;
            
            if (sscanf(argv[2], "%lf", &side1) != 1 ||
                sscanf(argv[3], "%lf", &side2) != 1 ||
                sscanf(argv[4], "%lf", &side3) != 1) {
                printf("Invalid parameter type for flag -t\n");
                return 1;
            }
            
            check_triangle(side1, side2, side3);
            break;
            
        default:
            printf("Invalid flag\n");
            return 1;
    }
    
    return 0;
}

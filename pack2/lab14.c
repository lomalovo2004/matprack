#include <stdio.h>
#include <stdarg.h>
#include <math.h>

#define epsilon 0.0001

typedef struct {
    double x;
    double y;
} Point;

int sign(double x){
    return (x > 0) - (x < 0);
}

double straight(Point p1, Point p2, Point p3){
    double x = p2.x;
    double x1 = p1.x;
    double x2 = p3.x;
    double y = p2.y;
    double y1 = p1.y;
    double y2 = p3.y;
    return ((x - x1) * (y2 - y) - (x2 - x) * (y - y1));
}

int polygon(int coef, ...){
    if (coef < 3){
        printf("Not enough sides for polygon\n");
        return 0;
    }
    Point array[coef];
    int length = coef, prev_sign;
    va_list ptr;
    va_start(ptr, coef);
    for (int i = 0; i < length; i++) {
        array[i] = va_arg(ptr, Point);
    }
    va_end(ptr);
    int cur_sign = sign(straight(array[0], array[1], array[2]));
    for (int i = 0; i < length; ++i) {
        double temp = straight(array[i], array[(i + 1) % length], array[(i + 2) % length]);
        if (fabs(temp) < epsilon){
            printf("is not convex\n");
            return 0;
        }
        prev_sign = cur_sign;
        cur_sign = sign(temp);
        if (cur_sign != prev_sign){
            printf("is not convex\n");
            return 0;
        }
    }
    printf("is convex\n");
    return 1;
}

int polynomial(double *res, double x, int n, int coef, ...){
    *res = 0;
    int length = coef;
    double array[coef];
    va_list ptr;
    va_start(ptr, coef);
    for (int i = length - 1; i >= 0; --i) {
        array[i] = va_arg(ptr, double);
    }
    va_end(ptr);
    for (int i = n; i >= 0 ; --i) {
        *res += pow(x, i) * array[i];
    }
    return 1;
}

int main(){
    double res = 0;
    Point p1 = {-5.60, 0.0};
    Point p3 = {-15.7, 4.9};
    Point p2 = {-15.7, 0.0};
    Point p4 = {-5.60, 4.9};
    Point p5 = {-8.0, 4.9};
    Point p6 = {2.0, 4.0};
    Point p7 = {5.0, 7.0};
    Point p8 = {8.0, 5.0};
    Point p9 = {7.0, 2.0};
    Point p10 = {4.0, 1.0};
    printf("Polygon№1 ");
    polygon(5, p1, p2, p3, p4, p5);
    printf("Polygon№2 ");
    polygon(5, p6, p7, p8, p9, p10);
    polynomial(&res, 16., 3, 3, 2.0, 0., 0.);
    printf("Polynomial#1: %f\n", res);
    polynomial(&res, 23., 3, 3, 2.34, 0.123, 90.1);
    printf("Polynomial#2: %f\n", res);
    return 0;
}
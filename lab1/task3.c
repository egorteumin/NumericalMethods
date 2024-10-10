#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define epsilon 0.001

//  tg(0.5х + 0.1) = х^2
double func_a(double x){
    return tan(0.5*x + 0.1) - x*x;
}



//  х^2 + х - 5
double func_b(double x){
    return x*x + x - 5;
}

// 2x + 1
double func_b_diff(double x){
    return 2*x + 1;
}



//  х^3 + 3х^2 - 2
double func_c(double x){
    return x*x*x + 3*x*x - 2;
}

// 3x^2 + 6x
double func_c_diff(double x){
    return 3*x*x + 6*x;
}



//  x0 = a; b - неподвижная точка
double metod_hord(double x, double r_border, double (*func)(double)){
    printf("x0 = %f\n", x);
    int counter_1 = 1;
    int counter_2 = 0;

    double prev_x = x+1;
    double func_res = 0;
    while(fabs(x - prev_x) > epsilon){
        prev_x = x;
        func_res = func(x);
        x = x - func_res*(r_border-x) / (func(r_border)-func_res);

        printf("x%d = %f\t|x%d-x%d| = %f\n", counter_1, x, counter_1, counter_2, fabs(x-prev_x));
        counter_1++;
        counter_2++;
    }
    return x;
}

//  x0 = b; a - неподвижная точка
double metod_newton(double x, double (*func)(double), double (*func_diff)(double)){
    printf("x0 = %f\n", x);
    int counter_1 = 0;
    int counter_2 = 1;

    double prev_x = x+1;
    while(fabs(x - prev_x) > epsilon){
        prev_x = x;
        x = x - func(x)/func_diff(x);

        printf("x%d = %f\t|x%d-x%d| = %f\n", counter_2, x, counter_2, counter_1, fabs(x-prev_x));
        counter_1++;
        counter_2++;
    }
    return x;
}

double metod_combine(double l_border, double r_border, double (*func)(double), double (*func_diff)(double)){
    printf("l_x0 = %f\tr_x0 = %f\n", l_border, r_border);
    int counter = 1;
    
    double func_res = 0;
    while(fabs(r_border - l_border) > epsilon){
        func_res = func(l_border);
        l_border = l_border - func_res*(r_border-l_border) / (func(r_border)-func_res);
        r_border = r_border - func(r_border)/func_diff(r_border);

        printf("l_x%d = %f\tr_x%d = %f\t|r_x%d-l_x%d| = %f\n", counter, l_border, counter, r_border, counter, counter, fabs(r_border-l_border));
        counter++;
    }
    return 0.5*(l_border+r_border);
}

int main(){
    printf("а) tg(0.5х+0.1) = х^2\n");
    printf("Метод хорд: x = %f\n", metod_hord(2.46, 2.75, func_a));

    printf("\nб) х^2 + х - 5 = 0\n");
    printf("Метод касательных: x = %f\n", metod_newton(2.2, func_b, func_b_diff));

    printf("\nв) х^3 + 3х^2 - 2 = 0\n");
    printf("Комбинированный метод: x = %f\n", metod_combine(0.5, 1, func_c, func_c_diff));

    return 0;
}
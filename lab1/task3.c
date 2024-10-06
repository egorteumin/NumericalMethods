#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define epsilon 0.001

//  tg(0.5х + 0.1) = х^2
double func_a(double x){
    return tan(0.5*x + 0.1) - x*x;
}

// //          1
// //  ------------------ - 2x
// //  2cos(0.5x + 0.1)^2
// double func_a_diff(double x){
//     return 1 / (2 * pow(cos(0.5*x + 0.1), 2)) - 2*x;
// }



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
    double prev_x = x+1;
    double func_res = 0;
    while(fabs(x - prev_x) > epsilon){
        prev_x = x;
        func_res = func(x);
        x = x - func_res*(r_border-x) / (func(r_border)-func_res);
        // printf("x = %f\tx-prev_x = %f\n", x, x-prev_x);
    }
    return x;
}

//  x0 = b; a - неподвижная точка
double metod_newton(double x, double (*func)(double), double (*func_diff)(double)){
    double prev_x = x+1;
    while(fabs(x - prev_x) > epsilon){
        prev_x = x;
        x = x - func(x)/func_diff(x);
        // printf("x = %f\tx-prev_x = %f\n", x, x-prev_x);
    }
    return x;
}

double metod_combine(double l_border, double r_border, double (*func)(double), double (*func_diff)(double)){
    double func_res = 0;
    while(r_border - l_border > epsilon){
        func_res = func(l_border);
        l_border = l_border - func_res*(r_border-l_border) / (func(r_border)-func_res);
        r_border = r_border - func(r_border)/func_diff(r_border);
        // printf("l_x = %f\tr_x = %f\tr_x-l_x = %f\n", l_border, r_border, r_border - l_border);
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
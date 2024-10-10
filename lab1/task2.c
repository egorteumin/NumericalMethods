#include <stdio.h>
#include <math.h>

#define epsilon 0.001

//  (2-х) * е^х = 0
//  x = 2
//  phi(x) = 2
double func(double x){
    return 2;
}

double iter_method(double x, double (*func)(double)){
    printf("x0 = %f\n", x);
    int counter_1 = 0;
    int counter_2 = 1;

    double prev_x = x + 1;
    while(fabs(x-prev_x) > epsilon){
        prev_x = x;
        x = func(x);

        printf("x%d = %f\t|x%d-x%d| = %f\n", counter_2, x, counter_2, counter_1, fabs(x-prev_x));
        counter_1++;
        counter_2++;
    }
    return x;
}

int main(){
    printf("(2-x) * e^x = 0\n");
    printf("Итерационный метод: x = %f\n", iter_method(1.1, func));
    return 0;
}
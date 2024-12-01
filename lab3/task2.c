#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define epsilon 0.001

void f(double **matrix, double x, double y){
    matrix[0][0] = tan(x*y) - x*x;
    matrix[1][0] = 7*x*x + 2*y*y - 1;
    return;
}

void f_diff(double **matrix, double x, double y){
    double a = 1 / (cos(x*y)*cos(x*y));
    
    matrix[0][0] = y*a - 2*x;
    matrix[0][1] = x*a;
    matrix[1][0] = 14*x;
    matrix[1][1] = 4*x;
    return;
}

double det(double **matrix){
    return matrix[0][0]*matrix[1][1]-matrix[0][1]*matrix[1][0];
}

void inverse(double **matrix, double **inverse_matrix){
    double deter = 1/det(matrix);
    
    inverse_matrix[0][0] = matrix[1][1]*deter;
    inverse_matrix[0][1] = -matrix[0][1]*deter;
    inverse_matrix[1][0] = -matrix[1][0]*deter;
    inverse_matrix[1][1] = matrix[0][0]*deter;
    return;
}

void phi(double **matrix, double **matrix_f_diff_inv, double **matrix_f){
    matrix[0][0] -= matrix_f_diff_inv[0][0]*matrix_f[0][0] +
                    matrix_f_diff_inv[0][1]*matrix_f[1][0];
    matrix[1][0] -= matrix_f_diff_inv[1][0]*matrix_f[0][0] +
                    matrix_f_diff_inv[1][1]*matrix_f[1][0];
    return;
}

int main(){
    double **matrix_X = (double**)malloc(2*sizeof(double*));
    double **matrix_f_diff = (double**)malloc(2*sizeof(double*));
    double **matrix_f_diff_inv = (double**)malloc(2*sizeof(double*));
    double **matrix_f = (double**)malloc(2*sizeof(double*));
    for(int i = 0; i < 2; ++i){
        matrix_X[i] = (double*)malloc(sizeof(double));
        matrix_f_diff[i] = (double*)malloc(2*sizeof(double));
        matrix_f_diff_inv[i] = (double*)malloc(2*sizeof(double));
        matrix_f[i] = (double*)malloc(sizeof(double));
    
        matrix_X[i][0] = 0.5;
    }

    f_diff(matrix_f_diff, matrix_X[0][0], matrix_X[1][0]);
    inverse(matrix_f_diff, matrix_f_diff_inv);
    for(int i = 0; i < 2; ++i){
        free(matrix_f_diff[i]);
    }
    free(matrix_f_diff);


    double norma;
    do{        
        f(matrix_f, matrix_X[0][0], matrix_X[1][0]);
        phi(matrix_X, matrix_f_diff_inv, matrix_f);

        norma = fabs((matrix_f[0][0] > matrix_f[1][0]) ? matrix_f[0][0] : matrix_f[1][0]);
    }while(norma > epsilon);
    
    f(matrix_f, matrix_X[0][0], matrix_X[1][0]);
    printf("x = %lf\ny = %lf\n\n", matrix_X[0][0], matrix_X[1][0]);
    printf("Значение системы в точке (x,y):\n%lf\n%lf\n", matrix_f[0][0], matrix_f[1][0]);


    for(int i = 0; i < 2; ++i){
        free(matrix_X[i]);
        free(matrix_f_diff_inv[i]);
        free(matrix_f[i]);
    }
    free(matrix_X);
    free(matrix_f_diff_inv);
    free(matrix_f);
    return 0;
}
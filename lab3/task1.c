#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define epsilon 0.001

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

void phi(double **matrix, double **matrix_W_inv, double **matrix_F){
    matrix[0][0] -= matrix_W_inv[0][0]*matrix_F[0][0] +
                    matrix_W_inv[0][1]*matrix_F[1][0];
    matrix[1][0] -= matrix_W_inv[1][0]*matrix_F[0][0] +
                    matrix_W_inv[1][1]*matrix_F[1][0];
    return;
}

void F(double **f, double **x){
    f[0][0] = cos(x[0][0]+0.5) - x[1][0] - 2;
    f[1][0] = sin(x[1][0]) - 2*x[0][0] - 1;
    return;
}

void W(double **w, double **x){
    w[0][0] = -sin(x[0][0]+0.5);
    w[0][1] = -1;
    w[1][0] = -2;
    w[1][1] = cos(x[1][0]);
    return;
}


int main(){
    double **matrix_X = (double**)malloc(2*sizeof(double*));
    double **matrix_F = (double**)malloc(2*sizeof(double*));
    double **matrix_W = (double**)malloc(2*sizeof(double*));
    double **matrix_W_inv = (double**)malloc(2*sizeof(double*));
    for(int i = 0; i < 2; ++i){
        matrix_X[i] = (double*)malloc(sizeof(double));
        matrix_F[i] = (double*)malloc(sizeof(double));
        matrix_W[i] = (double*)malloc(2*sizeof(double));
        matrix_W_inv[i] = (double*)malloc(2*sizeof(double));

        matrix_X[i][0] = 0.5;
    }

    W(matrix_W, matrix_X);
    inverse(matrix_W, matrix_W_inv);
    for(int i = 0; i < 2; ++i){
        free(matrix_W[i]);
    }
    free(matrix_W);

    double norma;
    do{
        F(matrix_F, matrix_X);
        phi(matrix_X, matrix_W_inv, matrix_F);
        
        norma = fabs((matrix_F[0][0] > matrix_F[1][0]) ? matrix_F[0][0] : matrix_F[1][0]);
    }while(sqrt(norma) > epsilon);
    
    F(matrix_F, matrix_X);
    printf("x = %lf\ny = %lf\n\n", matrix_X[0][0], matrix_X[1][0]);
    printf("Значение системы в точке (x,y):\n%lf\n%lf\n", matrix_F[0][0], matrix_F[1][0]);


    for(int i = 0; i < 2; ++i){
        free(matrix_X[i]);
        free(matrix_F[i]);
        free(matrix_W_inv[i]);
    }
    free(matrix_X);
    free(matrix_F);
    free(matrix_W_inv);
    return 0;
}
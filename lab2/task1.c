#include <stdio.h>
#include <stdlib.h>
#include "matrixio.h"

int main(int argc, char **argv){
    if(argc < 2){
        fprintf(stderr, "Ошибка: не передан файл\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if(file == NULL){
        fprintf(stderr, "Ошибка: файл не открылся\n");
        return 1;
    }

    long dim = 0;
    if(read_dim(&dim, file) < 1){
        return 1;
    }
    
    double **matrix_A = (double**)malloc(dim*sizeof(double*));
    char **matrix_X = (char**)malloc(dim*sizeof(char*));
    double *matrix_B = (double*)malloc(dim*sizeof(double));

    for(long i = 0; i < dim; ++i){
        matrix_A[i] = (double*)malloc(dim*sizeof(double));
        matrix_X[i] = (char*)malloc(16*sizeof(char));
    }

    read_A_matrix(matrix_A, dim, file);
    read_X_matrix(matrix_X, dim, file);
    read_B_matrix(matrix_B, dim, file);

    fclose(file);

    printf("Matrix A:\n");
    print_A_matrix(matrix_A, dim);
    printf("\nMatrix X:\n");
    print_X_matrix(matrix_X, dim);
    printf("Matrix B:\n");
    print_B_matrix(matrix_B, dim);

    for(long i = 0; i < dim; ++i){
        free(matrix_A[i]);
        free(matrix_X[i]);
    }
    free(matrix_A);
    free(matrix_X);
    free(matrix_B);
    return 0;
}
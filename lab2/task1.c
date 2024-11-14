#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "matrix.h"

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
    double **matrix_B = (double**)malloc(dim*sizeof(double*));

    for(long i = 0; i < dim; ++i){
        matrix_A[i] = (double*)malloc(dim*sizeof(double));
        matrix_X[i] = (char*)malloc(32*sizeof(char));
        matrix_B[i] = (double*)malloc(sizeof(double));
    }

    read_matrix((void**)matrix_A, dim, QUADRATIC, file);
    read_matrix((void**)matrix_X, dim, UNKNOWN, file);
    read_matrix((void**)matrix_B, dim, VECTOR, file);

    fclose(file);


    clockid_t clockid;
    struct timespec nanotime;
    clock_getcpuclockid(getpid(), &clockid);
    double **matrix_res = kramer(matrix_A, matrix_B, dim);
    clock_gettime(clockid, &nanotime);

    printf("Время выполнения метода Крамера: %ld наносекунд\n", nanotime.tv_nsec);
    for(long i = 0; i < dim; ++i){
        printf("%s = %f\n", matrix_X[i], *matrix_res[i]);
    }


    for(long i = 0; i < dim; ++i){
        free(matrix_res[i]);
    }
    free(matrix_res);


    nanotime.tv_sec = 0;
    nanotime.tv_nsec = 0;
    clock_settime(clockid, &nanotime);
    matrix_res = seidel(matrix_A, matrix_B, dim);
    clock_gettime(clockid, &nanotime);

    printf("\nВремя выполнения метода Зейделя: %ld наносекунд\n", nanotime.tv_nsec);
    for(long i = 0; i < dim; ++i){
        printf("%s = %f\n", matrix_X[i], *matrix_res[i]);
    }
    

    for(long i = 0; i < dim; ++i){
        free(matrix_A[i]);
        free(matrix_X[i]);
        free(matrix_B[i]);
        free(matrix_res[i]);
    }
    free(matrix_A);
    free(matrix_X);
    free(matrix_B);
    free(matrix_res);
    return 0;
}
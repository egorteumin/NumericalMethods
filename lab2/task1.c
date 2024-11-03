#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int read_dim(long *dim, FILE *file){
    char str[16];
    fgets(str, 16, file);

    *dim = strtol(str, NULL, 10);
    if(*dim < 1 || *dim != strtol(strtok(str, " "), NULL, 10)){
        fprintf(stderr, "Ошибка: неккоректная размерность\n");
        return -1;
    }

    return *dim;
}

void read_A_matrix(double **matrix, const long dim, FILE *file){ 
    char *str = (char*)calloc(20*dim, sizeof(char));
    char *str_end = NULL;

    for(long i = 0; i < dim; ++i){
        fgets(str, 20*dim, file);
        str_end = str;

        for(long j = 0; j < dim; ++j){
            matrix[i][j] = strtod(str_end, &str_end);
        }
    }

    free(str);
    return;
}

void read_X_matrix(char **matrix, const long dim, FILE *file){
    char *str = (char*)calloc(16*dim, sizeof(char));
    fgets(str, 16*dim, file);

    size_t n = 0;
    for(long i = 0; i < dim; ++i){
        for(long j = 0; j < dim; ++j){
            matrix[i][j] = str[n++];
            if(str[n] == ' '){
                n++;
                break;
            }
        }
    }

    free(str);
    return;
}

void read_B_matrix(double *matrix, const long dim, FILE *file){
    char *str = (char*)calloc(20*dim, sizeof(char));
    fgets(str, 20*dim, file);
    char *str_end = str;

    for(long i = 0; i < dim; i++){
        matrix[i] = strtod(str_end, &str_end);
    }

    free(str);
    return;
}

void print_A_matrix(double **matrix, const long dim){
    for(long i = 0; i < dim; ++i){
        for(long j = 0; j < dim; ++j){
            printf("%lf ", matrix[i][j]);
            if(j == dim-1){
                printf("\n");
            }
        }
    }
    return;
}

void print_B_matrix(double *matrix, const long dim){
    for(int i = 0; i < dim; ++i){
        printf("%lf\n", matrix[i]);
    }
    return;
}

void print_X_matrix(char **matrix, const long dim){
    for(int i = 0; i < dim; ++i){
        printf("%s\n", matrix[i]);
    }
    return;
}



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
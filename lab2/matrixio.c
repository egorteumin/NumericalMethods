#include "matrixio.h"
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
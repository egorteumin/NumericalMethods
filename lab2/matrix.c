#include "matrix.h"
#include <string.h>
#include <stdlib.h>
#include <errno.h>

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


void minor(double **matrix, double** minor_matrix, const long dim_matrix, const long pos_x, const long pos_y){
    long i = 0;
    for(long x = 0; x < dim_matrix; ++x){
        if(x == pos_x){
            continue;
        }

        long j = 0;
        for(long y = 0 ; y < dim_matrix; ++y){
            if(y == pos_y){
                continue;
            }
            minor_matrix[i][j++] = matrix[x][y];
        }
        i++;
    }
    return;
}

double det(double **matrix, const long dim){
    if(dim < 1){
        errno = EINVAL;
        return 0;
    }

    switch(dim){
        case 1:
            return **matrix;
        case 2:
            return matrix[0][0]*matrix[1][1]-matrix[0][1]*matrix[1][0];
        default:
            double **minor_matrix = (double**)malloc((dim-1)*sizeof(double*));
            for(long i = 0; i < dim-1; ++i){
                minor_matrix[i] = (double*)malloc((dim-1)*sizeof(double));
            }

            double res = 0;
            for(long i = 0; i < dim; ++i){
                minor(matrix, minor_matrix, dim, 0, i);
                if(i % 2 == 0){
                    res += matrix[0][i] * det(minor_matrix, dim-1);
                }
                else{
                    res -= matrix[0][i] * det(minor_matrix, dim-1);
                }
            }

            for(long i = 0; i < dim-1; ++i){
                free(minor_matrix[i]);
            }
            free(minor_matrix);
            return res;
    }
}
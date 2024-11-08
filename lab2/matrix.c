#include "matrix.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

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

void read_matrix(void **matrix, const long dim, const Etype matrix_type, FILE *file){
    char *str = (char*)calloc(32*dim, sizeof(char));
    
    switch(matrix_type){
        case QUADRATIC:
        {
            char *str_end = NULL;
            for(long i = 0; i < dim; ++i){
                fgets(str, 32*dim, file);
                str_end = str;

                for(long j = 0; j < dim; ++j){
                    ((double*)matrix[i])[j] = strtod(str_end, &str_end);
                }
            }
            break;
        }
        case UNKNOWN:
        {
            size_t n = 0;
            fgets(str, 32*dim, file);
            for(long i = 0; i < dim; ++i){
                for(long j = 0; j < dim; ++j){
                    ((char*)matrix[i])[j] = str[n++];
                    if(str[n] == ' ' || str[n] == '\n'){
                        n++;
                        ((char*)matrix[i])[++j] = '\0';
                        break;
                    }
                }
            }
            break;
        }
        case VECTOR:
        {
            char *str_end = NULL;
            fgets(str, 32*dim, file);
            str_end = str;
            for(long i = 0; i < dim; ++i){
                *((double*)matrix[i]) = strtod(str_end, &str_end);
            }
            break;
        }
        default:
            break;
    }

    free(str);
    return;
}

void print_matrix(void **matrix, const long dim, const Etype matrix_type){
    switch(matrix_type){
        case QUADRATIC:
            for(long i = 0; i < dim; ++i){
                for(long j = 0; j < dim; ++j){
                    printf("%lf ", ((double*)matrix[i])[j]);
                    if(j == dim-1){
                        printf("\n");
                    }
                }
            }
            break;
        case UNKNOWN:
            for(long i = 0; i < dim; ++i){
                printf("%s\n", (char*)matrix[i]);
            }
            break;
        case VECTOR:
            for(long i = 0; i < dim; ++i){
                printf("%lf\n", *(double*)matrix[i]);
            }
            break;
        default:
            break;
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

void inverse(double **matrix, double **inverse_matrix, const long dim){
    double **minor_matrix = (double**)malloc((dim-1)*sizeof(double*));
    for(long i = 0; i < dim-1; ++i){
        minor_matrix[i] = (double*)malloc((dim-1)*sizeof(double));
    }

    double det_matrix = det(matrix, dim);
    for(long i = 0; i < dim; ++i){
        for(long j = 0; j < dim; ++j){
            minor(matrix, minor_matrix, dim, j, i);
            if((i+j) % 2 == 0){
                inverse_matrix[i][j] = det(minor_matrix, dim-1)/det_matrix;
            }
            else{
                inverse_matrix[i][j] = -det(minor_matrix, dim-1)/det_matrix;
            }
        }
    }

    for(long i = 0; i < dim-1; ++i){
        free(minor_matrix[i]);
    }
    free(minor_matrix);
    return;
}


double** multiplication(double **matrix_inverse, double **matrix_B, const long dim){
    double **res = (double**)calloc(dim, sizeof(double*));
    for(long i = 0; i < dim; ++i){
        res[i] = (double*)calloc(1, sizeof(double));
    }

    for(long i = 0; i < dim; ++i){
        for(long j = 0; j < dim; ++j){
            res[i][0] += matrix_inverse[i][j] * matrix_B[j][0];
        }
    }

    return res;
}


double** kramer(double **matrix_A, double **matrix_B, const long dim){
    double **inverse_matrix = (double**)malloc(dim*sizeof(double*));
    for(long i = 0; i < dim; ++i){
        inverse_matrix[i] = (double*)malloc(dim*sizeof(double));
    }

    inverse(matrix_A, inverse_matrix, dim);
    double **res = multiplication(inverse_matrix, matrix_B, dim);
   
    for(long i = 0; i < dim; ++i){
        free(inverse_matrix[i]);
    }
    free(inverse_matrix);
    return res;
}

double** seidel(double **matrix_A, double **matrix_B, const long dim){
    double d_elem = 0;
    for(long i = 0; i < dim; ++i){
        d_elem = fabs(matrix_A[i][i]);
        for(long j = 0; j < dim; ++j){
            if(i == j){
                continue;
            }

            d_elem -= fabs(matrix_A[i][j]);
            if(d_elem <= 0){
                fprintf(stderr, "Ошибка: диаганальные коэффициенты меньше чем или равны сумме модулей остальных коэффициентов\n");
                return NULL;
            }
        }
    }

    double **matrix_res = (double**)calloc(dim, sizeof(double*));
    for(long i = 0; i < dim; ++i){
        matrix_res[i] = (double*)calloc(1, sizeof(double));
    }

    double norma;
    double new = 0;
    do{
        norma = 0;
        for(long i = 0; i < dim; ++i){
            new = matrix_B[i][0] / matrix_A[i][i];
            for(long j = 0; j < dim; ++j){
                if(i == j){
                    continue;
                }
                new -= matrix_A[i][j] / matrix_A[i][i] * matrix_res[j][0];
            }
            norma += (matrix_res[i][0] - new) * (matrix_res[i][0] - new);
            matrix_res[i][0] = new;
        }
    } while(sqrt(norma) > epsilon);

    return matrix_res;
}
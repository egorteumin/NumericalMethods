#pragma once
#include <stdio.h>

typedef enum{
    QUADRATIC,
    UNKNOWN,
    VECTOR
} Etype;

int read_dim(long *dim, FILE *file);
void read_matrix(void **matrix, const long dim, const Etype matrix_type, FILE *file);
void print_matrix(void **matrix, const long dim, const Etype matrix_type);

void minor(double **matrix, double** minor_matrix, const long dim_matrix, const long pos_x, const long pos_y);
double det(double **matrix, const long dim);
void inverse(double **matrix, double **inverse_matrix, const long dim);

double** multiplication(double **matrix_inverse, double **matrix_B, const long dim);
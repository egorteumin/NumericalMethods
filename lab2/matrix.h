#pragma once
#include <stdio.h>

int read_dim(long *dim, FILE *file);
void read_A_matrix(double **matrix, const long dim, FILE *file);
void read_X_matrix(char **matrix, const long dim, FILE *file);
void read_B_matrix(double *matrix, const long dim, FILE *file);

void print_A_matrix(double **matrix, const long dim);
void print_B_matrix(double *matrix, const long dim);
void print_X_matrix(char **matrix, const long dim);

void minor(double **matrix, double** minor_matrix, const long dim_matrix, const long pos_x, const long pos_y);
double det(double **matrix, const long dim);
void inverse(double **matrix, double **inverse_matrix, const long dim);
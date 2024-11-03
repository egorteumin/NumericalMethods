#pragma once
#include <stdio.h>

int read_dim(long *dim, FILE *file);
void read_A_matrix(double **matrix, const long dim, FILE *file);
void read_X_matrix(char **matrix, const long dim, FILE *file);
void read_B_matrix(double *matrix, const long dim, FILE *file);
void print_A_matrix(double **matrix, const long dim);
void print_B_matrix(double *matrix, const long dim);
void print_X_matrix(char **matrix, const long dim);
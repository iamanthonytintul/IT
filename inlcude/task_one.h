#include <stdio.h>
#define EPS 0.000000001
#define number_of_dots 3
#define number_of_coef 3
#define size_of_dimentions 2

int find_determinant_3(double[][number_of_dots], double*);

int calculate_coefficients(double[][size_of_dimentions], double*);

int input_number(FILE*, double*);

int input_dots(FILE*, double[][size_of_dimentions]);
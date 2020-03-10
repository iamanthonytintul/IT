#include <stdio.h>
#define EPS 1e-9
#define NUMBER_OF_DOTS 3
#define NUMBER_OF_COEF 3
#define SIZE_OF_DIMENSIONS 2
enum {FALSE, TRUE};
enum {SUCCESS, ERROR};
enum {COEF_A, COEF_B, COEF_C};
enum {X_COORDINATE, Y_COORDINATE};
enum {FIRST_DOT, SECOND_DOT, THIRD_DOT};

int find_determinant(double[][NUMBER_OF_DOTS], double*);

int calculate_coefficients(double[][SIZE_OF_DIMENSIONS], double*);

int read_number(FILE *input_stream, double *inputNumber);

int read_dots(FILE*, double[][SIZE_OF_DIMENSIONS]);
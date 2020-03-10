#include "task_one.h"

int main() {
    double arr_of_coefficients[NUMBER_OF_COEF] = {0};
    double arr_of_dots[NUMBER_OF_DOTS][SIZE_OF_DIMENSIONS] = {0};
    FILE* input_stream = stdin;
    if(!read_dots(input_stream, arr_of_dots)) {
        return ERROR;
    }
    if (!calculate_coefficients(arr_of_dots, arr_of_coefficients)) {
        return ERROR;
    }
    
    return SUCCESS;
}
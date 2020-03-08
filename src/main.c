#include "../inlcude/task_one.h"
#include "stdio.h"

int main() {
    double arr_of_coefficients[number_of_coef];
    double arr_of_dots[number_of_dots][size_of_dimentions];
    FILE* inpt = stdin;
    if(input_dots(inpt, arr_of_dots)) {
        printf("Ошибка чтения. Повторите");
        return -1;
    }
    if (calculate_coefficients(arr_of_dots, arr_of_coefficients)) {
        printf("Невозможно провести через три точки квадратичную функцию\n");
    } else {
        printf("a = %lf\nb = %lf\nc = %lf\n", arr_of_coefficients[0], arr_of_coefficients[1],
               arr_of_coefficients[2]);
    }
    return 0;
}
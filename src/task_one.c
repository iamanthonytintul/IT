/*
 * Составить программу, которая по заданным
 * трем точкам на плоскости определяет коэффициенты
 * уравнения проходящей через эти точки квадратичной
 * функции. Решение оформить в виде функции,
 * принимающей на вход указатели на координаты точек.
 * Найденные коэффициенты уравнения должны быть возвращены
 * функцией через дополнительные параметры.
 * */

#include <math.h>
#include <string.h>
#include "task_one.h"

int is_negative(int read_chars, int input_char);
int set_arr_of_x_coordinates(double arr_of_x_coordinates[][NUMBER_OF_DOTS], double dots[][SIZE_OF_DIMENSIONS]);
int set_arr_of_y_coordinates(double arr_of_y_coordinates[], double dots[][SIZE_OF_DIMENSIONS]);
int change_column_to_row_of_arrays(double in_arr[][NUMBER_OF_DOTS], double out_of_arr[], int number_of_column);
int copy_array(double in_arr[][NUMBER_OF_DOTS], double out_of_arr[][NUMBER_OF_DOTS]);
int is_negative(int read_chars, int input_char);
int is_fractional(int fraction_flag, int input_char);
int is_digit(int input_char);

int find_determinant(double array[][NUMBER_OF_DOTS],
                     double *det) {    /* Поиск определителя матрицы 3*3 методом треугольника */
    if (!array)
        return FALSE;
    if (!det)
        return FALSE;
    *det += array[1][1] * (array[0][0] * array[2][2] - array[0][2] * array[2][0]);
    *det += array[0][1] * (array[2][0] * array[1][2] - array[2][2] * array[1][0]);
    *det += array[2][1] * (array[0][2] * array[1][0] - array[0][0] * array[1][2]);
    return TRUE;
}

int set_arr_of_x_coordinates(double arr_of_x_coordinates[][NUMBER_OF_DOTS], double dots[][SIZE_OF_DIMENSIONS]) {
    if (!arr_of_x_coordinates)
        return FALSE;
    if (!dots)
        return FALSE;

    for (int i = 0; i < NUMBER_OF_DOTS; ++i) {
        arr_of_x_coordinates[i][COEF_A] = dots[i][X_COORDINATE] * dots[i][X_COORDINATE];
        arr_of_x_coordinates[i][COEF_B] = dots[i][X_COORDINATE];
        arr_of_x_coordinates[i][COEF_C] = 1;
    }
    return TRUE;
}

int set_arr_of_y_coordinates(double arr_of_y_coordinates[], double dots[][SIZE_OF_DIMENSIONS]) {
    if (!arr_of_y_coordinates)
        return FALSE;
    if (!dots)
        return FALSE;
    arr_of_y_coordinates[FIRST_DOT] = dots[FIRST_DOT][Y_COORDINATE];
    arr_of_y_coordinates[SECOND_DOT] = dots[SECOND_DOT][Y_COORDINATE];
    arr_of_y_coordinates[THIRD_DOT] = dots[THIRD_DOT][Y_COORDINATE];

    return TRUE;
}

int change_column_to_row_of_arrays(double in_arr[][NUMBER_OF_DOTS],
                                   double out_of_arr[], int number_of_column) {
    if (!in_arr)
        return FALSE;
    if (!out_of_arr)
        return FALSE;

    for (int i = 0; i < NUMBER_OF_DOTS; ++i) {
        in_arr[i][number_of_column] = out_of_arr[i];
    }
    return TRUE;
}

int copy_array(double in_arr[][NUMBER_OF_DOTS], double out_of_arr[][NUMBER_OF_DOTS]) {
    if (!in_arr)
        return FALSE;
    if (!out_of_arr)
        return FALSE;

    for (int j = 0; j < NUMBER_OF_DOTS; ++j) {
        memcpy(in_arr[j], out_of_arr[j], NUMBER_OF_DOTS * sizeof(double));
    }
    return TRUE;
}

int calculate_coefficients(double dots[][SIZE_OF_DIMENSIONS], double *arr_of_coefficients) {

    if (!arr_of_coefficients)
        return FALSE;
    if (!dots)
        return FALSE;

    double arr_of_x_coordinates[NUMBER_OF_DOTS][NUMBER_OF_DOTS] = {0};
    if (!set_arr_of_x_coordinates(arr_of_x_coordinates, dots))
        return FALSE;

    double arr_of_y_coordinates[NUMBER_OF_DOTS] = {0};
    if (!set_arr_of_y_coordinates(arr_of_y_coordinates, dots))
        return FALSE;

    double det_of_init_arr_X = 0;
    if (!find_determinant(arr_of_x_coordinates, &det_of_init_arr_X))
        return FALSE;

    /* Проверка на равенство определителя нулю */
    if (fabs(det_of_init_arr_X) < EPS)
        return FALSE;

    /* Создание подсчитывающего массива */
    double arr_count[NUMBER_OF_DOTS][NUMBER_OF_DOTS] = {0};

    /* Последовательно считаем корни матричного уравнения */
    double extra_det = 0;
    for (int i = 0; i < NUMBER_OF_DOTS; ++i) {

        if (!copy_array(arr_count, arr_of_x_coordinates))
            return FALSE;
        if (!change_column_to_row_of_arrays(arr_count, arr_of_y_coordinates, i))
            return FALSE;

        extra_det = 0;
        if (!find_determinant(arr_count, &extra_det))
            return FALSE;
        arr_of_coefficients[i] = extra_det / det_of_init_arr_X;

    }
    return TRUE;
}

int is_negative(int read_chars, int input_char) {
    return (read_chars == 0 && input_char == '-');
}

int is_fractional(int fraction_flag, int input_char) {
    return (fraction_flag == 0 && input_char == '.');
}

int is_digit(int input_char) {
    return (input_char >= '0' && input_char <= '9');
}

int read_number(FILE *input_stream, double *inputNumber) {
    if (!input_stream)
        return FALSE;
    if (!inputNumber)
        return FALSE;

    int input_char = 0;
    int is_negative_number = 0;
    int is_fractional_number = 0;
    int read_correct_chars = 0;
    double real_counter = 0.1;

    while (input_char = fgetc(input_stream), input_char != ' ' && input_char != EOF && input_char != '\n') {
        if (is_negative(read_correct_chars, input_char)) {

            is_negative_number++;
            read_correct_chars++;

        } else if (is_fractional(is_fractional_number, input_char)) {

            is_fractional_number++;
            read_correct_chars++;

        } else if (!is_digit(input_char)) {

            do {
                input_char = fgetc(input_stream);
            } while (input_char != '\n' && input_char != EOF); // Вычищаем буфер
            read_correct_chars = 0;

        } else {

            if (!is_fractional_number) {

                *inputNumber = (*inputNumber) * 10 + (input_char - '0');

            } else {

                *inputNumber += (input_char - '0') * real_counter;
                real_counter *= 0.1;

            }
            read_correct_chars++;
        }
    }
    if (!read_correct_chars) {
        do {
            input_char = fgetc(input_stream);
        } while (input_char != '\n' && input_char != EOF); // Вычищаем буфер
        return FALSE;
    }
    if (is_negative_number) {
        *inputNumber = (*inputNumber) * (-1);
    }
    return TRUE;
}

int read_dots(FILE *input_stream, double arr_of_dots[][SIZE_OF_DIMENSIONS]) {
    if (!input_stream)
        return FALSE;
    if (!arr_of_dots)
        return FALSE;

    double buff = 0;
    int i = 0;

    while (i < 3) {
        printf("Введите координты точек x%d и y%d: ", i + 1, i + 1);
        buff = 0;

        if (read_number(input_stream, &buff)) {

            arr_of_dots[i][0] = buff;
            buff = 0;

            if (read_number(input_stream, &buff))
                arr_of_dots[i][1] = buff;
            else
                i--;

        } else
            i--; // Если ввод некорректен, то откатываемся на шаг назад и просим ввести снова
        i++;
    }
    return TRUE;
}
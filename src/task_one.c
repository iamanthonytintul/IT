/*
 * Составить программу, которая по заданным
 * трем точкам на плоскости определяет коэффициенты
 * уравнения проходящей через эти точки квадратичной
 * функции. Решение оформить в виде функции,
 * принимающей на вход указатели на координаты точек.
 * Найденные коэффициенты уравнения должны быть возвращены
 * функцией через дополнительные параметры.
 * */

#include <stdio.h>
#include <math.h>
#include <string.h>
#include "../inlcude/task_one.h"

int find_determinant_3(double array[][number_of_dots], double* det) {    // Поиск определителя матрицы 3*3 методом треугольника
    if(!array) return 1; // Если NULL, значит ошибка: выходим из функции
    if(!det) return 1; // Если NULL, значит ошибка: выходим из функции
    *det += array[1][1] * (array[0][0] * array[2][2] - array[0][2] * array[2][0]);
    *det += array[0][1] * (array[2][0] * array[1][2] - array[2][2] * array[1][0]);
    *det += array[2][1] * (array[0][2] * array[1][0] - array[0][0] * array[1][2]);
    return 0;
}
int calculate_coefficients(double dots[][size_of_dimentions], double *arr_of_coefficients) {

    if(!arr_of_coefficients) return 1; // Если NULL, значит ошибка: выходим из функции
    if(!dots) return 1; // Если NULL, значит ошибка: выходим из функции

    /* Транспонированная матрица значений X. В дальнейшем поможет проще заменять столбцы матрицы */
    double arr_X[number_of_dots][number_of_dots] = {{dots[0][0]*dots[0][0], dots[1][0]*dots[1][0], dots[2][0]*dots[2][0]},
                                                    {dots[0][0],         dots[1][0],         dots[2][0]},
                                                    {1,                  1,                  1}};
    /* Матрица-столбец значений Y */
    double arr_Y[number_of_dots] = {dots[0][1], dots[1][1], dots[2][1]};

    /* Поиск определителя исходной матрицы и проверки на валидность и на равенство нулю. В таком случае решения задачи нет */
    double det_of_init_arr_X;
    if(find_determinant_3(arr_X, &det_of_init_arr_X)) return 1;
    if (fabs(det_of_init_arr_X) < EPS) {
        return 1;
    }

    /* Создание подсчитывающего массива. Именно в нем мы будем заменять столбцы на arr_Y */
    double arr_count[number_of_dots][number_of_dots];
    int i;
    for (i = 0; i < number_of_dots; ++i) {
        memcpy(arr_count[i], arr_X[i], number_of_dots * sizeof(double));
    }

    /* Последовательно считаем корни матричного уравнения */
    for (i = 0; i < number_of_dots; ++i) {

        memcpy(arr_count[i], arr_Y, number_of_dots * sizeof(double));

        double extra_det = 0;
        if(find_determinant_3(arr_count, &extra_det)) return 1;
        arr_of_coefficients[i] = extra_det / det_of_init_arr_X;

        memcpy(arr_count[i], arr_X[i], number_of_dots * sizeof(double));

    }
    return 0;
}
int input_number(FILE* inpt, double *input) {
    if(!inpt) return 1;
    char c = '\0';
    int is_minus = 0;
    int is_fraction = 0;
    int read_chars = 0;
    double real_counter = 0.1;

    if(!input) {
        return 1;
    } else {
        *input = 0;
    }
    while (c = fgetc(inpt), c != ' ' && c != EOF && c != '\n') {
        /* Если символы не были прочитаны и сразу попался минус, значит число отрицательное */
        if (read_chars == 0 && c == '-') {
            is_minus++;
            continue;
        }
        /* Если первый раз встретили точку, то число дробное */
        if (c == '.' && is_fraction == 0) {
            is_fraction++;
            continue;
        }
        /* Если встретились посторонние символы, то следует повторить ввод */
        if (!(c >= '0' && c <= '9')) {
            do{c = fgetc(inpt);
            }
            while (c != '\n' && c != EOF); // Вычищаем буфер
            return 1;
        }

        /* Проверяем не началась ли дробная часть и в зависимости от этого "строим" число */
        if (!is_fraction) {
            *input = (*input) * 10 + (c - '0');
        } else if (c != '.') {
            *input += (c - '0') * real_counter;
            real_counter *= 0.1;
        }
        read_chars++;
    }
    /* Если верных символов не прочитано к данному моменту, значит следует повторить ввод */
    if (!read_chars) {
        do{c = fgetc(inpt);
        }
        while (c != '\n' && c != EOF); // Вычищаем буфер
        return 1;
    }
    if (is_minus) {
        *input = (*input) * (-1);
    }
    return !read_chars;
}

int input_dots(FILE *inpt, double arr_of_dots[][size_of_dimentions]) {
    if(!inpt) return 1;
    if (!arr_of_dots) return 1; // Если NULL, значит ошибка: выходим из функции
    double buff = 0;
    int i;
    for (i = 0; i < 3; i++) {
        printf("Введите координты точек x%d и y%d: ", i + 1, i + 1);
        if (!input_number(inpt, &buff)) { // Читаем в буфер и сразу же проверяем, был ли корректен ввод
            arr_of_dots[i][0] = buff;
            if (!input_number(inpt, &buff)) {
                arr_of_dots[i][1] = buff;
            } else {
                i--;
            }
        } else i--; // Если ввод некорректен, то откатываемся на шаг назад и просим ввести снова
    }
    return 0;
}

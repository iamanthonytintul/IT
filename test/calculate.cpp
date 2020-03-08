#include "gtest/gtest.h"

extern "C" {
#include "../inlcude/task_one.h"
}

TEST(calc, ok) {
    double arr[number_of_dots][size_of_dimentions] = {{0,  0}, {1,  1}, {-1, 1}};
    double arr_ABC[number_of_coef];
    ASSERT_EQ(calculate_coefficients(arr, arr_ABC), 0);
}

TEST(calc2, ok) {
    double arr[number_of_dots][size_of_dimentions] = {{0,  1}, {0,  0}, {0, 2}};
    double arr_ABC[number_of_coef];
    ASSERT_EQ(calculate_coefficients(arr, arr_ABC), 1);
}

TEST(calc3, ok) {
    double arr[number_of_dots][size_of_dimentions] = {{1,  1}, {1,  1}, {1, 1}};
    double arr_ABC[number_of_coef];
    ASSERT_EQ(calculate_coefficients(arr, arr_ABC), 1);
}

TEST(calc4, ok) {
    double arr[number_of_dots][size_of_dimentions] = {{4,  5}, {7,  8}, {2, 1}};
    double arr_ABC[number_of_coef];
    ASSERT_EQ(calculate_coefficients(NULL, NULL), 1);
}

TEST(calc5, ok) {
    double arr[number_of_dots][size_of_dimentions] = {{2,  234}, {1234,  1346}, {-1.23423, 1.235325}};
    double arr_ABC[number_of_coef];
    ASSERT_EQ(calculate_coefficients(arr, arr_ABC), 0);
}

TEST(calc6, ok) {
    double arr_ABC[number_of_coef];
    ASSERT_EQ(calculate_coefficients(NULL, arr_ABC), 1);
}

TEST(calc7, ok) {
    double arr[number_of_dots][size_of_dimentions] = {{2,  234}, {1234,  1346}, {-1.23423, 1.235325}};
    ASSERT_EQ(calculate_coefficients(arr, NULL), 1);
}
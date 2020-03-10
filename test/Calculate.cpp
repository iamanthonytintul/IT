#include "gtest/gtest.h"

extern "C" {
#include "task_one.h"
}

TEST(Calculation, HandlesSimpleInput) {
    double arr_of_dots[NUMBER_OF_DOTS][SIZE_OF_DIMENSIONS] = {{0, 0}, {1, 1}, {-1, 1}};
    double arr_ABC[NUMBER_OF_COEF] = {0};
    double checking = 0;
    ASSERT_EQ(calculate_coefficients(arr_of_dots, arr_ABC), TRUE);
    for(int i = 0; i < NUMBER_OF_DOTS; i++) {
        checking = arr_of_dots[i][X_COORDINATE] * arr_of_dots[i][X_COORDINATE] * arr_ABC[COEF_A] +
                   arr_of_dots[i][X_COORDINATE] * arr_ABC[COEF_B] + arr_ABC[COEF_C];
        ASSERT_FLOAT_EQ(checking, arr_of_dots[i][Y_COORDINATE]);
    }
}

TEST(Calculation, HandlesZeroDeterminanteInput) {
    double arr_of_dots[NUMBER_OF_DOTS][SIZE_OF_DIMENSIONS] = {{1, 1}, {1, 1}, {1, 1}};
    double arr_ABC[NUMBER_OF_COEF] = {0};
    ASSERT_EQ(calculate_coefficients(arr_of_dots, arr_ABC), FALSE);
}

TEST(Calculation, HandlesComplexInput) {
    double arr_of_dots[NUMBER_OF_DOTS][SIZE_OF_DIMENSIONS] = {{2, 234}, {1234, 1346}, {-1.23423, 1.235325}};
    double arr_ABC[NUMBER_OF_COEF] = {0};
    ASSERT_EQ(calculate_coefficients(arr_of_dots, arr_ABC), TRUE);
    double checking = 0;
    for(int i = 0; i < NUMBER_OF_DOTS; i++) {
        checking = arr_of_dots[i][0] * arr_of_dots[i][0] * arr_ABC[COEF_A] +
                   arr_of_dots[i][0] * arr_ABC[COEF_B] + arr_ABC[COEF_C];
        ASSERT_FLOAT_EQ(checking, arr_of_dots[i][1]);
    }
}

TEST(Calculation, HandlesNullInputOfDotsArray) {
    double arr_ABC[NUMBER_OF_COEF] = {0};
    ASSERT_EQ(calculate_coefficients(NULL, arr_ABC), FALSE);
}

TEST(Calculation, HandlesNullInputOfResultArray) {
    double arr_of_dots[NUMBER_OF_DOTS][SIZE_OF_DIMENSIONS] = {{2, 234}, {1234, 1346}, {-1.23423, 1.235325}};
    ASSERT_EQ(calculate_coefficients(arr_of_dots, NULL), FALSE);
}
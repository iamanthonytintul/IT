#include "gtest/gtest.h"

extern "C" {
#include "task_one.h"
}

TEST(FindDeterminant, HandlesSimpleArray) {
    double arr[NUMBER_OF_DOTS][NUMBER_OF_DOTS] = {{2, 0, 1}, {1, 1, 1}, {4, -1, 1}};
    double det = 0;
    const double ACTUAL_VALUE = -1;
    EXPECT_EQ(find_determinant(arr, &det), TRUE);
    EXPECT_EQ(ACTUAL_VALUE, det);
}
TEST(FindDeterminant, HandlesNullArray) {
    double det = 0;
    EXPECT_EQ(find_determinant(NULL, &det), FALSE);
}
TEST(FindDeterminant, HandlesNullValue) {
    double arr[NUMBER_OF_DOTS][NUMBER_OF_DOTS] = {{2, 0, 1}, {1, 1, 1}, {4, -1, 1}};
    EXPECT_EQ(find_determinant(arr, NULL), FALSE);
}
TEST(FindDeterminant, HandlesNullInput) {
    EXPECT_EQ(find_determinant(NULL, NULL), FALSE);
}
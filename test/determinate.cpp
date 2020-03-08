#include "gtest/gtest.h"

extern "C" {
#include "../inlcude/task_one.h"
}

TEST(det1, ok) {
    double arr[number_of_dots][number_of_dots] = {{2, 0, 1}, {1, 1, 1}, {4, -1, 1}};
    double val = 0;
    ASSERT_EQ(find_determinant_3(arr, &val), 0);
}
TEST(det2, ok) {
    double val = 0;
    ASSERT_EQ(find_determinant_3(NULL, &val), 1);
}
TEST(det3, ok) {
    double arr[number_of_dots][number_of_dots] = {{2, 0, 1}, {1, 1, 1}, {4, -1, 1}};
    ASSERT_EQ(find_determinant_3(arr, NULL), 1);
}
TEST(det4, ok) {
    ASSERT_EQ(find_determinant_3(NULL, NULL), 1);
}
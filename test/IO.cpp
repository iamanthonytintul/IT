#include "gtest/gtest.h"

extern "C" {
#include "../inlcude/task_one.h"
}
FILE *ioTest;
TEST(io1, ok) {
    ioTest = fopen("../../test/inputTest/IO/test1", "r");
    double num = 0;
    ASSERT_EQ(input_number(ioTest, &num), 0);
    ASSERT_LT(num - 1234, EPS);
    fclose(ioTest);
}

TEST(io2, ok) {
    ioTest = fopen("../../test/inputTest/IO/test2", "r");
    double num = 0;
    ASSERT_EQ(input_number(ioTest, &num), 1);
    fclose(ioTest);
}

TEST(io3, ok) {
    ioTest = fopen("../../test/inputTest/IO/test3", "r");
    double num = 0;
    ASSERT_EQ(input_number(ioTest, &num), 0);
    ASSERT_LT(num - 14.1234325325, EPS);
    fclose(ioTest);
}

TEST(io4, ok) {
    ioTest = fopen("../../test/inputTest/IO/test4", "r");
    double num = 0;
    ASSERT_EQ(input_number(ioTest, &num), 1);
    fclose(ioTest);
}

TEST(io5, ok) {
    ioTest = fopen("../../test/inputTest/IO/test5", "r");
    double num = 0;
    ASSERT_EQ(input_number(ioTest, &num), 0);
    ASSERT_LT(num+12342342352, EPS);
    fclose(ioTest);
}

TEST(io6, ok) {
    ioTest = fopen("../../test/inputTest/IO/test6", "r");
    double num = 0;
    ASSERT_EQ(input_number(ioTest, &num), 1);
    fclose(ioTest);
}

TEST(io7, ok) {
    double num = 0;
    ASSERT_EQ(input_number(NULL, &num), 1);
}
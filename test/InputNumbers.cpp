#include "gtest/gtest.h"

extern "C" {
#include "task_one.h"
}

TEST(InputNumberTest, HandlesIntegerInput) {
    FILE* ioTest;
    double num = 0;
    ioTest = fopen(PATH_TO_IO_TEST_INTEGER, "r");
    const double ACTUAL_VALUE = 1234.0;
    EXPECT_EQ(read_number(ioTest, &num), TRUE);
    EXPECT_FLOAT_EQ(num, ACTUAL_VALUE);
    fclose(ioTest);
}

TEST(InputNumberTest, HandlesWrongInput) {
    FILE* ioTest;
    double num = 0;
    ioTest = fopen(PATH_TO_IO_TEST_WRONG, "r");
    EXPECT_EQ(read_number(ioTest, &num), FALSE);
    fclose(ioTest);
}

TEST(InputNumberTest, HandlesDoubleInput) {
    FILE* ioTest;
    double num = 0;
    ioTest = fopen(PATH_TO_IO_TEST_DOUBLE, "r");
    const double ACTUAL_VALUE = 14.1234325325;
    EXPECT_EQ(read_number(ioTest, &num), TRUE);
    EXPECT_FLOAT_EQ(num, ACTUAL_VALUE);
    fclose(ioTest);
}

TEST(InputNumberTest, HandlesFirstSpaceInput) {
    FILE* ioTest;
    double num = 0;
    ioTest = fopen(PATH_TO_IO_TEST_SPACE, "r");
    EXPECT_EQ(read_number(ioTest, &num), FALSE);
    fclose(ioTest);
}

TEST(InputNumberTest, HandlesNegativeNumberInput) {
    FILE* ioTest;
    double num = 0;
    ioTest = fopen(PATH_TO_IO_TEST_NEGATIVE, "r");
    const double ACTUAL_VALUE = -12342342352.0;
    EXPECT_EQ(read_number(ioTest, &num), TRUE);
    EXPECT_FLOAT_EQ(num, ACTUAL_VALUE);
    fclose(ioTest);
}

TEST(InputNumberTest, HandlesNullFileInput) {
    double num = 0;
    EXPECT_EQ(read_number(NULL, &num), FALSE);
}
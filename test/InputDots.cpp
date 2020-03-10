#include "gtest/gtest.h"

extern "C" {
    #include "task_one.h"
}

TEST(InputDotsTest, HandlesIntegerInput) {
    FILE *ioDotsTest;
    ioDotsTest = fopen(PATH_TO_IO_DOTS_TEST_INTEGER, "r");
    double num[NUMBER_OF_DOTS][SIZE_OF_DIMENSIONS] = {0};
    EXPECT_EQ(read_dots(ioDotsTest, num), TRUE);
    fclose(ioDotsTest);
}

TEST(InputDotsTest, HandlesDoubleInput) {
    FILE *ioDotsTest;
    ioDotsTest = fopen(PATH_TO_IO_DOTS_TEST_DOUBLE, "r");
    double num[NUMBER_OF_DOTS][SIZE_OF_DIMENSIONS] = {0};
    EXPECT_EQ(read_dots(ioDotsTest, num), TRUE);
    fclose(ioDotsTest);
}

TEST(InputDotsTest, HandlesWrongInput) {
    FILE *ioDotsTest;
    ioDotsTest = fopen(PATH_TO_IO_DOTS_TEST_WRONG, "r");
    double num[NUMBER_OF_DOTS][SIZE_OF_DIMENSIONS] = {0};
    EXPECT_EQ(read_dots(ioDotsTest, num), TRUE);
    fclose(ioDotsTest);
}

TEST(InputDotsTest, HandlesNullInput) {
    FILE *ioDotsTest;
    ioDotsTest = fopen(PATH_TO_IO_DOTS_TEST_NULL, "r");
    EXPECT_EQ(read_dots(ioDotsTest, NULL), FALSE);
    fclose(ioDotsTest);
}
TEST(InputDotsTest, HandlesNoFileInput) {
    double num[NUMBER_OF_DOTS][SIZE_OF_DIMENSIONS] = {0};
    EXPECT_EQ(read_dots(NULL, num), FALSE);
}

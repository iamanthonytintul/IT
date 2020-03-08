#include "gtest/gtest.h"

extern "C" {
    #include "../inlcude/task_one.h"
}

FILE *ioDotsTest;

TEST(ioDots1, ok) {
    ioDotsTest = fopen("../../test/inputTest/IODots/test1", "r");
    double num[number_of_dots][size_of_dimentions];
    ASSERT_EQ(input_dots(ioDotsTest, num), 0);
    fclose(ioDotsTest);
}

TEST(ioDots2, ok) {
    ioDotsTest = fopen("../../test/inputTest/IODots/test2", "r");
    double num[number_of_dots][size_of_dimentions];
    ASSERT_EQ(input_dots(ioDotsTest, num), 0);
    fclose(ioDotsTest);
}

TEST(ioDots3, ok) {
    ioDotsTest = fopen("../../test/inputTest/IODots/test3", "r");
    double num[number_of_dots][size_of_dimentions];
    ASSERT_EQ(input_dots(ioDotsTest, num), 0);
    fclose(ioDotsTest);
}

TEST(ioDots4, ok) {
    ioDotsTest = fopen("../../test/inputTest/IODots/test4", "r");
    double num[number_of_dots][size_of_dimentions];
    ASSERT_EQ(input_dots(ioDotsTest, num), 0);
    fclose(ioDotsTest);
}

TEST(ioDots5, ok) {
    ioDotsTest = fopen("../../test/inputTest/IODots/test5", "r");
    ASSERT_EQ(input_dots(ioDotsTest, NULL), 1);
    fclose(ioDotsTest);
}
TEST(ioDots6, ok) {
    double num[number_of_dots][size_of_dimentions];
    ASSERT_EQ(input_dots(NULL, num), 1);
}

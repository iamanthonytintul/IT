#include "gtest/gtest.h"

extern "C" {
#include "employee_DB.h"
}

TEST(FillStructure, HandlesRegularCase) {

    FILE *input_stream = fopen(PATH_INPUT_REGULAR_CASE, "r");

    EXPECT_TRUE(input_stream != NULL);

    int capacity_of_employees = read_number(input_stream);
    employee_info **emp = read_employees(input_stream, capacity_of_employees);
    EXPECT_TRUE(emp != NULL);

    int amount_of_positions = 0;
    char** unique_position = find_unique_positions(emp, capacity_of_employees, &amount_of_positions);
    for (int i = 0; i < amount_of_positions; ++i) {
        mark_position_as_checked(emp, capacity_of_employees, unique_position[i]);
    }

    for (int i = 0; i < capacity_of_employees; ++i) {
        EXPECT_EQ(emp[i]->is_checked, TRUE);
    }

    free(unique_position);
    free_employees(emp, capacity_of_employees);
    fclose(input_stream);
}
TEST(FillStructure, HandlesInvalidCase) {
    FILE *input_stream = fopen(PATH_INPUT_INVALID_CASE, "r");

    EXPECT_TRUE(input_stream != NULL);

    int capacity_of_employees = read_number(input_stream);
    employee_info **emp = read_employees(input_stream, capacity_of_employees);
    EXPECT_TRUE(emp == NULL);

    fclose(input_stream);
}

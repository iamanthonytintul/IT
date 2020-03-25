#include "gtest/gtest.h"

extern "C" {

#include "static_employee_DB.h"
#include "count_time.h"
#include <dlfcn.h>
}

class Functional {

public:
    void *library;

    boolean (*print_the_most_aged_employees_in_each_position_dyn)(FILE *input_stream, employee_info **emp,
                                                                  int capacity_of_emp);
};

class Functional_test : public ::testing::Test {
protected:
    void SetUp() {
        dyn_lib.library = dlopen(PATH_TO_DYNAMIC_LIB, RTLD_LAZY);
        *(void **) (&dyn_lib.print_the_most_aged_employees_in_each_position_dyn) =
                dlsym(dyn_lib.library, "print_the_most_aged_employees_in_each_position_dyn");

    }

    void TearDown() {
        dlclose(dyn_lib.library);
    }

    Functional dyn_lib{};
};


TEST_F(Functional_test, HandlesFirstRegularCase) {

    FILE *input_stream = fopen(PATH_FUNCTIONAL_INPUT_FIRST_REGULAR_CASE, "r");
    FILE *output_static_stream = fopen(PATH_FUNCTIONAL_OUTPUT_STATIC_LIB, "w+");
    FILE *output_dynamic_stream = fopen(PATH_FUNCTIONAL_OUTPUT_DYNAMIC_LIB, "w+");

    EXPECT_TRUE(input_stream != NULL);
    EXPECT_TRUE(output_static_stream != NULL);
    EXPECT_TRUE(output_dynamic_stream != NULL);

    int capacity_of_employees = read_number(input_stream);
    if (capacity_of_employees != FAILURE) {
        employee_info **employees = read_employees(input_stream, capacity_of_employees);

        //if (employees) {
            sort_by_surname(employees, capacity_of_employees);
            dyn_lib.print_the_most_aged_employees_in_each_position_dyn(output_dynamic_stream, employees,
                                                                       capacity_of_employees);
        //}
        free_employees(employees, capacity_of_employees);
    }

    rewind(input_stream);
    capacity_of_employees = read_number(input_stream);
    if (capacity_of_employees != FAILURE) {
        employee_info **employees = read_employees(input_stream, capacity_of_employees);

        if (employees) {
            sort_by_surname(employees, capacity_of_employees);
            print_the_most_aged_employees_in_each_position_static(output_static_stream, employees,
                                                                  capacity_of_employees);
        }
        free_employees(employees, capacity_of_employees);
    }

    rewind(output_static_stream);
    rewind(output_dynamic_stream);

    int char_output_static = 0;
    int char_output_dynamic = 0;
    while (char_output_static != EOF || char_output_dynamic != EOF) {
        char_output_static = fgetc(output_static_stream);
        char_output_dynamic = fgetc(output_dynamic_stream);
        EXPECT_EQ(char_output_static, char_output_dynamic);
    }

    fclose(input_stream);
    fclose(output_dynamic_stream);
    fclose(output_static_stream);
}

TEST_F(Functional_test, HandlesSecondRegularCase) {

    FILE *input_stream = fopen(PATH_FUNCTIONAL_INPUT_SECOND_REGULAR_CASE, "r");
    FILE *output_static_stream = fopen(PATH_FUNCTIONAL_OUTPUT_STATIC_LIB, "w+");
    FILE *output_dynamic_stream = fopen(PATH_FUNCTIONAL_OUTPUT_DYNAMIC_LIB, "w+");

    EXPECT_TRUE(input_stream != NULL);
    EXPECT_TRUE(output_static_stream != NULL);
    EXPECT_TRUE(output_dynamic_stream != NULL);

    int capacity_of_employees = read_number(input_stream);
    if (capacity_of_employees != FAILURE) {
        employee_info **employees = read_employees(input_stream, capacity_of_employees);

        if (employees) {
            sort_by_surname(employees, capacity_of_employees);
            print_the_most_aged_employees_in_each_position_static(output_static_stream, employees,
                                                                  capacity_of_employees);
        }
        free_employees(employees, capacity_of_employees);
    }

    rewind(input_stream);

    capacity_of_employees = read_number(input_stream);
    if (capacity_of_employees != FAILURE) {
        employee_info **employees = read_employees(input_stream, capacity_of_employees);

        if (employees) {
            sort_by_surname(employees, capacity_of_employees);
            dyn_lib.print_the_most_aged_employees_in_each_position_dyn(output_dynamic_stream, employees,
                                                                       capacity_of_employees);
        }
        free_employees(employees, capacity_of_employees);
    }

    rewind(output_static_stream);
    rewind(output_dynamic_stream);

    int char_output_static = 0;
    int char_output_dynamic = 0;
    while (char_output_static != EOF || char_output_dynamic != EOF) {
        char_output_static = fgetc(output_static_stream);
        char_output_dynamic = fgetc(output_dynamic_stream);
        EXPECT_EQ(char_output_static, char_output_dynamic);
    }

    fclose(input_stream);
    fclose(output_dynamic_stream);
    fclose(output_static_stream);
}


#include "gtest/gtest.h"

extern "C" {

#include <dlfcn.h>
#include "static_employee_DB.h"
#include "count_time.h"

}

class Functional {

public:
    void *library;

    boolean
    (*get_youngest_oldest_employees_in_positions_dynamic)(employee_info **emp, int capacity_of_emp,
                                                          char **unique_positions, int amount_of_positions);
};

class Functional_test : public ::testing::Test {
protected:
    void SetUp() {
        dyn_lib.library = dlopen(PATH_TO_DYNAMIC_LIB, RTLD_LAZY);
        *(void **) (&dyn_lib.get_youngest_oldest_employees_in_positions_dynamic) =
                dlsym(dyn_lib.library, "get_youngest_oldest_employees_in_positions_dynamic");

    }

    void TearDown() {
        dlclose(dyn_lib.library);
    }

    Functional dyn_lib{};
};


TEST_F(Functional_test, HandlesFirstRegularCase) {

    FILE *input_stream = fopen(PATH_FUNCTIONAL_INPUT_FIRST_REGULAR_CASE, "r");
    EXPECT_TRUE(input_stream != NULL);
    FILE *output_static_stream = fopen(PATH_FUNCTIONAL_OUTPUT_STATIC_LIB, "w+");
    EXPECT_TRUE(output_static_stream != NULL);
    FILE *output_dynamic_stream = fopen(PATH_FUNCTIONAL_OUTPUT_DYNAMIC_LIB, "w+");
    EXPECT_TRUE(output_dynamic_stream != NULL);

    int capacity_of_employees = read_number(input_stream);
    if (capacity_of_employees != FAILURE) {
        employee_info **employees = read_employees(input_stream, capacity_of_employees);
        EXPECT_TRUE(employees != NULL);

        int amount_of_positions = 0;
        char **unique_positions = find_unique_positions(employees, capacity_of_employees, &amount_of_positions);
        EXPECT_TRUE(unique_positions != NULL);

        sort_by_surname(employees, capacity_of_employees);

        get_the_youngest_in_positions_static(employees, capacity_of_employees, unique_positions, amount_of_positions);
        get_the_oldest_in_positions_static(employees, capacity_of_employees, unique_positions, amount_of_positions);

        print_employees_in_age(output_static_stream, employees, capacity_of_employees, unique_positions,
                               amount_of_positions, YOUNG);
        print_employees_in_age(output_static_stream, employees, capacity_of_employees, unique_positions,
                               amount_of_positions, OLD);

        free(unique_positions);
        free_employees(employees, capacity_of_employees);
    }

    rewind(input_stream);

    capacity_of_employees = read_number(input_stream);
    if (capacity_of_employees != FAILURE) {
        employee_info **employees = read_employees(input_stream, capacity_of_employees);
        EXPECT_TRUE(employees != NULL);

        int amount_of_positions = 0;
        char **unique_positions = find_unique_positions(employees, capacity_of_employees, &amount_of_positions);
        EXPECT_TRUE(unique_positions != NULL);

        sort_by_surname(employees, capacity_of_employees);

        dyn_lib.get_youngest_oldest_employees_in_positions_dynamic(employees, capacity_of_employees,
                                                                   unique_positions, amount_of_positions);

        print_employees_in_age(output_dynamic_stream, employees, capacity_of_employees, unique_positions,
                               amount_of_positions,
                               YOUNG);
        print_employees_in_age(output_dynamic_stream, employees, capacity_of_employees, unique_positions,
                               amount_of_positions,
                               OLD);

        free(unique_positions);
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
        EXPECT_TRUE(employees != NULL);

        int amount_of_positions = 0;
        char **unique_positions = find_unique_positions(employees, capacity_of_employees, &amount_of_positions);
        EXPECT_TRUE(unique_positions != NULL);

        sort_by_surname(employees, capacity_of_employees);

        get_the_youngest_in_positions_static(employees, capacity_of_employees, unique_positions, amount_of_positions);
        get_the_oldest_in_positions_static(employees, capacity_of_employees, unique_positions, amount_of_positions);

        print_employees_in_age(output_static_stream, employees, capacity_of_employees, unique_positions,
                               amount_of_positions, YOUNG);
        print_employees_in_age(output_static_stream, employees, capacity_of_employees, unique_positions,
                               amount_of_positions, OLD);

        free(unique_positions);
        free_employees(employees, capacity_of_employees);
    }

    rewind(input_stream);

    capacity_of_employees = read_number(input_stream);
    if (capacity_of_employees != FAILURE) {
        employee_info **employees = read_employees(input_stream, capacity_of_employees);
        EXPECT_TRUE(employees != NULL);

        int amount_of_positions = 0;
        char **unique_positions = find_unique_positions(employees, capacity_of_employees, &amount_of_positions);
        EXPECT_TRUE(unique_positions != NULL);

        sort_by_surname(employees, capacity_of_employees);

        dyn_lib.get_youngest_oldest_employees_in_positions_dynamic(employees, capacity_of_employees,
                                                                   unique_positions, amount_of_positions);

        print_employees_in_age(output_dynamic_stream, employees, capacity_of_employees, unique_positions,
                               amount_of_positions,
                               YOUNG);
        print_employees_in_age(output_dynamic_stream, employees, capacity_of_employees, unique_positions,
                               amount_of_positions,
                               OLD);

        free(unique_positions);
        free_employees(employees, capacity_of_employees);
    }

    rewind(output_static_stream);
    rewind(output_dynamic_stream);

    int char_output_static = 0;
    int char_output_dynamic = 0;
    while (char_output_static != EOF || char_output_dynamic != EOF) {
        char_output_static = fgetc(output_static_stream);
        char_output_dynamic = fgetc(output_dynamic_stream);
        if (char_output_dynamic != char_output_static) { ;
        }
        EXPECT_EQ(char_output_static, char_output_dynamic);
    }

    fclose(input_stream);
    fclose(output_dynamic_stream);
    fclose(output_static_stream);
}
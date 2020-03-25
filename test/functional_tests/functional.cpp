#include "gtest/gtest.h"

extern "C" {

#include <dlfcn.h>
#include "static_employee_DB.h"
#include "count_time.h"

}
class Functional {

public:
    void *library;

    int (*read_number)(FILE *input_stream);

    employee_info **(*read_employees)(FILE *input_stream, int capacity_of_emp);

    boolean (*sort_by_surname)(employee_info **emp, int capacity_of_emp);

    boolean (*print_the_most_aged_employees_in_each_position_dyn)(FILE *output_stream, employee_info **emp, int capacity_of_emp);

    boolean (*free_employees)(employee_info **emp, int capacity_of_emp);
};

class Functional_test : public ::testing::Test {
protected:
    void SetUp() {
        dyn_lib = new Functional();
        dyn_lib->library = dlopen(PATH_TO_DYNAMIC_LIB, RTLD_LAZY);
        *(void **) (&dyn_lib->read_number) = dlsym(dyn_lib->library, "read_number");
        *(void **) (&dyn_lib->read_employees) = dlsym(dyn_lib->library, "read_employees");
        *(void **) (&dyn_lib->sort_by_surname) = dlsym(dyn_lib->library, "sort_by_surname");
        *(void **) (&dyn_lib->print_the_most_aged_employees_in_each_position_dyn) =
                dlsym(dyn_lib->library, "print_the_most_aged_employees_in_each_position_dyn");
        *(void **) (&dyn_lib->free_employees) = dlsym(dyn_lib->library, "free_employees");

    }

    void TearDown() {
        dlclose(dyn_lib->library);
        delete dyn_lib;
    }

    Functional *dyn_lib;
};


TEST_F(Functional_test, HandlesFirstRegularCase) {

    FILE *input_stream = fopen(PATH_FUNCTIONAL_INPUT_FIRST_REGULAR_CASE, "r");
    FILE *output_static_stream = fopen(PATH_FUNCTIONAL_OUTPUT_STATIC_LIB, "w+");
    FILE *output_dynamic_stream = fopen(PATH_FUNCTIONAL_OUTPUT_DYNAMIC_LIB, "w+");

    EXPECT_TRUE(input_stream != NULL);
    EXPECT_TRUE(output_static_stream != NULL);
    EXPECT_TRUE(output_dynamic_stream != NULL);

    int capacity_of_employees = dyn_lib->read_number(input_stream);
    if (capacity_of_employees != FAILURE) {
        employee_info **employees = dyn_lib->read_employees(input_stream, capacity_of_employees);

        if (employees) {
            dyn_lib->sort_by_surname(employees, capacity_of_employees);
            dyn_lib->print_the_most_aged_employees_in_each_position_dyn(output_dynamic_stream, employees, capacity_of_employees);
        }
        dyn_lib->free_employees(employees, capacity_of_employees);
    }

    rewind(input_stream);
    /*int capacity_of_employees = read_number(input_stream);
    if (capacity_of_employees != FAILURE) {
        employee_info **employees = read_employees(input_stream, capacity_of_employees);

        if (employees) {
            sort_by_surname(employees, capacity_of_employees);
            print_the_most_aged_employees_in_each_position_static(output_static_stream, employees, capacity_of_employees);
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
    }*/

    fclose(input_stream);
    fclose(output_dynamic_stream);
    fclose(output_static_stream);
}

/*TEST_F(Functional_test, HandlesSecondRegularCase) {

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

    capacity_of_employees = dyn_lib->read_number(input_stream);
    if (capacity_of_employees != FAILURE) {
        employee_info **employees = dyn_lib->read_employees(input_stream, capacity_of_employees);

        if (employees) {
            dyn_lib->sort_by_surname(employees, capacity_of_employees);
          //  dyn_lib->print_the_most_aged_employees_in_each_position_dyn(output_dynamic_stream, employees, capacity_of_employees);
        }
        dyn_lib->free_employees(employees, capacity_of_employees);
    }

    rewind(output_static_stream);
    rewind(output_dynamic_stream);

    int char_output_static = 0;
    int char_output_dynamic = 0;
    while (char_output_static != EOF || char_output_dynamic != EOF){
        char_output_static = fgetc(output_static_stream);
        char_output_dynamic = fgetc(output_dynamic_stream);
        EXPECT_EQ(char_output_static, char_output_dynamic);
    }

    fclose(input_stream);
    fclose(output_dynamic_stream);
    fclose(output_static_stream);
}
*/


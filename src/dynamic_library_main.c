#include "employee_types.h"
#include "count_time.h"

#include <dlfcn.h>

#define LIBRARY_ERR 1

int main() {

    void *library = dlopen(PATH_TO_DYNAMIC_LIB, RTLD_LAZY);
    if (!library) {
        return LIBRARY_ERR;
    }

    int (*read_number)(FILE *input_stream) = NULL;
    employee_info **(*read_employees)(FILE *input_stream, int capacity_of_emp) = NULL;
    boolean (*sort_by_surname)(employee_info **emp, int capacity_of_emp) = NULL;
    boolean (*print_the_most_aged_employees_in_each_position_dyn)(FILE *input_stream, employee_info **emp,
                                                            int capacity_of_emp) = NULL;
    boolean (*free_employees)(employee_info **emp, int capacity_of_emp) = NULL;

    *(void **) (&read_number) = dlsym(library, "read_number");
    if(!read_number) {
        return LIBRARY_ERR;
    }
    *(void **) (&read_employees) = dlsym(library, "read_employees");
    if(!read_employees) {
        return LIBRARY_ERR;
    }
    *(void **) (&sort_by_surname) = dlsym(library, "sort_by_surname");
    if(!sort_by_surname) {
        return LIBRARY_ERR;
    }
    *(void **) (&print_the_most_aged_employees_in_each_position_dyn) =
            dlsym(library,"print_the_most_aged_employees_in_each_position");
    if(!print_the_most_aged_employees_in_each_position_dyn) {
        return LIBRARY_ERR;
    }
    *(void **) (&free_employees) = dlsym(library, "free_employees");
    if(!free_employees) {
        return LIBRARY_ERR;
    }

    FILE *input_stream = stdin;
    FILE *output_stream = stdout;


    long start = pinpoint_time();

    int capacity_of_employees = read_number(input_stream);
    if (capacity_of_employees != FAILURE) {
        employee_info **employees = read_employees(input_stream, capacity_of_employees);

        if (employees) {
            sort_by_surname(employees, capacity_of_employees);
            print_the_most_aged_employees_in_each_position_dyn(output_stream, employees, capacity_of_employees);
        }
        free_employees(employees, capacity_of_employees);
    }

    long end = pinpoint_time();

    printf("Working time takes: %ld ms\n", end - start);

    dlclose(library);

    return 0;
}

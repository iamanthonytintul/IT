#include <stdio.h>
#include "static_employee_DB.h"
#include "count_time.h"

int main() {

    FILE *input_stream = stdin;
    FILE *output_stream = stdout;

    long start = pinpoint_time();

    int capacity_of_employees = read_number(input_stream);
    if (capacity_of_employees != FAILURE) {
        employee_info **employees = read_employees(input_stream, capacity_of_employees);

        if (employees) {
            sort_by_surname(employees, capacity_of_employees);
            print_the_most_aged_employees_in_each_position_static(output_stream, employees, capacity_of_employees);
        }
        free_employees(employees, capacity_of_employees);
    }

    long end = pinpoint_time();

    printf("Working time takes: %ld ms\n", end - start);

    return 0;
}

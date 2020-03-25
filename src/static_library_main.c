#include <stdio.h>
#include "static_employee_DB.h"
#include "count_time.h"

int main() {

    FILE *input_stream = stdin;
    FILE *output_stream = stdout;

    long timer_start = 0, timer_end = 0;
    timer_start = pinpoint_time();

    int capacity_of_employees = read_number(input_stream);
    if (capacity_of_employees != FAILURE) {
        employee_info **employees = read_employees(input_stream, capacity_of_employees);

        if (!employees) {
            fclose(input_stream);
            fclose(output_stream);
            return FAILURE;
        }

        int amount_of_positions = 0;
        char **unique_positions = find_unique_positions(employees, capacity_of_employees, &amount_of_positions);

        if (!unique_positions) {
            free_employees(employees, capacity_of_employees);
            fclose(input_stream);
            fclose(output_stream);
            return FAILURE;
        }

        sort_by_surname(employees, capacity_of_employees);

        get_the_youngest_in_positions_static(employees, capacity_of_employees, unique_positions, amount_of_positions);
        get_the_oldest_in_positions_static(employees, capacity_of_employees, unique_positions, amount_of_positions);

        timer_end = pinpoint_time();

        print_employees_in_age(output_stream, employees, capacity_of_employees, unique_positions, amount_of_positions,
                               YOUNG);
        print_employees_in_age(output_stream, employees, capacity_of_employees, unique_positions, amount_of_positions,
                               OLD);

        free(unique_positions);
        free_employees(employees, capacity_of_employees);
    }

    printf("Static library takes: %ld ms\n", timer_end - timer_start);

    return 0;
}

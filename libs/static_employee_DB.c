#include "static_employee_DB.h"

boolean print_the_most_aged_employees_in_each_position_static(FILE *output_stream, employee_info **emp, int capacity_of_emp) {

    int amount_of_positions = 0;
    char **unique_positions = find_unique_positions(emp, capacity_of_emp, &amount_of_positions);

    if (!unique_positions) {
        return FALSE;
    }
    mark_all_as_unchecked(emp, capacity_of_emp);
    get_the_youngest_in_positions_static(output_stream, emp, capacity_of_emp, unique_positions,
                                  amount_of_positions);
    print_employees_in_age(output_stream, emp, capacity_of_emp, unique_positions, amount_of_positions, "YOUNG");

    mark_all_as_unchecked(emp, capacity_of_emp);
    get_the_oldest_in_positions_static(output_stream, emp, capacity_of_emp, unique_positions,
                                            amount_of_positions);
    print_employees_in_age(output_stream, emp, capacity_of_emp, unique_positions, amount_of_positions, "OLD");


    free(unique_positions);
    return TRUE;
}

int get_the_youngest_in_positions_static(FILE *output_stream, employee_info **emp, int capacity_of_emp,
                                  char **unique_positions, int amount_of_unique_positions) {

    if (!output_stream || !emp || !unique_positions) {
        return FALSE;
    }

    int min_age = INITIAL_VALUE;
    for (int i = 0; i < amount_of_unique_positions; i++) {

        for (int j = 0; j < capacity_of_emp; j++) {
            if (strcmp(emp[j]->position, unique_positions[i]) == EQ_STR &&
                (emp[j]->age < min_age || min_age == INITIAL_VALUE)) {
                min_age = emp[j]->age;
            }

        }

        for (int j = 0; j < capacity_of_emp; j++) {
            if (strcmp(emp[j]->position, unique_positions[i]) == EQ_STR &&
                emp[j]->age == min_age) {

                emp[j]->is_checked = TRUE;


            }
        }
        min_age = INITIAL_VALUE;

    }

    return TRUE;
}

int get_the_oldest_in_positions_static(FILE *output_stream, employee_info **emp, int capacity_of_emp,
                                char **unique_positions, int amount_of_unique_positions) {

    if (!output_stream || !emp || !unique_positions) {
        return FALSE;
    }

    int max_age = INITIAL_VALUE;
    for (int i = 0; i < amount_of_unique_positions; i++) {

        for (int j = 0; j < capacity_of_emp; j++) {
            if (strcmp(emp[j]->position, unique_positions[i]) == EQ_STR &&
                (emp[j]->age > max_age || max_age == INITIAL_VALUE)) {
                max_age = emp[j]->age;
            }

        }
        for (int j = 0; j < capacity_of_emp; j++) {
            if (strcmp(emp[j]->position, unique_positions[i]) == EQ_STR &&
                emp[j]->age == max_age) {

                emp[j]->is_checked = TRUE;

            }
        }
        max_age = INITIAL_VALUE;
    }

    return TRUE;
}

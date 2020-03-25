#include "static_employee_DB.h"

int get_the_youngest_in_positions_static(employee_info **emp, int capacity_of_emp,
                                         char **unique_positions, int amount_of_unique_positions) {

    if (!emp || !unique_positions) {
        return FALSE;
    }

    mark_all_as_unchecked(emp, capacity_of_emp);

    for (int i = 0; i < amount_of_unique_positions; i++) {
        int min_age = INITIAL_VALUE;
        for (int j = 0; j < capacity_of_emp; j++) {
            if (strcmp(emp[j]->position, unique_positions[i]) == EQ_STR &&
                (emp[j]->age < min_age || min_age == INITIAL_VALUE)) {
                min_age = emp[j]->age;
            }
        }
        for (int j = 0; j < capacity_of_emp; j++) {
            if (strcmp(emp[j]->position, unique_positions[i]) == EQ_STR &&
                emp[j]->age == min_age) {
                emp[j]->mark_youngest_in_position = TRUE;
            }
        }
    }
    return TRUE;
}

int get_the_oldest_in_positions_static(employee_info **emp, int capacity_of_emp,
                                       char **unique_positions, int amount_of_unique_positions) {

    if (!emp || !unique_positions) {
        return FALSE;
    }

    mark_all_as_unchecked(emp, capacity_of_emp);
    for (int i = 0; i < amount_of_unique_positions; i++) {

        int max_age = INITIAL_VALUE;
        for (int j = 0; j < capacity_of_emp; j++) {
            if (strcmp(emp[j]->position, unique_positions[i]) == EQ_STR &&
                (emp[j]->age > max_age || max_age == INITIAL_VALUE)) {
                max_age = emp[j]->age;
            }

        }
        for (int j = 0; j < capacity_of_emp; j++) {
            if (strcmp(emp[j]->position, unique_positions[i]) == EQ_STR &&
                emp[j]->age == max_age) {

                emp[j]->mark_oldest_in_position = TRUE;

            }
        }
    }

    return TRUE;
}

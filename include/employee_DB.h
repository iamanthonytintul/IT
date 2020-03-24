#include "employee_types.h"
#include <string.h>

boolean mark_all_as_unchecked(employee_info **emp, int capacity_of_emp);

boolean sort_by_surname(employee_info **emp, int capacity_of_emp);

char **find_unique_positions(employee_info **emp, int capacity_of_emp, int *amount_of_positions);

boolean mark_position_as_checked(employee_info **emp, int capacity_of_emp, char *position);

char *read_string(FILE *input_stream);

employee_info **read_employees(FILE *input_stream, int capacity_of_emp);

int read_number(FILE *input_stream);

boolean free_employees(employee_info **emp, int capacity_of_emp);

boolean print_employees(FILE* output_stream, employee_info **emp, int capacity_of_emp);

boolean print_employees_in_age(FILE *output_stream, employee_info **emp, int capacity_of_emp,
                               char **unique_positions, int amount_of_unique_positions, char *age_gradation);

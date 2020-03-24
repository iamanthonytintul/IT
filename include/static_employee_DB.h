#include "employee_DB.h"

int get_the_youngest_in_positions_static(FILE *output_stream, employee_info **emp, int capacity_of_emp,
                                  char **unique_positions, int amount_of_unique_positions);

int get_the_oldest_in_positions_static(FILE *output_stream, employee_info **emp, int capacity_of_emp,
                                char **unique_positions, int amount_of_unique_positions);

boolean print_the_most_aged_employees_in_each_position_static(FILE *output_stream, employee_info **emp, int capacity_of_emp);

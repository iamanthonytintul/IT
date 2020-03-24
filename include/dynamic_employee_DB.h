#include "employee_DB.h"

#define _GNU_SOURCE
#define __USE_GNU

boolean free_pthread_data(subarray **pthread_data, int number_of_threads);

boolean print_the_most_aged_employees_in_each_position(FILE *output_stream, employee_info **emp, int capacity_of_emp);

boolean init_pthreads_data(subarray **pthreads_data, FILE *output_stream,
                           employee_info **emp, int capacity_of_emp, char **unique_positions, int number_of_threads,
                           int amount_of_positions);

void *get_the_youngest_in_positions_dynamic(void *data);

void *get_the_oldest_in_positions_dynamic(void *data);



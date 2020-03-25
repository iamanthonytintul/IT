#include "employee_DB.h"

#define _GNU_SOURCE
#define __USE_GNU

boolean free_pthread_data(subarray **pthread_data, int number_of_threads);

boolean
get_youngest_oldest_employees_in_positions_dynamic(employee_info **emp, int capacity_of_emp, char **unique_positions,
                                                   int amount_of_positions);

boolean init_pthreads_data(subarray **pthreads_data,
                           employee_info **emp, int capacity_of_emp, char **unique_positions, int number_of_threads,
                           int amount_of_positions);



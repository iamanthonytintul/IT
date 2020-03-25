#include "dynamic_employee_DB.h"
#include <sys/sysinfo.h>
#include <pthread.h>
#include <sched.h>

boolean init_pthreads_data(subarray **pthreads_data, employee_info **emp, int capacity_of_emp,
                           char **unique_positions, int number_of_threads, int amount_of_positions) {

    if (!pthreads_data || !emp || !unique_positions) {
        return FALSE;
    }
    int i = 0;
    int size_of_subarray = amount_of_positions / number_of_threads;
    int offset = 0;
    int err_flag = FALSE;
    for (i = 0; i < number_of_threads && !err_flag; ++i) {
        pthreads_data[i] = (struct subarray *) malloc(sizeof(struct subarray));
        if (!pthreads_data[i]) {
            err_flag = TRUE;
        } else {
            pthreads_data[i]->unique_positions = unique_positions;
            pthreads_data[i]->emp = emp;
            pthreads_data[i]->capacity_of_emp = capacity_of_emp;
            pthreads_data[i]->subarray_size = (i == number_of_threads - 1) ? size_of_subarray + amount_of_positions % 8
                                                                           : size_of_subarray;
            pthreads_data[i]->offset = offset;
            offset += size_of_subarray;
        }
    }
    if (err_flag) {
        return FALSE;
    }
    return TRUE;
}

void *get_the_youngest_oldest_dynamic(void *data) {

    subarray *pthread_data = (subarray *) data;

    int end_index = pthread_data->offset + pthread_data->subarray_size;

    for (int i = pthread_data->offset; i < end_index; i++) {

        int j = 0;
        int min_age = pthread_data->emp[j]->age;
        int max_age = pthread_data->emp[j]->age;
        for (j = 0; j < pthread_data->capacity_of_emp; j++) {
            if (strcmp(pthread_data->emp[j]->position, pthread_data->unique_positions[i]) == EQ_STR) {

                if (pthread_data->emp[j]->age < min_age || min_age == INITIAL_VALUE) {

                    min_age = pthread_data->emp[j]->age;

                }
                if (pthread_data->emp[j]->age > max_age || max_age == INITIAL_VALUE) {

                    max_age = pthread_data->emp[j]->age;

                }
            }
        }

        for (j = 0; j < pthread_data->capacity_of_emp; j++) {
            if (strcmp(pthread_data->emp[j]->position, pthread_data->unique_positions[i]) == EQ_STR) {
                if (pthread_data->emp[j]->age == min_age) {

                    pthread_data->emp[j]->mark_youngest_in_position = TRUE;

                }
                if (pthread_data->emp[j]->age == max_age) {

                    pthread_data->emp[j]->mark_oldest_in_position = TRUE;

                }
            }
        }
    }

    return NULL;
}

boolean
get_youngest_oldest_employees_in_positions_dynamic(employee_info **emp, int capacity_of_emp, char **unique_positions,
                                                   int amount_of_positions) {

    if (!emp) {
        return FALSE;
    }

    int number_of_threads = get_nprocs();
    pthread_t *pthreads = (pthread_t *) malloc(number_of_threads * sizeof(pthread_t));
    if (!pthreads) {
        return FALSE;
    }
    subarray **pthreads_data = (subarray **) malloc(number_of_threads * sizeof(subarray *));
    if (!pthreads_data) {
        free(pthreads);
        return FALSE;
    }

    if (!init_pthreads_data(pthreads_data, emp, capacity_of_emp,
                            unique_positions, number_of_threads, amount_of_positions)) {
        free(pthreads);
        free_pthread_data(pthreads_data, number_of_threads);
        return FALSE;
    }

    int err_flag = FALSE;
    for (int i = 0; i < number_of_threads && !err_flag; i++) {
        err_flag = pthread_create(&(pthreads[i]), NULL, &get_the_youngest_oldest_dynamic, pthreads_data[i]);
//        cpu_set_t cpu_set;
//        CPU_ZERO(&cpu_set);
//        CPU_SET(i, &cpu_set);
//        pthread_setaffinity_np(pthreads[i], sizeof(cpu_set), &cpu_set);
    }

    for (int i = 0; i < number_of_threads; i++) {
        pthread_join(pthreads[i], NULL);
    }

    free(pthreads);
    free_pthread_data(pthreads_data, number_of_threads);
    if (err_flag) {
        return FALSE;
    }

    return TRUE;
}

boolean free_pthread_data(subarray **pthread_data, int number_of_threads) {
    if (!pthread_data) {
        return FALSE;
    }
    for (int i = 0; i < number_of_threads; i++) {
        if (pthread_data[i] != NULL) {
            free(pthread_data[i]);
        }
    }
    free(pthread_data);
    return TRUE;
}


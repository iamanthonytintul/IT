#include <stdio.h>
#include <stdlib.h>

#define FIRST_SYMBOL 0
#define EQ_STR 0
#define INITIAL_VALUE -1
#define FAILURE -1

typedef enum boolean {
    FALSE, TRUE
} boolean;

enum {
    YOUNG, OLD
};

typedef struct employee_info {
    char *name;
    char *surname;
    char *position;
    int salary;
    int age;
    int experience;
    char sex;
    int is_checked:2;
    int mark_youngest_in_position:2;
    int mark_oldest_in_position:2;
} employee_info;

typedef struct subarray {
    employee_info **emp;
    char **unique_positions;
    int capacity_of_emp;
    int subarray_size;
    int offset;
} subarray;


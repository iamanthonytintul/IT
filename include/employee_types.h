#include <stdio.h>
#include <stdlib.h>

#define FIRST_SYMBOL 0
#define EQ_STR 0
#define INITIAL_VALUE -1
#define FAILURE -1

typedef enum boolean {
    FALSE, TRUE
} boolean;

typedef struct employee_info {  // The input goes in the following sequence:
    char *name;                 //  Name
    char *surname;              //  Surname
    char *position;             //  Age
    int salary;                 //  Sex
    int age;                    //  Position
    int experience;             //  Salary
    char sex;                   //  Experience
    int is_checked:2;
} employee_info;

typedef struct subarray {
    FILE *output_stream;
    employee_info **emp;
    char **unique_positions;
    int the_most_age;
    int capacity_of_emp;
    int subarray_size;
    int offset;
} subarray;
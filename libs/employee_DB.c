#include "employee_DB.h"

boolean mark_all_as_unchecked(employee_info **emp, int capacity_of_emp) {
    if (!emp) {
        return FALSE;
    }
    for (int i = 0; i < capacity_of_emp; ++i) {
        emp[i]->is_checked = FALSE;
    }

    return TRUE;
}

boolean sort_by_surname(employee_info **emp, int capacity_of_emp) {
    if (!emp) {
        return FALSE;
    }
    for (int i = 0; i < capacity_of_emp; i++) {
        int min_surname = i;
        for (int j = i + 1; j < capacity_of_emp; j++) {
            if (strcmp(emp[min_surname]->surname, emp[j]->surname) > EQ_STR) {
                min_surname = j;
            }
        }
        employee_info *tmp_employee = emp[min_surname];
        emp[min_surname] = emp[i];
        emp[i] = tmp_employee;
    }

    return TRUE;
}

char **find_unique_positions(employee_info **emp, int capacity_of_emp, int *amount_of_positions) {
    if (!emp || !amount_of_positions) {
        return NULL;
    }
    char **unique_positions = (char **) malloc(capacity_of_emp * sizeof(char *));
    if (!unique_positions) {
        return NULL;
    }
    mark_all_as_unchecked(emp, capacity_of_emp);
    *amount_of_positions = 0;
    for (int i = 0; i < capacity_of_emp; i++) {
        if (!emp[i]->is_checked) {
            unique_positions[*amount_of_positions] = emp[i]->position;
            mark_position_as_checked(emp, capacity_of_emp, emp[i]->position);
            *amount_of_positions = *amount_of_positions + 1;
        }
    }
    return unique_positions;
}

boolean mark_position_as_checked(employee_info **emp, int capacity_of_emp, char *position) {
    if (!emp || !position) {
        return FALSE;
    }
    for (int i = 0; i < capacity_of_emp; ++i) {
        if (strcmp(emp[i]->position, position) == EQ_STR)
            emp[i]->is_checked = TRUE;
    }

    return TRUE;
}

boolean is_digit(int input_char) {
    return (input_char >= '0' && input_char <= '9');
}

boolean is_end_of_string(int input_char) {
    return input_char == EOF || input_char == '\n';
}

boolean clean_buffer(FILE *input_stream) {
    if (!input_stream) {
        return FALSE;
    }
    while (!is_end_of_string(fgetc(input_stream)));
    return TRUE;
}

char *read_string(FILE *input_stream) {
    if (!input_stream) {
        return NULL;
    }
    char *input_string = NULL;
    int size = 0;
    int capacity = 0;
    char input_char = '\0';
    int error_flag = FALSE;

    while (input_char = fgetc(input_stream), !error_flag && !is_end_of_string(input_char)) {
        if (size + 1 >= capacity) {

            size_t new_capacity = !capacity ? 1 : capacity * 2;
            char *tmp = (char *) malloc((new_capacity + 1) * sizeof(char));
            if (!tmp) {
                if (input_string) {
                    free(input_string);
                }
                clean_buffer(input_stream);
                error_flag = TRUE;
            }
            if (!error_flag && input_string) {
                tmp = strcpy(tmp, input_string);
                free(input_string);
            }
            input_string = tmp;
            capacity = new_capacity;

        }
        if (!error_flag) {
            input_string[size] = input_char;
            input_string[size + 1] = '\0';
            size++;
        }
    }
    return input_string;
}

int read_number(FILE *input_stream) {
    int input_number = 0;
    if (!input_stream) {
        return FAILURE;
    }
    int input_char = 0;
    int error_flag = FALSE;

    input_char = fgetc(input_stream);
    while (!error_flag && !is_end_of_string(input_char)) {
        if (!is_digit(input_char)) {
            clean_buffer(input_stream);
            error_flag = TRUE;
        } else {
            input_number = input_number * 10 + (input_char - '0');
            input_char = fgetc(input_stream);
        }

    }
    if (error_flag) {
        return FAILURE;
    }
    return input_number;
}

employee_info **read_employees(FILE *input_stream, int capacity_of_emp) {
    if (!input_stream) {
        return NULL;
    }

    employee_info **emp = (employee_info **) malloc(capacity_of_emp * sizeof(employee_info *));
    if (!emp) {
        return NULL;
    }
    for (int i = 0; i < capacity_of_emp; ++i) {
        emp[i] = NULL;
    }
    char *tmp = NULL;
    int read_employee_flag = TRUE;
    for (int i = 0; i < capacity_of_emp && read_employee_flag; ++i) {

        employee_info *tmp_emp = malloc(sizeof(employee_info));
        if (tmp_emp != NULL) {
            tmp_emp->name = read_string(input_stream);
            if (tmp_emp->name == NULL) {
                read_employee_flag = FALSE;
            }
            tmp_emp->surname = read_string(input_stream);
            if (tmp_emp->surname == NULL) {
                read_employee_flag = FALSE;
            }
            tmp_emp->age = read_number(input_stream);
            if (tmp_emp->age == FAILURE) {
                read_employee_flag = FALSE;
            }

            tmp = read_string(input_stream);
            if (tmp == NULL) {
                read_employee_flag = FALSE;
            } else {
                tmp_emp->sex = tmp[FIRST_SYMBOL];
                free(tmp);
            }

            tmp_emp->position = read_string(input_stream);
            if (tmp_emp->position == NULL) {
                read_employee_flag = FALSE;
            }
            tmp_emp->salary = read_number(input_stream);
            if (tmp_emp->salary == FAILURE) {
                read_employee_flag = FALSE;
            }
            tmp_emp->experience = read_number(input_stream);
            if (tmp_emp->experience == FAILURE) {
                read_employee_flag = FALSE;
            }
            tmp_emp->mark_oldest_in_position = FALSE;
            tmp_emp->mark_youngest_in_position = FALSE;

            fgetc(input_stream); // Введен разделитель
            emp[i] = tmp_emp;
        }
    }
    if (read_employee_flag == FALSE) {
        free_employees(emp, capacity_of_emp);
        return NULL;
    }
    return emp;
}

boolean free_employees(employee_info **emp, int capacity_of_emp) {
    if (!emp) {
        return FALSE;
    }
    for (int i = 0; i < capacity_of_emp; i++) {
        if (emp[i] != NULL) {
            if (emp[i]->name != NULL) {
                free(emp[i]->name);
            }
            if (emp[i]->surname != NULL) {
                free(emp[i]->surname);
            }
            if (emp[i]->position != NULL) {
                free(emp[i]->position);
            }
            free(emp[i]);
        }
    }
    free(emp);

    return TRUE;
}

boolean print_employees_in_age(FILE *output_stream, employee_info **emp, int capacity_of_emp, char **unique_positions,
                               int amount_of_unique_positions, int age_gradation) {
    if (!output_stream || !emp || !unique_positions) {
        return FALSE;
    }
    for (int i = 0; i < amount_of_unique_positions; ++i) {
        fprintf(output_stream, "----------THE %sEST in %s position----------\n",
                (age_gradation == YOUNG) ? "YOUNG" : "OLD",
                unique_positions[i]);

        for (int j = 0; j < capacity_of_emp; j++) {
            if (strcmp(emp[j]->position, unique_positions[i]) == EQ_STR) {
                if ((age_gradation == YOUNG && emp[j]->mark_youngest_in_position == TRUE) ||
                    (age_gradation == OLD && emp[j]->mark_oldest_in_position == TRUE)) {
                    fprintf(output_stream, "%s\n", emp[j]->name);
                    fprintf(output_stream, "%s\n", emp[j]->surname);
                    fprintf(output_stream, "%d\n", emp[j]->age);
                    fprintf(output_stream, "%c\n", emp[j]->sex);
                    fprintf(output_stream, "%s\n", emp[j]->position);
                    fprintf(output_stream, "%d\n", emp[j]->salary);
                    fprintf(output_stream, "%d\n", emp[j]->experience);
                    fprintf(output_stream, "\n");
                }
            }
        }
        fprintf(output_stream, "---------------------------------------------\n\n");
    }
    return TRUE;
}

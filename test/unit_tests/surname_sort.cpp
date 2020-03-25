#include "gtest/gtest.h"

extern "C" {
#include "employee_DB.h"
}

TEST(SurnameSort, HandlesRegularCase) {

    FILE *input_stream = fopen(PATH_INPUT_REGULAR_CASE, "r");
    FILE *output_stream = fopen(PATH_OUTPUT, "w+");
    FILE *true_output_stream = fopen(PATH_TRUE_OUTPUT, "r");

    EXPECT_TRUE(input_stream != NULL);
    EXPECT_TRUE(output_stream != NULL);
    EXPECT_TRUE(true_output_stream != NULL);

    int capacity_of_employees = read_number(input_stream);
    employee_info **emp = read_employees(input_stream, capacity_of_employees);
    EXPECT_TRUE(emp != NULL);

    EXPECT_EQ(sort_by_surname(emp, capacity_of_employees), TRUE);

    for (int j = 0; j < capacity_of_employees; j++) {
        fprintf(output_stream, "%s\n", emp[j]->name);
        fprintf(output_stream, "%s\n", emp[j]->surname);
        fprintf(output_stream, "%d\n", emp[j]->age);
        fprintf(output_stream, "%c\n", emp[j]->sex);
        fprintf(output_stream, "%s\n", emp[j]->position);
        fprintf(output_stream, "%d\n", emp[j]->salary);
        fprintf(output_stream, "%d\n", emp[j]->experience);
        fprintf(output_stream, "\n");
    }

    rewind(output_stream);

    int char_output = '\0';
    int char_true_output = '\0';
    do {
        EXPECT_EQ(char_output, char_true_output);
        char_output = fgetc(output_stream);
        char_true_output = fgetc(true_output_stream);
    } while (char_output != EOF || char_true_output != EOF);

    fclose(output_stream);
    fclose(input_stream);
    free_employees(emp, capacity_of_employees);
}

TEST(SurnameSort, HandlesSameSurnameCase) {
    FILE *input_stream = fopen(PATH_INPUT_SAME_SURNAME_CASE, "r");
    FILE *output_stream = fopen(PATH_OUTPUT, "w+");

    EXPECT_TRUE(input_stream != NULL);
    EXPECT_TRUE(output_stream != NULL);

    int capacity_of_employees = read_number(input_stream);
    employee_info **emp = read_employees(input_stream, capacity_of_employees);
    EXPECT_TRUE(emp != NULL);

    EXPECT_EQ(sort_by_surname(emp, capacity_of_employees), TRUE);

    for (int j = 0; j < capacity_of_employees; j++) {
        fprintf(output_stream, "%s\n", emp[j]->name);
        fprintf(output_stream, "%s\n", emp[j]->surname);
        fprintf(output_stream, "%d\n", emp[j]->age);
        fprintf(output_stream, "%c\n", emp[j]->sex);
        fprintf(output_stream, "%s\n", emp[j]->position);
        fprintf(output_stream, "%d\n", emp[j]->salary);
        fprintf(output_stream, "%d\n", emp[j]->experience);
        fprintf(output_stream, "\n");
    }

    rewind(input_stream);
    rewind(output_stream);

    int char_output = '\0';
    int char_input = '\0';
    while (fgetc(input_stream) != '\n');

    do {
        EXPECT_EQ(char_output, char_input);
        char_output = fgetc(output_stream);
        char_input = fgetc(input_stream);
    } while (char_output != EOF || char_input != EOF);

    fclose(output_stream);
    fclose(input_stream);
    free_employees(emp, capacity_of_employees);
}

TEST(SurnameSort, HandlesNullDB) {
    FILE *input_stream = fopen(PATH_INPUT_SAME_SURNAME_CASE, "r");
    FILE *output_stream = fopen(PATH_OUTPUT, "w+");

    EXPECT_TRUE(input_stream != NULL);
    EXPECT_TRUE(output_stream != NULL);

    int capacity_of_employees = read_number(input_stream);
    employee_info **emp = NULL;

    EXPECT_EQ(sort_by_surname(emp, capacity_of_employees), FALSE);

    fclose(output_stream);
    fclose(input_stream);
}
#include "main.h"
#include "common/config.h"
#include <stdio.h>
#include <stdlib.h>

void day_1_impl(const char *input, config *config) {
    part_1(input, config);
    part_2(input, config);
}

void part_1(const char *input, config *config) {
    const char *pos = input;
    size_t rows = 0;

    while (*pos != '\0') {
        char current_char = *pos;
        pos++;
        if (current_char == '\n') {
            rows++;
        }
    }

    calibration_value *calibration_values =
        malloc(sizeof(calibration_value) * rows);

    size_t current_row = 0;
    pos = input;
    char current_digit = 'T';
    while (*pos != '\0') {
        char current_char = *pos;
        pos++;

        if (current_char == '\n') {
            // get last num
            calibration_values[current_row].number[1] = current_digit;
            current_row++;
            current_digit = 'T';
            continue;
        }

        // check is numeric
        if (current_char >= '0' && current_char <= '9') {
            if (current_digit == 'T') {
                calibration_values[current_row].number[0] = current_char;
            }

            current_digit = current_char;
        }
    }

    if (config->verbose)
        printf("rows: %zu\n", rows);

    int total = 0;
    for (size_t i = 0; i < rows; i++) {
        calibration_value cv = calibration_values[i];
        char str[3] = {cv.number[0], cv.number[1], '\0'};
        if (config->verbose)
            printf("%s\n", str);

        int num = atoi(str);
        total += num;
    }

    printf("Part 1 Total: %d\n", total);

    free(calibration_values);
}

void part_2(const char *input, config *config) {}

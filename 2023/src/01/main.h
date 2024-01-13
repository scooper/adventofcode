#ifndef DAY1_ENTRY_H
#define DAY1_ENTRY_H

#include "common/config.h"

typedef struct calibration_value {
    char number[2];
} calibration_value;

const static struct {
    char num;
    const char* str;
} num_reference[] = {
    {'1', "one"},
    {'2', "two"},
    {'3', "three"},
    {'4', "four"},
    {'5', "five"},
    {'6', "six"},
    {'7', "seven"},
    {'8', "eight"},
    {'9', "nine"}
};

void day_1_impl(const char *input, config *config);
void part_1(const char *input, config *config);
void part_2(const char *input, config *config);

#endif // DAY1_ENTRY_H

#ifndef DAY1_ENTRY_H
#define DAY1_ENTRY_H

#include "common/config.h"

typedef struct calibration_value {
    char number[2];
} calibration_value;

void day_1_impl(const char *input, config *config);
void part_1(const char *input, config *config);
void part_2(const char *input, config *config);

#endif // DAY1_ENTRY_H

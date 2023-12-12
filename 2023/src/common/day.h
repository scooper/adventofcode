#ifndef DAY_H
#define DAY_H

#include "01/main.h"
#include "config.h"

typedef struct day {
    int num;
    void (*day_impl)(const char *input, config *config);
} day;

#define DAYS_NUM 1
static day days[DAYS_NUM] = {{1, &day_1_impl}};

#endif // DAY_H

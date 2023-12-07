#ifndef DAY_H
#define DAY_H

#include "20231201/entry.h"

typedef struct day {
    int num;
    void (*day_impl)(const char *input);
} day;

#define DAYS_NUM 1
static day days[DAYS_NUM] = {{1, &day_1_impl}};

#endif // DAY_H

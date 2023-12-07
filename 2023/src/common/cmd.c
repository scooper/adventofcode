#include "cmd.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "day.h"

int day_to_run = -1;
char *input_name = nullptr;

void parse_args(int argc, char *argv[]) {
    for (int i = 0; i < argc; i++) {
        const char *arg = argv[i];
        for (int j = 0; j < CMD_NUM; j++) {
            cmd_option option = cmds[j];
            if (strcmp(arg, option.cmd_short) == 0) {
                if (option.has_arg) {
                    if (i + 1 >= argc) {
                        printf("Arg not provided for option '%s', '%s'\n",
                               option.cmd_short, option.cmd_long);
                        return;
                    }
                    const char *option_arg = argv[++i];
                    option.callback(option_arg);
                } else {
                    option.callback(nullptr);
                }
                break;
            } else if (strstr(arg, option.cmd_long) != nullptr) {
                if (option.has_arg) {
                    const char *equals = strstr(arg, "=");
                    if (equals == nullptr) {
                        printf("Arg not provided for option '%s', '%s'\n",
                               option.cmd_short, option.cmd_long);
                        return;
                    }
                    option.callback((equals + 1));
                } else {
                    option.callback(nullptr);
                }
                break;
            }
        }
    }

    if (day_to_run == -1) {
        printf("Day has not been provided, run ('-h', '--help') for usage.\n");
        return;
    }
    if (day_to_run - 1 < 0 || day_to_run - 1 > DAYS_NUM - 1) {
        printf("Day is not in range 0 - %d\n", DAYS_NUM);
        return;
    }

    days[day_to_run - 1].day_impl("something");
}

void set_day(const char *day) { day_to_run = atoi(day); }

void verbose_on(const char *_) {
    printf("verbose is on\n");
    g_config.verbose = true;
}

void print_help(const char *_) {
    printf("aoc_2023 - Advent of Code 2023\n\n"
           "Usage:\t aoc_2023 [options] [input]\n"
           "\t e.g. aoc_2023 -d 1 foo/bar.txt\n\n"
           "Options:\n"
           "\t -d DAY_NUMBER   \t Select an available challenge (day) to run.\n"
           "\t --day=DAY_NUMBER\t Day range (1 - %d)\n\n"
           "\t -v              \t Verbose mode, prints more stuff (usually "
           "debug logs).\n"
           "\t --verbose\n",
           DAYS_NUM);
    exit(0);
}

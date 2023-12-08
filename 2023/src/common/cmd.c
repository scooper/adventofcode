#include "cmd.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "day.h"

int day_to_run = -1;
void parse_args(int argc, char *argv[]) {

    // check for help
    if (argc > 1 && (strcmp(argv[1], cmd_help.cmd_short) == 0 ||
                     strcmp(argv[1], cmd_help.cmd_long) == 0)) {
        cmd_help.callback(nullptr);
    }

    for (int i = 1; i < argc - 1; i++) {
        const char *arg = argv[i];
        for (int j = 0; j < CMD_NUM; j++) {
            cmd_option option = cmds[j];
            if (strcmp(arg, option.cmd_short) == 0) {
                if (option.has_arg) {
                    if (i + 1 >= argc - 1) {
                        printf("Arg not provided for option '%s', '%s', %s\n",
                               option.cmd_short, option.cmd_long, see_help);
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
                        printf("Arg not provided for option '%s', '%s', %s\n",
                               option.cmd_short, option.cmd_long, see_help);
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
        printf("Day has not been provided, %s\n", see_help);
        return;
    }
    if (day_to_run - 1 < 0 || day_to_run - 1 > DAYS_NUM - 1) {
        printf("Day is not in range 0 - %d, %s\n", DAYS_NUM, see_help);
        return;
    }
  
    // run day
    days[day_to_run - 1].day_impl(argv[argc - 1]);
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

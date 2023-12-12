#include "cmd.h"
#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "day.h"

void run_cmds(int argc, char *argv[]) {
    config config = {false, -1};

    // check for help
    if (argc > 1 && (strcmp(argv[1], cmd_help.cmd_short) == 0 ||
                     strcmp(argv[1], cmd_help.cmd_long) == 0)) {
        cmd_help.callback(nullptr, &config);
    }

    // check args
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
                    option.callback(option_arg, &config);
                } else {
                    option.callback(nullptr, &config);
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
                    option.callback((equals + 1), &config);
                } else {
                    option.callback(nullptr, &config);
                }
                break;
            }
        }
    }

    if (config.day == -1) {
        printf("Day has not been provided, %s\n", see_help);
        return;
    }
    if (config.day - 1 < 0 || config.day - 1 > DAYS_NUM - 1) {
        printf("Day is not in range 1 - %d, %s\n", DAYS_NUM, see_help);
        return;
    }

    // run day
    char *file_txt = read_file_to_string(argv[argc - 1]);
    days[config.day - 1].day_impl(file_txt, &config);
    free(file_txt);
}

void set_day(const char *day, config *config) { config->day = atoi(day); }

void verbose_on(const char *_, config *config) {
    printf("verbose is on\n");
    config->verbose = true;
}

void print_help(const char *_, config *config) {
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

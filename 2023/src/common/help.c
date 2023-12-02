#include <stdio.h>

void print_help() {
    printf("aoc_2023 - Advent of Code 2023\n\n"
           "Usage:\t aoc_2023 [options] [input]\n"
           "\t e.g. aoc_2023 -d 1 foo/bar.txt\n\n"
           "Options:\n"
           "\t -d=DAY_NUMBER   \t Select an available challenge (day) to run.\n"
           "\t --day=DAY_NUMBER\n\n"
           "\t -v              \t Verbose mode, prints more stuff (usually debug logs).\n"
           "\t --verbose\n");
}

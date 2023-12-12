#ifndef CMD_H
#define CMD_H

#include "config.h"

typedef struct cmd_option {
    bool has_arg;
    char cmd_short[8];
    char cmd_long[16];
    void (*callback)(const char *data, config *config);
} cmd_option;

void run_cmds(int argc, char *argv[]);
void set_day(const char *day, config *config);
void verbose_on(const char *_, config *config);
void print_help(const char *_, config *config);

#define CMD_NUM 2
// probably better as a hash table - would need to make one
static cmd_option cmds[CMD_NUM] = {{false, "-v", "--verbose", &verbose_on},
                                   {true, "-d", "--day", &set_day}};
static const cmd_option cmd_help = {false, "-h", "--help", &print_help};

static const char *see_help = "see ('-h', '--help') for usage.";

#endif // CMD_H

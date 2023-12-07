#ifndef CMD_H
#define CMD_H

typedef struct cmd_option {
    bool has_arg;
    char cmd_short[8];
    char cmd_long[16];
    void (*callback)(const char *data);
} cmd_option;

void parse_args(int argc, char *argv[]);
void set_day(const char *day);
void verbose_on(const char *_);
void print_help(const char *_);

#define CMD_NUM 3
static cmd_option cmds[CMD_NUM] = {{false, "-h", "--help", &print_help},
                                   {false, "-v", "--verbose", &verbose_on},
                                   {true, "-d", "--day", &set_day}};

#endif // CMD_H

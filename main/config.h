#define VERSION_MAJOR 0
#define VERSION_MINOR 0
#define VERSION_PATCH 1

#include "../include/list.h"

struct cmd_history {
    int id;
    char *commands;
    LIST_ENTRY(cmd_history);
};

int modctl(int argc, char **argv);

void history_take(char *cmd, int len);
void history_list();
int inter_hist(int argc, char **argv);

int welcome(int argc, char **argv);

int print_main_version(int argc, char **argv);

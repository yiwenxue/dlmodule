#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "../include/yiwen_int.h"
#include "../include/yiwen_string.h"
#include "../include/command.h"
#include "../include/module.h"
#include "../include/log.h"
#include "../include/yiwen_pcolor.h"

void    history_take(char *cmd, int len);
int     modctl(int argc, char **argv);
int     inter_hist(int argc, char **argv);

struct command_data builtin_cmd_data[] = {
    {"run",         "run a command through shell",          inter_run},
    {"help",        "show a brief introduce to commands",   inter_help},
    {"exit",        "exit the interpreter",                 inter_exit},
    /* {"history",     "show the commands you typed brfore",   inter_hist}, */
    /* {"modctl",      "module conctrl tool",                  modctl}, */
    {NULL,          NULL,                                   NULL},
};

struct command builtin_cmd[] = {
    {"run",         "run a command through shell",          0, &builtin_cmd_data[0], {NULL, NULL}, NULL, NULL},
    {"help",        "show a brief introduce to commands",   0, &builtin_cmd_data[1], {NULL, NULL}, NULL, NULL},
    {"exit",        "exit the interpreter",                 0, &builtin_cmd_data[2], {NULL, NULL}, NULL, NULL},
    /* {"hist",        "show the commands you typed brfore",   0, &builtin_cmd_data[3], {NULL, NULL}, NULL, NULL}, */
    /* {"modctl",      "module control tool",                  0, &builtin_cmd_data[4], {NULL,NULL}, NULL, NULL}, */
    {NULL,          NULL,                                   0, NULL, {NULL,NULL}, NULL, NULL}
};

int modctl(int argc, char **argv){
    int erro = 0;
    if (argc < 3){
        printf("Usage:\n"
                "  <%s> <command> [option]\n"
                "     load   <path to module> load a module.\n"
                "     unload <module name>    unload a module.\n"
                "     status <module name>    show module status.\n"
                "     list                    list all modules.\n", argv[0]);
        return -1;
    }
    if (strncmp(argv[1], "load", 4) == 0){
        erro = modload(mod_list_main_hp, argv[2]);
    }
    return erro;
}

int modlist(struct mod_list_h *mod_list_hp){
    struct module *var;
    printf("List all module.\n");
    LIST_FOREACH(var, mod_list_hp, m_list){
        printf("%s at %p", var->name, var);
    }
    printf("\n");
    return 0;
}

void history_list(){

}

int inter_hist(int argc, char **argv){
    return 0;
}

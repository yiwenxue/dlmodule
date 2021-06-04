#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "../include/command.h"
#include "../include/log.h"
#include "../include/module.h"
#include "../include/yiwen_int.h"
#include "../include/yiwen_pcolor.h"
#include "../include/yiwen_string.h"
#include "config.h"

#define TBUFFER 1024
#define PATH_MAX 255

extern int inter_state;
extern int inter_ifexit;

struct command_data builtin_cmd_data[] = {
    {"run", "run a command through shell", inter_run},
    {"help", "show a brief introduce to commands", inter_help},
    {"exit", "exit the interpreter", inter_exit},
    {"version", "show the version of laucher", print_main_version},
    {NULL, NULL, NULL},
};

struct command builtin_cmd[] = {
    {NULL, NULL, 0, NULL, {NULL, NULL}, NULL, NULL},
    {NULL, NULL, 0, NULL, {NULL, NULL}, NULL, NULL},
    {NULL, NULL, 0, NULL, {NULL, NULL}, NULL, NULL},
    {NULL, NULL, 0, NULL, {NULL, NULL}, NULL, NULL},
    {NULL, NULL, 0, NULL, {NULL, NULL}, NULL, NULL}};

int main(int argc, char *argv[])
{
    welcome(0, NULL);
#if debug
    printf("[main] Launch: Test routine for interpreter + module/command\n");
#endif
    // init module pool
    struct mod_list_h mod_list_main_h;
    mod_list_main_hp = &mod_list_main_h;
    LIST_INIT(mod_list_main_hp);

    // init command pool
    struct cmd_list_h cmd_list_main_h;
    cmd_list_main_hp = &cmd_list_main_h;
    LIST_INIT(cmd_list_main_hp);

    int preset_command_size =
        sizeof(builtin_cmd_data) / sizeof(struct command_data);

    // Fill command pool
    for (int i = 0; 1; ++i) {
        if (builtin_cmd_data[i].name == NULL) {
            break;
        }
        builtin_cmd[i].name = builtin_cmd_data[i].name;
        builtin_cmd[i].desc = builtin_cmd_data[i].desc;
        builtin_cmd[i].commanddata = &builtin_cmd_data[i];

        cmdappend(cmd_list_main_hp, &builtin_cmd[i]);
    }
    // load preload modules
    if (argc >= 2) modload(mod_list_main_hp, argv[1]);
    modload(mod_list_main_hp, "./modctl/modctl.ko");

    inter_init();
    char cmdline[1024];
    modload(mod_list_main_hp, "./hist/hist.ko");
    modload(mod_list_main_hp, "./screencap/screencap.ko");
    modload(mod_list_main_hp, "./hashfile/hashfile.ko");

    while (!inter_ifexit) {
        show_prompt("[%t|%s] > ");

        if (readlinen(cmdline, TBUFFER) == -1) break;

        parser(cmd_list_main_hp, cmdline, TBUFFER);
    }
    printf("\n");

#if debug
    printf("\n [inter] Done.\n");
#endif

    // CleanUp.
    struct module *mvar, *mtvar;
    LIST_FOREACH_SAFE(mvar, mod_list_main_hp, m_list, mtvar)
    {
#if debug
        printf(
            "[main] module info:\n"
            "\t name: %s\n"
            "\t handle: %p\n"
            "\t extra: %p\n",
            mvar->moduledata->name, mvar->moduledata->load,
            mvar->moduledata->extra);
#endif
        modunload(mod_list_main_hp, mvar);
    }

    // remove builtin commands from list
    struct command *cvar, *ctvar;
    LIST_FOREACH_SAFE(cvar, cmd_list_main_hp, cmd_list, ctvar)
    {
        cmdpop(cmd_list_main_hp, cvar);
    }

#if debug
    printf("[main] exit.\n");
#endif
    return 0;
}

void history_list() {}

int inter_hist(int argc, char **argv) { return 0; }

int print_main_version(int argc, char **argv)
{
    print_version(VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
    return 0;
}

int welcome(int argc, char **argv)
{
    char *asci =
        "                ```                     `.--.              \n"
        "            -oyhhddddhs+-          ./shdddyyyyo-           \n"
        "           --`    `:oddddh:      -hddy+:`      .-          \n"
        "                     `+ddd:      `/:`                      \n"
        "                       .hmdo                               \n"
        "             `/oyyyso/. .mmm/         -+syyso/`            \n"
        "          .+:hdmmmmmmdhsydmms       -ydmmmmmmmh:+.         \n"
        "          .  -:://:-.    `ymh           `````    .         \n"
        "                          /mm                              \n"
        "                          ymm`                             \n"
        "                        `ommm`                             \n"
        "                       /mmmmm.                             \n"
        "                  ..  -mmmmmms   ./+`   `-.                \n"
        "          os+/os/:`    :++/hNNdhy--:`     ./ys+/yy         \n"
        "          `y.`hmy`       .sNNNNNNm/        +Nm.`y.         \n"
        "           .y``smdo///+ohmNNm/.yNNNmyo+++ohNh. s-          \n"
        "            -s` -ymNNNmdddhs:---+yhdddmNNds:  o/           \n"
        "             -y`  :yo/:::--.......------`    o/            \n"
        "              .y.   :so/-`                  o/             \n"
        "               `o:     .-:://+oo:-.       .o.              \n"
        "                 -/         `dNy         -/                \n"
        "                   -        -mNm.       ``                 \n"
        "                            hNNNs                          \n"
        "                            oNNN/                          \n"
        "                            `mNm`                          \n"
        "                             /N+                           \n"
        "                              s`                           \n"
        "                                                           \n";

    printf("\033c");
    printf(C_RED "%s" C_DEFAULT "%s", asci,
           " --------------------------------------------------------- \n"
           "|                     Welcome, " C_RED "h4ck3r" C_DEFAULT
           ".                    |\n"
           " --------------------------------------------------------- \n\n");

    return 0;
}

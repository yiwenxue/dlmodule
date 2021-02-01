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
    {NULL,          NULL,                                   NULL},
};

struct command builtin_cmd[] = {
    {"run",         "run a command through shell",          0, &builtin_cmd_data[0], {NULL, NULL}, NULL, NULL},
    {"help",        "show a brief introduce to commands",   0, &builtin_cmd_data[1], {NULL, NULL}, NULL, NULL},
    {"exit",        "exit the interpreter",                 0, &builtin_cmd_data[2], {NULL, NULL}, NULL, NULL},
    {NULL,          NULL,                                   0, NULL, {NULL,NULL}, NULL, NULL}
};

void history_list(){

}

int inter_hist(int argc, char **argv){
    return 0;
}

void welcome(){
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
    printf(C_RED "%s" C_DEFAULT "%s", asci,
" --------------------------------------------------------- \n"
"|                     Welcome, " C_RED "h4ck3r" C_DEFAULT ".                    |\n"
" --------------------------------------------------------- \n\n"
);
}


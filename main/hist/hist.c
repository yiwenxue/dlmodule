#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "../../include/log.h"
#include "../../include/module.h"
#include "../../include/command.h"
#include "../../include/yiwen_int.h"

void store_hist(char *cmd, int len){
    /* struct cmd_history * item = malloc(sizeof(struct cmd_history)); */
    /* item->commands = malloc(sizeof(char) * 1024); */
    /* timestamp_str(item->commands, 1024); */
    /* strncat(item->commands, cmd, len); */

    int fd = open("./.history", O_WRONLY|O_CREAT|O_APPEND, 0666);

    timestamp(fd);
    write(fd, cmd, len);
    write(fd, "\n", 1);

    close(fd);
}

int 
load(int cmd, void *extra){
    int error = 0;

    switch (cmd){
        case MOD_LOAD:
            history_store = store_hist;
            mprintf("Hello interptrter, the commands will be stored as history!\n");
            break;
        case MOD_UNLOAD:
            history_store = history_store_null;
            mprintf("Bye interpreter, the latter command will not be stored any more!\n");
            break;
        default:
            error = -1;
            break;
    }
    return error;
}

static const struct 
module_data isay_mod = {
    "history_store",
    load,
    NULL
};

DECLARE_MODULE(isay, isay_mod);

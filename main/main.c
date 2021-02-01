
#include "config.h"

#define TBUFFER 1024
#define PATH_MAX 255

struct cmd_history {
    int id;
    char *commands;
    LIST_ENTRY(cmd_history);
};

extern int inter_state;
extern int inter_ifexit;

int main(int argc, char *argv[])
{

    welcome();
#if  debug 
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
    // Fill command pool
    for (int i = 0; 1; ++i) {
        if (builtin_cmd[i].name == NULL){
            break;
        }
        cmdappend(cmd_list_main_hp, &builtin_cmd[i]);
    }
    // load preload modules
    if (argc >= 2)
        modload(mod_list_main_hp, argv[1]);
    modload(mod_list_main_hp, "./modctl/modctl.ko");

    inter_init();
    char cmdline[1024];
    modload(mod_list_main_hp, "./hist/hist.ko");

    while (!inter_ifexit) {
        show_prompt("[%t|%s] > ");

        if (readlinen(cmdline, TBUFFER) == -1)
            break;

        parser(cmd_list_main_hp, cmdline, TBUFFER);
    }
    printf("\n");
#if debug 
    printf("\n [inter] Done.\n");
#endif 
    // CleanUp.
    struct module *mvar, *mtvar;
    LIST_FOREACH_SAFE(mvar, mod_list_main_hp, m_list, mtvar){
        /* printf("[main] module info:\n" */
        /*         "\t name: %s\n" */
        /*         "\t handle: %p\n" */
        /*         "\t extra: %p\n", mvar->moduledata->name, mvar->moduledata->load, mvar->moduledata->extra); */
        modunload(mod_list_main_hp, mvar);
    }
    /* struct command *cvar, *ctvar; */
    /* LIST_FOREACH_SAFE(cvar, cmd_list_main_hp, cmd_list, ctvar){ */
    /*     cmdpop(cmd_list_main_hp, cvar); */
    /* } */
#if debug
    printf("[main] exit.\n");
#endif
    return 0;
}

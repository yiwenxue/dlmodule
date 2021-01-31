#include "../../include/module.h"
#include "../../include/command.h"
#include <stdio.h>

int modctl_modload(int argc, char **argv){
    if (argc < 2){
        printf("Usage:\n"
               "    modctl load [module file]\n");
        return -1;
    }

    return modctl_load(mod_list_main_hp, argv[1]);
}

int modctl_modunload(int argc, char **argv){
    if (argc < 2){
        printf("Usage:\n"
               "    modctl unload [module name]\n");
        return -1;
    }
    int erro = 0;
    erro = modctl_unload(mod_list_main_hp, argv[1]);
    if (erro == -1)
        mprintf("Module [%s] not found!\n", argv[1]);
    return erro;
}

int modctl_list(struct mod_list_h *mod_list_hp){
    struct module *var;
    printf("List all module.\n");
    LIST_FOREACH(var, mod_list_hp, m_list){
        /* printf("%s at %p", var->name, var); */
        modshow(var);
    }
    printf("\n");
    return 0;
}

int modctl(int argc, char **argv){
  if (argc < 2){
	printf("Usage:\n"
			"    <%s> <cmd> \n", argv[0]);
    return -1;
  }
  if (strncmp(argv[1], "load", 4) == 0) {
  	return modctl_modload(argc-1, argv+1);
  } else if (strncmp(argv[1], "unload", 6) == 0){
  	return modctl_modunload(argc-1, argv+1);
  } else if (strncmp(argv[1], "list", 4) == 0){
    return modctl_list(mod_list_main_hp);
  }
  return 0;
}

static int 
load(int cmd, void *extra){
  int erro =0;
  switch (cmd){
  case MOD_LOAD:
	mprintf("Modctl module installed\n");
	break;
  case MOD_UNLOAD:
	mprintf("Modctl module uninstalled\n");
	break;
  default:
	erro = -1;
	break;
  }
  return 0;
}

const struct command_data modctl_data = {
  .name = "modctl",
  .desc = "Modctl is cmd tool manage loaded modules.",
  .evh = modctl
};

COMMAND_MODULE(modctl, &modctl_data, load, NULL, NULL);

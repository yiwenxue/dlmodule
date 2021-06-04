#include <ctype.h>
#include <fcntl.h>
#include <openssl/sha.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../../include/command.h"
#include "../../include/module.h"
#include "../../include/yiwen_int.h"

char *default_asci =
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

const size_t fdsize(int fd)
{
    off_t offset = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    return offset;
}

int splash(int argc, char **argv)
{
    char *asci;

    if (argc == 1)
        asci = default_asci;
    else {
        int fd;
        char file_name[255] = {0};
        char *path = getenv("ASCI_PATH");
        if (path) {
            snprintf(file_name, 255, "%s/%s.asci", path, argv[1]);
            fd = open(file_name, O_RDONLY);
            int size = fdsize(fd);
            char *data = (char *)malloc(sizeof(char) * size);
            read(fd, data, size);
            close(fd);

            asci = data;
        }
        else
            asci = default_asci;
    }

    printf("\033c");
    printf(C_RED "%s" C_DEFAULT "%s", asci,
           " --------------------------------------------------------- \n"
           "|                     Welcome, " C_RED "h4ck3r" C_DEFAULT
           ".                    |\n"
           " --------------------------------------------------------- \n\n");

    if (asci != default_asci) free(asci);

    return 0;
}

static int load(int cmd, void *extra)
{
    int erro = 0;
    switch (cmd) {
        case MOD_LOAD:
            mprintf("Splash module installed\n");
            break;
        case MOD_UNLOAD:
            mprintf("Splash module uninstalled\n");
            break;
        default:
            erro = -1;
            break;
    }
    return 0;
}

const struct command_data splash_data = {
    .name = "splash",
    .desc = "Splash is cmd tool to show an ascii art.",
    .evh = splash};

COMMAND_MODULE(splash, &splash_data, load, NULL, NULL);

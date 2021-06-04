#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <openssl/sha.h>
#include <ctype.h>
#include <fcntl.h>

#include "../../include/command.h"
#include "../../include/log.h"
#include "../../include/module.h"
#include "../../include/yiwen_int.h"

#define VERSION_MAJOR 0
#define VERSION_MINOR 0
#define VERSION_PATCH 1

struct hashfile_option {
    char opt;
    char *desc;
};

struct hashfile_option hashfile_options[] = {
    {'f', "The file to store contents"}, {'t', "Choose a hash algorithm"}, {'b', "set the block size of hash buffer"},
    {'h', "Show this help msg\n"}, {'v', "Show the version of this program"}, {0,NULL}
};

const char *hashfile_descript =
    "This program is used to calculate the hash signature of a file.";

unsigned long strtosize(const char *restrict str);

const size_t fdsize(int fd);

unsigned char *fdsha1(char *filename, long block_size);
unsigned char *fdsha224(char *filename, long block_size);
unsigned char *fdsha256(char *filename, long block_size);
unsigned char *fdsha384(char *filename, long block_size);
unsigned char *fdsha512(char *filename, long block_size);

unsigned long strtosize(const char *restrict str)
{
    unsigned long file_size = 0;
    int arg_len = strlen(str);
    if (arg_len > 20) {
        mprintf("the input size is not supported %s, please use B,K,M,G\n", str);
    }

    char *pEnd, dim;
    if (str[arg_len - 1] < '0' || str[arg_len - 1] > '9') {
        dim = str[arg_len - 1];
    }
    else
        dim = 'B';
    dim = tolower(dim);

    file_size = strtol(str, &pEnd, 10);

    switch (dim) {
        case 'b':
            break;
        case 'k':
            file_size <<= 10;
            break;
        case 'm':
            file_size <<= 20;
            break;
        case 'g':
            file_size <<= 30;
            break;
        default:
            mprintf("Wrong units: %c\n", dim);
            return -1;
    }
    return file_size;
}

unsigned char *fdsha1(char *filename, long block_size)
{
    int fd = open(filename, O_RDONLY, 0666);

    long file_size = fdsize(fd);

    if (file_size == 0) {
        mprintf("0 byte got.\n");
        close(fd);
        return 0;
    }

    SHA_CTX sha_context;
    if (!SHA1_Init(&sha_context)) {
        perror("SHA1_Init failed!");
        exit(-1);
    }

    unsigned char *sha =
        (unsigned char *)malloc(sizeof(char) * SHA_DIGEST_LENGTH);

    char *buffer = (char *)malloc(sizeof(char) * block_size);

    long sign = 0, diff = 0;
    unsigned long read_size = 0;
    while (file_size != 0) {
        diff = file_size - block_size;
        sign = diff >> (sizeof(long) * 8 - 1);

        read_size = block_size + (diff & sign);

        read(fd, buffer, read_size);

        if (!SHA1_Update(&sha_context, buffer, read_size)) {
            perror("SHA1_Update failed!");
            exit(-1);
        }

        file_size -= read_size;
    }
    close(fd);

    if (!SHA1_Final(sha, &sha_context)) {
        perror("SHA1_Final Failed!");
        exit(-1);
    }

    return sha;
}

unsigned char *fdsha224(char *filename, long block_size)
{
    int fd = open(filename, O_RDONLY, 0666);

    long file_size = fdsize(fd);

    if (file_size == 0) {
        mprintf("0 byte got.\n");
        close(fd);
        return 0;
    }

    SHA256_CTX sha_context;
    if (!SHA224_Init(&sha_context)) {
        perror("SHA1_Init failed!");
        exit(-1);
    }

    unsigned char *sha =
        (unsigned char *)malloc(sizeof(char) * SHA224_DIGEST_LENGTH);

    char *buffer = (char *)malloc(sizeof(char) * block_size);

    long sign = 0, diff = 0;
    unsigned long read_size = 0;
    while (file_size != 0) {
        diff = file_size - block_size;
        sign = diff >> (sizeof(long) * 8 - 1);

        read_size = block_size + (diff & sign);

        read(fd, buffer, read_size);

        if (!SHA224_Update(&sha_context, buffer, read_size)) {
            perror("SHA1_Update failed!");
            exit(-1);
        }

        file_size -= read_size;
    }
    close(fd);

    if (!SHA224_Final(sha, &sha_context)) {
        perror("SHA1_Final Failed!");
        exit(-1);
    }

    return sha;
}
unsigned char *fdsha256(char *filename, long block_size)
{
    int fd = open(filename, O_RDONLY, 0666);

    long file_size = fdsize(fd);

    if (file_size == 0) {
        mprintf("0 byte got.\n");
        close(fd);
        return 0;
    }

    SHA256_CTX sha_context;
    if (!SHA256_Init(&sha_context)) {
        perror("SHA1_Init failed!");
        exit(-1);
    }

    unsigned char *sha =
        (unsigned char *)malloc(sizeof(char) * SHA256_DIGEST_LENGTH);

    char *buffer = (char *)malloc(sizeof(char) * block_size);

    long sign = 0, diff = 0;
    unsigned long read_size = 0;
    while (file_size != 0) {
        diff = file_size - block_size;
        sign = diff >> (sizeof(long) * 8 - 1);

        read_size = block_size + (diff & sign);

        read(fd, buffer, read_size);

        if (!SHA256_Update(&sha_context, buffer, read_size)) {
            perror("SHA1_Update failed!");
            exit(-1);
        }

        file_size -= read_size;
    }
    close(fd);

    if (!SHA256_Final(sha, &sha_context)) {
        perror("SHA1_Final Failed!");
        exit(-1);
    }

    return sha;
}
unsigned char *fdsha384(char *filename, long block_size)
{
    int fd = open(filename, O_RDONLY, 0666);

    long file_size = fdsize(fd);

    if (file_size == 0) {
        mprintf("0 byte got.\n");
        close(fd);
        return 0;
    }

    SHA512_CTX sha_context;
    if (!SHA384_Init(&sha_context)) {
        perror("SHA1_Init failed!");
        exit(-1);
    }

    unsigned char *sha =
        (unsigned char *)malloc(sizeof(char) * SHA384_DIGEST_LENGTH);

    char *buffer = (char *)malloc(sizeof(char) * block_size);

    long sign = 0, diff = 0;
    unsigned long read_size = 0;
    while (file_size != 0) {
        diff = file_size - block_size;
        sign = diff >> (sizeof(long) * 8 - 1);

        read_size = block_size + (diff & sign);

        read(fd, buffer, read_size);

        if (!SHA384_Update(&sha_context, buffer, read_size)) {
            perror("SHA1_Update failed!");
            exit(-1);
        }

        file_size -= read_size;
    }
    close(fd);

    if (!SHA384_Final(sha, &sha_context)) {
        perror("SHA1_Final Failed!");
        exit(-1);
    }

    return sha;
}
unsigned char *fdsha512(char *filename, long block_size)
{
    int fd = open(filename, O_RDONLY, 0666);

    long file_size = fdsize(fd);

    if (file_size == 0) {
        mprintf("0 byte got.\n");
        close(fd);
        return 0;
    }

    SHA512_CTX sha_context;
    if (!SHA512_Init(&sha_context)) {
        perror("SHA1_Init failed!");
        exit(-1);
    }

    unsigned char *sha =
        (unsigned char *)malloc(sizeof(char) * SHA512_DIGEST_LENGTH);

    char *buffer = (char *)malloc(sizeof(char) * block_size);

    long sign = 0, diff = 0;
    unsigned long read_size = 0;
    while (file_size != 0) {
        diff = file_size - block_size;
        sign = diff >> (sizeof(long) * 8 - 1);

        read_size = block_size + (diff & sign);

        read(fd, buffer, read_size);

        if (!SHA512_Update(&sha_context, buffer, read_size)) {
            perror("SHA1_Update failed!");
            exit(-1);
        }

        file_size -= read_size;
    }
    close(fd);

    if (!SHA512_Final(sha, &sha_context)) {
        perror("SHA1_Final Failed!");
        exit(-1);
    }

    return sha;
}

const size_t fdsize(int fd)
{
    off_t offset = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    return offset;
}

int hashfile_print_usage(int argc, char **argv)
{
    mprintf("Usage: \n");
    mprintf("%s <opt> <arg>\n", argv[0]);
    mprintf("%s\n", hashfile_descript);
    int i = 0;
    while (1) {
        if (hashfile_options[i].desc != NULL)
            mprintf("\t-%c    %s\n", hashfile_options[i].opt, hashfile_options[i].desc);
        else
            break;
        i++;
    }
    return 0;
}

int hashfile(int argc, char **argv) {
    if (argc == 1) {
        fprintf(stderr, "error: no args recived!\n");
        hashfile_print_usage(argc, argv);
        return -1;
    }

    char *file_name = NULL;
    char *hash_algo = "sha1";
    unsigned long block_size = 1024;

    int long_index = 0, opt = 0;

    while(long_index < argc)
    {
        if (argv[long_index][0] == '-')
        {
            if(strnlen(argv[long_index], 255) == 1)
            {
                long_index ++;
                continue;
            }
            switch (argv[long_index][1]) {
            case 'f':
                file_name = argv[++long_index];
                break;
            case 't':
                hash_algo = argv[++long_index];
                break;
            case 'b':
                block_size = strtosize(argv[++long_index]);
                break;
            case 'h':
                hashfile_print_usage(argc, argv);
                return 0;
            case 'v':
                print_version(VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
                return 0;
            default:
                mprintf("Unexcepted input\n");
                hashfile_print_usage(argc, argv);
                return -1;
            }
        }
        long_index ++;
    }

    if (file_name == NULL)
    {
        return -1;
    }

    unsigned char *res = 0;
    int sha_len = 0;

    if (strncmp(hash_algo, "sha1", 4) == 0) {
        res = fdsha1(file_name, block_size);
        sha_len = SHA_DIGEST_LENGTH;
    }
    else if (strncmp(hash_algo, "sha224", 4) == 0) {
        res = fdsha224(file_name, block_size);
        sha_len = SHA224_DIGEST_LENGTH;
    }
    else if (strncmp(hash_algo, "sha256", 4) == 0) {
        res = fdsha256(file_name, block_size);
        sha_len = SHA256_DIGEST_LENGTH;
    }
    else if (strncmp(hash_algo, "sha384", 4) == 0) {
        res = fdsha384(file_name, block_size);
        sha_len = SHA384_DIGEST_LENGTH;
    }
    else if (strncmp(hash_algo, "sha512", 4) == 0) {
        res = fdsha512(file_name, block_size);
        sha_len = SHA512_DIGEST_LENGTH;
    }
    else {
        mprintf("sha algorithm not supported: %s\n", hash_algo);
        exit(-1);
    }

    mprintf("%s (%s): ", hash_algo, file_name);
    for (int i = 0; i < sha_len; i++) {
        printf("%02x", res[i]);
    }
    printf("\n");

    free(res);

    return 0;
}

static int load(int cmd, void *extra)
{
    int erro = 0;
    switch (cmd) {
        case MOD_LOAD:
            mprintf("Hashfile module installed\n");
            break;
        case MOD_UNLOAD:
            mprintf("Hashfile module uninstalled\n");
            break;
        default:
            erro = -1;
            break;
    }
    return 0;
}

const struct command_data hashfile_data = {
    .name = "hashfile",
    .desc = "Hashfile is cmd tool manage loaded modules.",
    .evh = hashfile};

COMMAND_MODULE(hashfile, &hashfile_data, load, NULL, NULL);

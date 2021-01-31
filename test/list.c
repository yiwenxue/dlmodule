#include "../include/list.h"
#include <stdio.h>
#include <stdlib.h>

struct integer{
    int data;
    LIST_ENTRY(integer) int_l;
};

int main(int argc, char *argv[])
{
    LIST_HEAD(integer_h, integer) mylisthead;
    LIST_INIT(&mylisthead);
    LIST_HEAD_INSPECTOR(&mylisthead);
    struct integer var1 = {50, {NULL, NULL}};
    struct integer var2 = {50, {NULL, NULL}};
    struct integer var3 = {50, {NULL, NULL}};
    LIST_INSERT_NULL(&mylisthead, &var1, int_l);
    LIST_INSERT_TAIL(&mylisthead, &var2, int_l);
    LIST_INSERT_TAIL(&mylisthead, &var3, int_l);

    LIST_HEAD_INSPECTOR(&mylisthead);
    LIST_ELM_INSPECTOR(&var1, &mylisthead, integer, int_l);
    LIST_ELM_INSPECTOR(&var2, &mylisthead, integer, int_l);
    LIST_ELM_INSPECTOR(&var3, &mylisthead, integer, int_l);


    LIST_SWAP_ELM(&var1, &var3, &mylisthead, integer, int_l);
    /* LIST_REMOVE(&var2, &mylisthead, integer, int_l); */
    /* LIST_INIT(&mylisthead); */

    LIST_HEAD_INSPECTOR(&mylisthead);
    LIST_ELM_INSPECTOR(&var1, &mylisthead, integer, int_l);
    LIST_ELM_INSPECTOR(&var2, &mylisthead, integer, int_l);
    LIST_ELM_INSPECTOR(&var3, &mylisthead, integer, int_l);

    LIST_CHECK_HEAD(&mylisthead, int_l);
    LIST_CHECK_FRONT(&mylisthead, int_l);
    LIST_CHECK_TAIL(&mylisthead, int_l);

    LIST_CHECK_PREV(&var1, &mylisthead, integer, int_l);
    LIST_CHECK_NEXT(&var1, int_l);
    LIST_CHECK_PREV(&var1, &mylisthead, integer, int_l);
    LIST_CHECK_NEXT(&var1, int_l);
    LIST_CHECK_PREV(&var1, &mylisthead, integer, int_l);
    LIST_CHECK_NEXT(&var1, int_l);

    return 0;
}

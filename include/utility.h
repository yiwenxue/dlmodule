#pragma once
#ifndef YIWEN_DATA_STRUCTURE_UTILITY
#define YIWEN_DATA_STRUCTURE_UTILITY
#include <stdlib.h>

#define panic(str, arg)    do{                          \
    fprintf(stderr, "panic:" str, arg);                 \
    exit(-1);                                           \
} while (0)

/**
 * A macro to determine the offset from the container to
 * the element. 
 *
 * @type : the type of container
 * @elm  : the element in the container
 *
 * value : the offset in size_t type 
 *
 * */
#define offset_of(type, elm)                            \
    ((size_t) &(((type *)0)->elm))

/**
 * A macro to determine the pointer to container of an element
 * in data structure. 
 *
 * @ptr : the pointer to the data pointer in a data structure
 * @type: the type of container 
 * @elm : the element in the container
 *
 * value: a pointer to the container 
 *
 * */
#define container_of(ptr, type, elm) ({                 \
    const typeof(((type *)0)->elm) * __mptr = (ptr);    \
    (type *)((char *)__mptr - offset_of(type, elm)); })

#endif 

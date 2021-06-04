/* A simple double linked list written with preprocessors
Copyright © 2021 yiwenxue
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.
3. All advertising materials mentioning features or use of this software
must display the following acknowledgement:
This product includes software developed by the yiwenxue.
4. Neither the name of the yiwenxue nor the
names of its contributors may be used to endorse or promote products
derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY yiwen ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL yiwenxue BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once
#ifndef YIWEN_DL_LIST
#define YIWEN_DL_LIST

#include "utility.h"

/* A method to create head for every list. It wil give you a 
 * struct contains a pointer to first and the last element in 
 * this list.
 *
 * @name: the name of the list
 * @type: the type of elements the list will contain
 * */
#define LIST_HEAD(name, type)                           \
struct name {                                           \
    struct type *lh_first; /* first element */          \
    struct type *lh_last;  /* last element */           \
}

#define LIST_HEAD_INITIALIZER(head)                     \
{ NULL }

/* Return the first element of this header. 
 * */
#define LIST_FIRST(head)                                \
    ((head)->lh_first)

/* Return the last element of this header.
 * */
#define LIST_LAST(head)                                 \
    ((head)->lh_last)

/* Init the list header, just set the pointers to null.
 * */
#define	LIST_INIT(head) do {						    \
    LIST_FIRST((head)) = NULL;					        \
    LIST_LAST((head)) = NULL;                           \
} while (0)

/* The entry point for each node, it should be embedded into the
 * data struct.
 * */
#define LIST_ENTRY(type)                                \
struct {                                                \
    struct type *le_next;                               \
    struct type **le_prev;                              \
}

/* Return the next element of the current one. If the current 
 * element is the last one, a NULL pointer will be returned. */
#define LIST_NEXT(elm, field)                           \
    ((elm)->field.le_next)

/* Return the previous element of the current, if the current is
 * the first element, return NULL. 
 * */
#define LIST_PREV(elm, head, type, field)               \
    ((elm)->field.le_prev == &LIST_FIRST(head)) ? NULL: \
    container_of((elm)->field.le_prev,                  \
           struct type, field.le_next)

/* Traverse the list from the begining with a unsafe method.
 * The pointer to the next element may lost the current element 
 * remove from list, and then be freed. */
#define LIST_FOREACH(var, head, field)                  \
    for((var) = LIST_FIRST(head);                       \
        (var);                                          \
        (var) = LIST_NEXT((var), field))

/* Traverse the list from the begining with a safe method.
 * Use an extra tvar to record the next elemnt before remove the
 * current one. */
#define LIST_FOREACH_SAFE(var, head, field, tvar)       \
    for((var) = LIST_FIRST(head);                       \
        (var) && ((tvar) = LIST_NEXT((var), field),1);  \
        (var) = (tvar))

/* Traverse the list from a specific element with a unsafe method.
 * If the current element is invalid, start from the begining in stead.
 * The pointer to the next element may lost the current element 
 * remove from list, and then be freed. */
#define LIST_FOREACH_FROM(var, head, field)             \
    for((var) = ((var)? (var) : LIST_FIRST(head));      \
        (var);                                          \
        (var) = LIST_NEXT((var), field))

/* Traverse the list from a specific element with a safe method.
 * If the current element is invalid, start from the begining in stead.
 * Use an extra tvar to record the next elemnt before remove the
 * current one. */
#define LIST_FOREACH_FROM_SAFE(var, head, field, tvar)  \
    for((var) = ((var)? (var) : LIST_FIRST(head));      \
        (var) && ((tvar) = LIST_NEXT((var), field),1);  \
        (var) = (tvar))

/* Insert an element after a specific element. If you have the 
 * pointer to this element, it will be super convinent. 
 * */
#define LIST_INSERT_AFTER(listelm, elm, field)  do{     \
    if((LIST_NEXT(elm, field) = LIST_NEXT(listelm, field)\
            )!= NULL){                                  \
        LIST_NEXT(listelm, field)->field.le_prev        \
        = &LIST_NEXT(elm, field);                       \
    }                                                   \
    LIST_NEXT(listelm, field) = (elm);                  \
    (elm)->field.le_prev = &LIST_NEXT(listelm, field);  \
} while (0)

#define LIST_CHECK_HEAD(head, field) do {                    \
    if (LIST_FIRST(head) == NULL|| LIST_LAST(head) == NULL)  \
        if (LIST_FIRST(head) != LIST_LAST(head))             \
            panic("Bad null list %p: only one of the front and tail is null.", (head));\
} while (0)

#define LIST_CHECK_FRONT(head, field) do {              \
    if (LIST_FIRST(head) != NULL &&                     \
           LIST_FIRST(head)->field.le_prev !=           \
              &LIST_FIRST(head))                        \
        panic("Bad list front %p first->prev != head", (head));\
} while (0)

#define LIST_CHECK_TAIL(head, field) do {               \
    if (LIST_LAST(head) != NULL &&                      \
            LIST_LAST(head)->field.le_next != NULL)     \
        panic("Bad list tail %p last->next != NULL", (head));\
} while (0)

/**
 * Insert and element at the begining of the list. It will 
 * chech the validation of the header at the begining. 
 *
 * @head : head of the list
 * @elm  : the new element to insert
 * @field: the region of the data struct
 * */
#define LIST_INSERT_HEAD(head, elm, field) do {         \
    LIST_CHECK_HEAD(head, field);                       \
    if (LIST_FIRST(head) != NULL) {                     \
        LIST_CHECK_FRONT(head, field);                  \
        if (elm == LIST_FIRST(head)) break;             \
        (elm)->field.le_next = LIST_FIRST(head);        \
        LIST_FIRST(head)->field.le_prev = &LIST_NEXT(elm, field);\
        LIST_FIRST(head) = (elm);                       \
        (elm)->field.le_prev = &LIST_FIRST(head);       \
    } else LIST_INSERT_NULL(head, elm, field);          \
} while (0)

/**
 * Insert and element at the begining of the list. It will 
 * chech the validation of the header at the begining. 
 *
 * @head : head of the list
 * @elm  : the new element to insert
 * @field: the region of the data struct
 * */
#define LIST_INSERT_TAIL(head, elm, field) do {                  \
    LIST_CHECK_HEAD(head, field);                               \
    if (LIST_LAST(head) != NULL){                               \
        LIST_CHECK_TAIL(head, field);                           \
        if (elm == LIST_LAST(head)) break;                      \
        LIST_LAST(head)->field.le_next = (elm);                 \
        (elm)->field.le_prev = &(LIST_LAST(head)->field.le_next);\
        LIST_LAST(head) = (elm);                                \
        (elm)->field.le_next = NULL;                            \
    } else LIST_INSERT_NULL(head, elm, field);                  \
} while (0)

#define LIST_INSERT_NULL(head, elm, field) do { \
    LIST_FIRST(head) = (elm);                   \
    LIST_LAST(head) = (elm);                    \
    (elm)->field.le_prev = &LIST_FIRST(head);   \
    (elm)->field.le_next = NULL;                \
} while (0)

#define LIST_HEAD_INSPECTOR(head) do {                  \
    fprintf(stderr, "Inspector: header %p: {%p, %p}\n", \
            (head), LIST_FIRST(head), LIST_LAST(head)); \
} while (0)

#define LIST_ELM_INSPECTOR(elm, head, type, field) do {        \
    fprintf(stderr, "Inspector: elm    %p: entry->{%p, %p}\n", \
            (elm), (elm)->field.le_prev, (elm)->field.le_next);\
} while (0)

#define LIST_CHECK_PREV(elm, head, type, field) do {                    \
    struct type * __ptr = LIST_PREV(elm, head, type, field);            \
    if (__ptr != NULL ) { if ((__ptr)->field.le_next != (elm))          \
            panic("Bad list prev %p prev->next != current", elm);}      \
    else if (LIST_FIRST(head) != (elm))                                 \
            panic("Bad list head prev %p prev->next != current", elm);       \
} while (0)

#define LIST_CHECK_NEXT(elm, field) do {                    \
    if (LIST_NEXT(elm, field) != NULL &&                    \
            LIST_NEXT(elm,field)->field.le_prev             \
            != &LIST_NEXT(elm, field))                      \
        panic("Bad list next %p next->prev != current", elm);\
} while (0)

/**
 * LIST_REMOVE: A Macro to revome an element from the list
 *  The case of head of list should be considered
 * */
#define LIST_REMOVE(elm, head, type, field) do {        \
    if(LIST_NEXT(elm, field) != NULL)                   \
        LIST_NEXT(elm, field)->field.le_prev            \
            =  (elm)->field.le_prev;                    \
    else LIST_LAST(head) = LIST_PREV(elm, head, type, field); \
    *(elm)->field.le_prev = LIST_NEXT(elm, field);      \
} while (0)

/* ToDo. Comeon, solve this fucking shit. */
#define LIST_SWAP_ELM(elm1, elm2, head, type, field) do {   \
    if (LIST_NEXT(elm1, field) == (elm2)) {             \
        *((elm1)->field.le_prev) = (elm2);                 \
        (elm2)->field.le_prev = (elm1)->field.le_prev;    \
        (elm1)->field.le_prev = &LIST_NEXT(elm2, field); \
        LIST_NEXT(elm1, field) = LIST_NEXT(elm2, field);\
        if (LIST_NEXT(elm2, field)) LIST_NEXT(elm2, field)->field.le_prev = &LIST_NEXT(elm1, field);\
        LIST_NEXT(elm2, field) = (elm1);                \
    } else if (LIST_NEXT(elm2, field) == (elm1)) {      \
        *((elm2)->field.le_prev) = (elm1);                 \
        (elm1)->field.le_prev = (elm2)->field.le_prev;    \
        (elm2)->field.le_prev = &LIST_NEXT(elm1, field); \
        LIST_NEXT(elm2, field) = LIST_NEXT(elm1, field);\
        if (LIST_NEXT(elm1, field)) LIST_NEXT(elm1, field)->field.le_prev = &LIST_NEXT(elm2, field);\
        LIST_NEXT(elm1, field) = (elm2);                \
    } else {                                            \
        *((elm1)->field.le_prev) = (elm2);                 \
        *((elm2)->field.le_prev) = (elm1);                 \
        struct type ** varp = (elm1)->field.le_prev;    \
        struct type * varn = (elm1)->field.le_next;    \
        (elm1)->field.le_prev = (elm2)->field.le_prev;  \
        (elm2)->field.le_prev = (varp);                 \
        if (!LIST_NEXT(elm1, field)) {(LIST_NEXT(elm2, field))->field.le_prev = &LIST_NEXT(elm1, field);} \
        else if (!LIST_NEXT(elm2, field)) {(LIST_NEXT(elm1, field))->field.le_prev = &LIST_NEXT(elm2, field);} \
        else { (varp) =  (LIST_NEXT(elm2, field))->field.le_prev;\
            (LIST_NEXT(elm2, field))->field.le_prev = (LIST_NEXT(elm1, field))->field.le_prev;\
            (LIST_NEXT(elm1, field))->field.le_prev = (varp);} \
        LIST_NEXT(elm1, field) = LIST_NEXT(elm2, field);\
        LIST_NEXT(elm2, field) = (varn);                \
    }                                                   \
    if (LIST_LAST(head) == (elm1)) LIST_LAST(head) = (elm2);\
    else if (LIST_LAST(head) == (elm2)) LIST_LAST(head) = (elm1);\
} while (0)

/**
 * Swap the header of two lists. 
 * */
#define LIST_SWAP(head1, head2, type, field) do {       \
    struct type * swap_tmp = LIST_FIRST(head1);         \
    LIST_FIRST((head1)) = LIST_FIRST((head2));          \
    LIST_FIRST((head2)) = swap_tmp;                     \
    if ((swap_tmp = LIST_FIRST((head1))) != NULL)       \
        swap_tmp->field.le_prev = &LIST_FIRST((head1)); \
    if ((swap_tmp = LIST_FIRST((head2))) != NULL)       \
        swap_tmp->field.le_prev = &LIST_FIRST((head2)); \
} while (0)

#define LIST_CONCAT(head1, head2, type, field) do {             \
    struct type *currelm = LIST_FIRST(head1);                   \
    if (currelm == NULL) {                                      \
        if ((LIST_FIRST(head1) = LIST_FIRST(head2)) != NULL) {  \
            LIST_FIRST(head2)->field.le_prev =                  \
                &LIST_FIRST(head1);                             \
            LIST_INIT(head2);                                   \
        }                                                       \
    } else if (LIST_HEAD(head2) != NULL) {                      \
        while (LIST_NEXT(currelm, field) != NULL)               \
            currelm = LIST_NEXT(currelm, field)                 \
        LIST_NEXT(currelm, field) = LIST_FIRST(head2);          \
        LIST_FIRST(head2)->field.le_prev = &LIST_NEXT(currelm, field)\
        LIST_INIT(HEAD);                                        \
    }                                                           \
} while (0)

#endif

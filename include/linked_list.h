#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>

#define linked_list_define(T)     \
    typedef struct ___Node_##T    \
    {                             \
        T value;                  \
        struct ___Node_##T *next; \
        struct ___Node_##T *prev; \
    } ___Node_##T;                \
    typedef struct LinkList_##T   \
    {                             \
        ___Node_##T *front;       \
        ___Node_##T *back;        \
        int size;                 \
    } LinkList_##T

#define linked_list_init { \
    .front = NULL,         \
    .back = NULL,          \
    .size = 0,             \
}

#define ___linked_list_node_init \
    (typeof(*list.front))        \
    {                            \
        .next = NULL,            \
        .prev = NULL,            \
    }

#define linked_list_push(list, _value)                             \
    do                                                             \
    {                                                              \
        if (list.size == 0)                                        \
        {                                                          \
            list.front = malloc(sizeof(typeof(*list.front)));      \
            *list.front = ___linked_list_node_init;                \
            list.back = list.front;                                \
            list.front->value = _value;                            \
        }                                                          \
        else                                                       \
        {                                                          \
            list.back->next = malloc(sizeof(typeof(*list.front))); \
            *list.back->next = ___linked_list_node_init;           \
            list.back->next->prev = list.back;                     \
            list.back = list.back->next;                           \
            list.back->value = _value;                             \
        }                                                          \
        list.size++;                                               \
    } while (0)

#define linked_list_pop(list) ({                         \
    if (list.size == 0)                                  \
    {                                                    \
        printf("Nothing to pop");                        \
        exit(1);                                         \
    }                                                    \
    typeof(list.front->value) ___ret = list.back->value; \
    typeof(list.back) ___removed_node = list.back;       \
    list.back = list.back->prev;                         \
    free(___removed_node);                               \
    list.size--;                                         \
    if (list.size != 0)                                  \
        list.back->next = NULL;                          \
    ___ret;                                              \
})

#define linked_list_peek(list) (list.back->value)


#endif

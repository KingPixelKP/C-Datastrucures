#ifndef LIST_H
#define LIST_H
#include <stdlib.h>
#define list_define(T)       \
    typedef struct UList_##T \
    {                        \
        T *array;            \
        int size;            \
        int capacity;        \
    } UList_##T

#define list_init { \
    .array = {0},   \
    .size = 0,      \
    .capacity = 0,  \
}

#define list_push(list, value)                                                     \
    do                                                                             \
    {                                                                              \
        if (list.size >= list.capacity)                                            \
        {                                                                          \
            if (list.capacity == 0)                                                \
                list.capacity = 256;                                               \
            else                                                                   \
                list.capacity *= 2;                                                \
            list.array = realloc(list.array, list.capacity * sizeof(*list.array)); \
        }                                                                          \
        list.array[list.size++] = value;                                           \
    } while (0)

#define list_remove(list, index)                         \
    do                                                   \
    {                                                    \
        if (index == list.size - 1)                      \
            list.size--;                                 \
        else                                             \
        {                                                \
            list.array[index] = list.array[--list.size]; \
        }                                                \
    } while (0)

#define list_free(list)   \
    do                    \
    {                     \
        free(list.array); \
    } while (0)

#endif
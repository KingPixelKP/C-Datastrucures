#ifndef LIST_H
#define LIST_H
#include <stdlib.h>
/**
 * Defines a list of type T
 */
#define list_define(T)       \
    typedef struct UList_##T \
    {                        \
        T *array;            \
        int size;            \
        int capacity;        \
    } UList_##T

/**
 * Inits the list
 */
#define list_init { \
    .array = {0},   \
    .size = 0,      \
    .capacity = 0,  \
}

/**
 * Pushes a value onto the list
 */
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

/**
 * Removes a value from the list, WILL NOT MANTAIN ORDER
 */
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

/**
 * Frees all memory the list used
 */
#define list_free(list)   \
    do                    \
    {                     \
        free(list.array); \
    } while (0)

#endif
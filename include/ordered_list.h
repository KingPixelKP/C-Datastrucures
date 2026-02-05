#ifndef O_LIST_H
/**
 * This list is not sorted its values will not be sorted, this list only makes sure that the values stay in their insertion order
 */
#define O_LIST_H
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * Defines an ordered list of type T
 */
#define olist_define(T)      \
    typedef struct Olist_##T \
    {                        \
        T *array;            \
        int size;            \
        int capacity;        \
    } OList_##T

/**
 * Inits the list
 */
#define olist_init { \
    .array = NULL,   \
    .size = 0,       \
    .capacity = 0,   \
}

/**
 * Check if the index is within bounds of the list
 */
#define ___olist_check_bounds(list, index)   \
    {                                        \
        if (index >= list.size)              \
        {                                    \
            printf("Index out of bounds\n"); \
            exit(1);                         \
        }                                    \
    }

/**
 * Pushes a value onto the list
 */
#define olist_push(list, value)                                                    \
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
 * Pops the last value of the list
 */
#define olist_pop(list) (list.array[--list.size])

/**
 * Peeks the last value of the list
 */
#define olist_peek(list) (list.array[list.size - 1])

/**
 * Inserts an element at the index position of the list
 */
#define olist_insert(list, index, value)                                                                      \
    do                                                                                                        \
    {                                                                                                         \
        if (list.size >= list.capacity)                                                                       \
        {                                                                                                     \
            if (list.capacity == 0)                                                                           \
                list.capacity = 256;                                                                          \
            else                                                                                              \
                list.capacity *= 2;                                                                           \
            list.array = realloc(list.array, list.capacity * sizeof(*list.array));                            \
        }                                                                                                     \
        if (list.size == index)                                                                               \
            olist_push(list, value);                                                                          \
        else                                                                                                  \
        {                                                                                                     \
            ___olist_check_bounds(list, index);                                                               \
            memmove(&list.array[index + 1], &list.array[index], sizeof(*list.array) * list.size - index - 1); \
            list.array[index] = value;                                                                        \
            list.size++;                                                                                      \
        }                                                                                                     \
    } while (0)

/**
 * Removes a value from the list, WILL NOT MANTAIN ORDER
 */
#define olist_remove(list, index)                                                                                     \
    do                                                                                                                \
    {                                                                                                                 \
        ___olist_check_bounds(list, index);                                                                           \
        if (index == list.size - 1)                                                                                   \
            list.size--;                                                                                              \
        else                                                                                                          \
        {                                                                                                             \
            memmove(&list.array[index], &list.array[index + 1], sizeof(typeof(*list.array)) * list.size - index - 1); \
            list.size--;                                                                                              \
        }                                                                                                             \
    } while (0);

/**
 * Gets the value at the indexes position
 */
#define olist_get(list, index) ({       \
    ___olist_check_bounds(list, index); \
    list.array[index];                  \
})

/**
 * Frees all memory the list used
 */
#define olist_free(list)  \
    do                    \
    {                     \
        free(list.array); \
    } while (0)

#endif
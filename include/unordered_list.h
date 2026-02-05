#ifndef UNO_LIST_H
#define UNO_LIST_H
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

/**
 * Defines an unordered list of type T
 */
#define ulist_define(T)      \
    typedef struct UList_##T \
    {                        \
        T *array;            \
        int size;            \
        int capacity;        \
    } UList_##T

/**
 * Defines a list of type T with name name
 */
#define ulist_define_name(T, name) \
    typedef struct name            \
    {                              \
        T *array;                  \
        int size;                  \
        int capacity;              \
    } name

/**
 * Inits the list
 */
#define ulist_init { \
    .array = NULL,   \
    .size = 0,       \
    .capacity = 0,   \
}

/**
 * Check if the index is within bounds of the list
 */
#define ___ulist_check_bounds(list, index)   \
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
#define ulist_push(list, value)                                                    \
    do                                                                             \
    {                                                                              \
        if (list.size >= list.capacity)                                            \
        {                                                                          \
            if (list.capacity == 0)                                                \
                list.capacity = 256;                                               \
            else                                                                   \
                list.capacity *= 2;                                                \
            list.array = realloc(list.array, list.capacity * sizeof(*list.array)); \
            if (!list.array)                                                       \
            {                                                                      \
                printf("Rellocation error!\n");                                    \
                exit(1);                                                           \
            }                                                                      \
        }                                                                          \
        list.array[list.size++] = value;                                           \
    } while (0)

/**
 * Pops the last value of the list
 */
#define ulist_pop(list) (list.array[--list.size])

/**
 * Peeks the last value of the list
 */
#define ulist_peek(list) (list.array[list.size - 1])

/**
 * Inserts an element at the index position of the list
 */
#define ulist_insert(list, index, value)                                                                      \
    do                                                                                                        \
    {                                                                                                         \
        if (list.size >= list.capacity)                                                                       \
        {                                                                                                     \
            if (list.capacity == 0)                                                                           \
                list.capacity = 256;                                                                          \
            else                                                                                              \
                list.capacity *= 2;                                                                           \
            list.array = realloc(list.array, list.capacity * sizeof(*list.array));                            \
            if (!list.array)                                                                                  \
            {                                                                                                 \
                printf("Rellocation error!\n");                                                               \
                exit(1);                                                                                      \
            }                                                                                                 \
        }                                                                                                     \
        if (list.size == index)                                                                               \
            ulist_push(list, value);                                                                          \
        else                                                                                                  \
        {                                                                                                     \
            ___ulist_check_bounds(list, index);                                                               \
            memmove(&list.array[index + 1], &list.array[index], sizeof(*list.array) * list.size - index - 1); \
            list.array[index] = value;                                                                        \
            list.size++;                                                                                      \
        }                                                                                                     \
    } while (0)

/**
 * Removes a value from the list, WILL NOT MANTAIN ORDER
 */
#define ulist_remove(list, index)                        \
    do                                                   \
    {                                                    \
        ___ulist_check_bounds(list, index);              \
        if (index == list.size - 1)                      \
            list.size--;                                 \
        else                                             \
        {                                                \
            list.array[index] = list.array[--list.size]; \
        }                                                \
    } while (0)

/**
 * Gets the value at the indexes position
 */
#define ulist_get(list, index) ({       \
    ___ulist_check_bounds(list, index); \
    list.array[index];                  \
})

/**
 * Frees all memory the list used
 */
#define ulist_free(list)  \
    do                    \
    {                     \
        free(list.array); \
    } while (0)

#endif
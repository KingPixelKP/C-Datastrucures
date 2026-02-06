#ifndef BITSET_H
#define BITSET_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct BitSet
{
    char *array;
    int size;
} BitSet;

#define bit_set_init(_size)                                     \
    (BitSet)                                                    \
    {                                                           \
        .array = malloc((_size + sizeof(char) / sizeof(char))), \
        .size = _size,                                          \
    }

#define ___bit_set_check_bounds(bit_set, n)             \
    {                                                   \
        if (n > bit_set.size)                           \
        {                                               \
            printf("Cannot set bit outside of size\n"); \
            exit(1);                                    \
        }                                               \
    }

#define ___bit_set_get_word(bit_set, n) (bit_set.array[n / sizeof(char)])

#define ___bit_set_set_word(bit_set, n, word)   \
    do                                          \
    {                                           \
        bit_set.array[n / sizeof(char)] = word; \
    } while (0)

#define bit_set_set(bit_set, n)                                                              \
    do                                                                                       \
    {                                                                                        \
        ___bit_set_check_bounds(bit_set, n);                                                 \
        ___bit_set_set_word(bit_set, n, (___bit_set_get_word(bit_set, n) | (1 << (n % 8)))); \
    } while (0)

#define bit_set_clear(bit_set, n)                                                             \
    do                                                                                        \
    {                                                                                         \
        ___bit_set_check_bounds(bit_set, n);                                                  \
        ___bit_set_set_word(bit_set, n, (___bit_set_get_word(bit_set, n) & ~(1 << (n % 8)))); \
    } while (0)

#define bit_set_toggle(bit_set, n)                                                           \
    do                                                                                       \
    {                                                                                        \
        ___bit_set_check_bounds(bit_set, n);                                                 \
        ___bit_set_set_word(bit_set, n, (___bit_set_get_word(bit_set, n) ^ (1 << (n % 8)))); \
    } while (0)

#define bit_set_get(bit_set, n) ({                    \
    ___bit_set_check_bounds(bit_set, n);              \
    (___bit_set_get_word(bit_set, n) >> (n % 8)) & 1; \
})

#endif
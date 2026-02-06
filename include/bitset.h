#ifndef BITSET_H
#define BITSET_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef BITSET_SIZE
#define BITSET_SIZE 128
#endif

typedef struct BitSet
{
    char array[BITSET_SIZE / 8];
} BitSet;

#define bit_set_init  \
    (BitSet)          \
    {                 \
        .array = {0}, \
    }

#define ___bit_set_check_bounds(bit_set, n)             \
    {                                                   \
        if (n > BITSET_SIZE)                            \
        {                                               \
            printf("Cannot set bit outside of size\n"); \
            exit(1);                                    \
        }                                               \
    }

#define ___bit_set_get_word(bit_set, n) (bit_set.array[n / 8])

#define ___bit_set_set_word(bit_set, n, word)   \
    do                                          \
    {                                           \
        bit_set.array[n / 8] = word; \
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
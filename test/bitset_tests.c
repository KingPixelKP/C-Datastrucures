#define BITSET_SIZE 128
#include "bitset.h"
#include <assert.h>
#include <stdio.h>

int main()
{
    BitSet set = bit_set_init;
    for (int i = 0; i < 128; i++)
    {
        printf("\\ %d:%d\n",i, i / 8);
        printf("%% %d:%d\n",i, i % 8);
    }
    for (int i = 0; i < 99; i++)
    {
        printf("I:%d: %u\n", i, bit_set_get(set, i) ? 1 : 0);
        assert(!bit_set_get(set, i));
    }
    for (int i = 0; i < 99; i++)
    {
        printf("Setting %i\n", i);
        bit_set_set(set, i);
    }
    for (int i = 0; i < 99; i++)
    {
        printf("I:%d: %u\n", i, bit_set_get(set, i) ? 1 : 0);
        assert(bit_set_get(set, i));
    }
    for (int i = 0; i < 99; i++)
    {
        if (i % 2 == 0)
        {
            printf("Clearing %i\n", i);
            bit_set_clear(set, i);
        }
    }
    for (int i = 0; i < 99; i++)
    {
        if (i % 2 != 0)
        {
            printf("I:%d: %u\n", i, bit_set_get(set, i) ? 1 : 0);
            assert(bit_set_get(set, i));
        }
        if (i % 2 == 0)
        {
            printf("I:%d: %u\n", i, bit_set_get(set, i) ? 1 : 0);
            assert(!bit_set_get(set, i));
        }
    }
    for (int i = 0; i < 99; i++)
    {
        printf("Toggling %i\n", i);
        bit_set_toggle(set, i);
    }
    for (int i = 0; i < 99; i++)
    {
        if (i % 2 == 0)
        {
            printf("I:%d: %u\n", i, bit_set_get(set, i) ? 1 : 0);
            assert(bit_set_get(set, i));
        }
        if (i % 2 != 0)
        {
            printf("I:%d: %u\n", i, bit_set_get(set, i) ? 1 : 0);
            assert(!bit_set_get(set, i));
        }
    }
}
#include "bitset.h"
#include <assert.h>
#include <stdio.h>

int main()
{
    BitSet set = bit_set_init(99);
    assert(set.size == 99);
    for (int i = 0; i < 99; i++)
    {
        bit_set_set(set, i);
    }
    for (int i = 0; i < 99; i++)
    {
        assert(bit_set_get(set, i));
    }
    for (int i = 0; i < 99; i++)
    {
        if (i % 2 == 0)
            bit_set_clear(set, i);
    }
    for (int i = 0; i < 99; i++)
    {
        if (i % 2 != 0)
            assert(bit_set_get(set, i));
        if (i % 2 == 0)
            assert(!bit_set_get(set, i));
    }
    for (int i = 0; i < 99; i++)
    {
        bit_set_toggle(set, i);
    }
    for (int i = 0; i < 99; i++)
    {
        if (i % 2 == 0)
            assert(bit_set_get(set, i));
        if (i % 2 != 0)
            assert(!bit_set_get(set, i));
    }
}
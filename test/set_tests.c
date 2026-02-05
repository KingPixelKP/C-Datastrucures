#include "set.h"
#include "default_funcitons.h"
#include <stdio.h>
#include <assert.h>

set_define(int);

int main()
{
    Set_int set = set_init(intEqualFn);

    assert(set_size(set) == 0);
    for (int i = 0; i < 512; i++)
    {
        printf("Adding %d\n", i);
        set_add(set, i);
    }
    assert(set_size(set) == 512);
    for (int i = 0; i < 512; i++)
    {
        printf("Adding dupped %d\n", i);
        set_add(set, i);
    }
    assert(set_size(set) == 512);
    for (int i = 0; i < 512; i++)
    {
        printf("Set has %d", i);
        assert(set_has(set, i));
    }
    assert(set_size(set) == 512);
    for (int i = 0; i < 512; i++)
    {
        printf("Set get index %d", i);
        assert(set_get(set, i) == i);
    }
    assert(set_size(set) == 512);
    for (int i = 0; i < 512; i++)
    {
        printf("remove %d", i);
        set_remove(set, i);
    }
    assert(set_size(set) == 0);

    return 0;
}
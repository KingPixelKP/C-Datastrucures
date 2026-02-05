#include "packed_array.h"
#include <assert.h>
#include <stdio.h>

packed_array_define(int);

int main()
{
    PArray_int array = packed_array_init;
    assert(array.size == 0);
    for (int i = 0; i < 512; i++)
    {
        printf("pushing %d\n", i);
        packed_array_push(array, i, i);
    }
    assert(array.size == 512);
    for (int i = 0; i < 512; i++)
    {
        printf("removing %d\n", i);
        packed_array_remove_entity(array, i);
    }
    assert(array.size == 0);
    for (int i = 0; i < 512; i++)
    {
        printf("pushing %d\n", i);
        packed_array_push(array, i, i);
    }
    assert(array.size == 512);
    for (int i = 0; i < 512; i++)
    {
        printf("checking index %d\n", i);
        assert(packed_array_has_index(array,i));
        assert(packed_array_has_entity(array,i));
        assert(packed_array_get_index(array,i) != -1);
        assert(packed_array_get_entity(array,i) != -1);
    }
}
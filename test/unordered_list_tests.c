#include "unordered_list.h"
#include <assert.h>
#include <stdio.h>

ulist_define(int);

int main()
{
    UList_int list = ulist_init;
    for (int i = 0; i < 2048; i++)
    {
        printf("Inserting %d\n", i);
        ulist_push(list, i);
    }
    assert(list.size == 2048);
    for (int i = 0; i < 2048; i++)
    {
        printf("Getting %d\n", i);
        assert(ulist_get(list, i) == i);
    }
    assert(list.size == 2048);
    for (int i = 2047; i >= 0; i--)
    {
        printf("Removing Index %d\n", i);
        ulist_remove(list, i);
    }
    assert(list.size == 0);
    for (int i = 0; i < 2048; i++)
    {
        printf("Inserting %d at 0\n", i);
        ulist_insert(list, 0, i);
    }
    assert(list.size == 2048);
    int j = 0;
    for (int i = 2047; i >= 0; i--)
    {
        printf("Geeting %d at index %d",j,i);
        assert(ulist_get(list, i) == j);
        j++;
    }
    assert(list.size == 2048);
    for (int i = 2047; i >= 0; i--)
    {
        printf("Removing Index 0\n");
        ulist_remove(list, 0);
    }
    assert(list.size == 0);
    for (int i = 0; i < 2048; i++)
    {
        printf("Inserting %d\n", i);
        ulist_push(list, i);
    }
    assert(list.size == 2048);
    for (int i = 2047; i >= 0; i--)
    {
        printf("Popping %d\n", i);
        assert(ulist_peek(list) == i);
        assert(ulist_pop(list) == i);
    }
    ulist_free(list);
}
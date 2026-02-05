#include "unordered_list.h"
#include <assert.h>
#include <stdio.h>

list_define(int);

int main()
{
    UList_int list = list_init;
    for (int i = 0; i < 2048; i++)
    {
        printf("Inserting %d\n", i);
        list_push(list, i);
    }
    assert(list.size == 2048);
    for (int i = 0; i < 2048; i++)
    {
        printf("Getting %d\n", i);
        assert(list_get(list, i) == i);
    }
    assert(list.size == 2048);
    for (int i = 2047; i >= 0; i--)
    {
        printf("Removing Index %d\n", i);
        list_remove(list, i);
    }
    assert(list.size == 0);
    for (int i = 0; i < 2048; i++)
    {
        printf("Inserting %d at 0\n", i);
        list_insert(list, 0, i);
    }
    assert(list.size == 2048);
    int j = 0;
    for (int i = 2047; i >= 0; i--)
    {
        printf("Geeting %d at index %d",j,i);
        assert(list_get(list, i) == j);
        j++;
    }
    assert(list.size == 2048);
    for (int i = 2047; i >= 0; i--)
    {
        printf("Removing Index 0\n");
        list_remove(list, 0);
    }
    assert(list.size == 0);
    for (int i = 0; i < 2048; i++)
    {
        printf("Inserting %d\n", i);
        list_push(list, i);
    }
    assert(list.size == 2048);
    for (int i = 2047; i >= 0; i--)
    {
        printf("Popping %d\n", i);
        assert(list_peek(list) == i);
        assert(list_pop(list) == i);
    }
    list_free(list);
}
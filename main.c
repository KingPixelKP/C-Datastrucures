#include "linked_list.h"
#include <assert.h>
#include <stdio.h>

linked_list_define(int);

int main()
{
    LinkList_int list = linked_list_init;
    for (int i = 0; i < 512; i++)
        linked_list_push(list, i);
    for (int i = 511; i >= 0; i--) {
        assert(linked_list_peek(list) == i);
        assert(linked_list_pop(list) == i);
    }
}

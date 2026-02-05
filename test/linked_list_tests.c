#include "linked_list.h"
#include <assert.h>
#include <stdio.h>

linked_list_define(int);

void rem(LinkList_int list, int index)
{
    typeof(list.front) ___to_remove = ___linked_list_get_node(list, index);
    list.size--;
    if (___to_remove->next)
        ___to_remove->next->prev = ___to_remove->prev;
    else
        list.back = ___to_remove->prev;
    if (___to_remove->prev)
        ___to_remove->prev->next = ___to_remove->next;
    else
        list.front = ___to_remove->next;
    free(___to_remove);
}

int main()
{
    LinkList_int list = linked_list_init;
    // Stack tests
    assert(list.size == 0);
    for (int i = 0; i < 512; i++)
    {
        printf("Pushing %d\n", i);
        linked_list_push_back(list, i);
    }
    assert(list.size == 512);
    for (int i = 511; i >= 0; i--)
    {
        printf("Peeking %d\n", i);
        assert(linked_list_peek_back(list) == i);
        printf("Popping %d\n", i);
        assert(linked_list_pop(list) == i);
    }
    assert(list.size == 0);
    // Queue tests
    for (int i = 0; i < 512; i++)
    {
        printf("Pusing %d\n", i);
        linked_list_push_back(list, i);
    }
    assert(list.size == 512);
    for (int i = 0; i < 512; i++)
    {
        printf("Peeking %d\n", i);
        assert(linked_list_peek_front(list) == i);
        printf("Popping %d\n", i);
        assert(linked_list_deque(list) == i);
    }
    assert(list.size == 0);
    for (int i = 0; i < 512; i++)
    {
        printf("Pushing %d\n", i);
        linked_list_push_back(list, i);
    }
    assert(list.size == 512);
    linked_list_push_back(list, 666);
    linked_list_push_front(list, 999);
    assert(list.size == 514);
    assert(linked_list_get(list, 513) == 666);
    assert(linked_list_get(list, 0) == 999);
    assert(linked_list_get(list, 128) == 127);
    linked_list_set(list, 128, 555);
    assert(list.size == 514);
    assert(linked_list_get(list, 128) == 555);
    linked_list_insert(list, 128, 9999);
    assert(list.size == 515);
    assert(linked_list_get(list, 128) == 9999);
    for (int i = 0; i < 515; i++)
    {
        printf("Removing 0\n");
        linked_list_remove(list, 0);
    }
    linked_list_free(list);
}

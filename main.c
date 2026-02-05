#include "linked_list.h"
#include <assert.h>
#include <stdio.h>

linked_list_define(int);

int main()
{
    LinkList_int list = linked_list_init;
    //Stack tests
    assert(list.size==0);
    for (int i = 0; i < 512; i++) {
        printf("Pushing %d\n",i);
        linked_list_push_back(list, i);
    }
    assert(list.size==512);
    for (int i = 511; i >= 0; i--) {
        printf("Peeking %d\n",i);
        assert(linked_list_peek_back(list) == i);
        printf("Popping %d\n",i);
        assert(linked_list_pop(list) == i);
    }
    assert(list.size==0);
    //Queue tests
    for (int i = 0; i < 512; i++) {
        printf("Pusing %d\n",i);
        linked_list_push_back(list, i);
    }
    assert(list.size==512);
    for (int i = 0; i < 512; i++) {
        printf("Peeking %d\n",i);
        assert(linked_list_peek_front(list) == i);
        printf("Popping %d\n",i);
        assert(linked_list_deque(list) == i);
    }
    assert(list.size==0);
    for (int i = 0; i < 512; i++) {
        printf("Pushing %d\n",i);
        linked_list_push_back(list, i);
    }
    assert(list.size==512);
    linked_list_push_back(list, 666);
    linked_list_push_front(list,999);
    assert(list.size==514);
    assert(linked_list_get(list, 513) == 666);
    assert(linked_list_get(list, 0) == 999);
    assert(linked_list_get(list, 128) == 129);
}

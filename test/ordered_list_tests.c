#include "ordered_list.h"
#include "hash_map.h"
#include <assert.h>

olist_define(int);

/**
 * Removes a value from the list, WILL NOT MANTAIN ORDER
 */
void rem(OList_int list, int index)
{
    do
    {
        ___olist_check_bounds(list, index);
        if (index == list.size - 1)
            list.size--;
        else
        {
            memmove(&list.array[index], &list.array[index + 1], list.size - index - 1);
            list.size--;
        }
    } while (0);
}

int main()
{
    OList_int list = olist_init;
    for (int i = 0; i < 512; i++)
    {
        olist_push(list, i);
    }

    assert(list.size == 512);
    olist_remove(list,0);
    assert(list.size == 511);

    for (int i = 0; i < 511; i++)
    {
        printf("Element at %d, %d, expected:%d\n", i, olist_get(list, i), i + 1);
        assert(olist_get(list, i) == i + 1);
    }
}
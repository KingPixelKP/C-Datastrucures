#include "search_tree.h"

search_tree_define(int, int);

int main()
{
    BSTree_intint tree = search_tree_init(intCmpFn);
    assert(tree.size == 0);
    search_tree_put(tree, 1, 1);
    assert(tree.size == 1);
    search_tree_put(tree, 1, 1);
    assert(tree.size == 1);
    search_tree_put(tree, 1, 1);
    assert(tree.size == 1);
    search_tree_get(tree, 1, 0);
    assert(tree.size == 1);
}
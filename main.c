#include "search_tree.h"

search_tree_define(int, int);

int main()
{
    BSTree_intint tree = search_tree_init(intCmpFn);
    search_tree_put(tree, 1, 1);
}
#include "unordered_list.h"
#include "hash_map.h"
#include <assert.h>

hash_map_define(int, int);

int hashFn(const int key) { return key; };
bool equalFn(const int key1, const int key2) { return key1 == key2; }

int main()
{
    UHMap_intint hash_map = hash_map_init(hashFn, equalFn);
    for (int i = 0; i < 512; i++)
        hash_map_put(hash_map, i, i);
    assert(hash_map.size == 512);
    for (int i = 0; i < 512; i++)
    {
        assert(hash_map_has(hash_map, i));
        assert(hash_map_get(hash_map, i) == i);
    }
}

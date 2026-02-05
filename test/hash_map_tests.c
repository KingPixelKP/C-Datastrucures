#include "hash_map.h"
#include <assert.h>

typedef struct Keyy
{
    int key;
    char cc;
} Keyy;

hash_map_define(Keyy, int);

int hashFn(const Keyy key) { return key.key; };
bool equalFn(const Keyy key1, const Keyy key2) { return key1.key == key2.key; }

int main()
{
    UHMap_Keyyint hash_map = hash_map_init(hashFn, equalFn);
    for (int i = 0; i < 512; i++)
    {
        Keyy d = {i, 'A'};
        hash_map_put(hash_map, d, i);
        printf("Inserted %d, %d\n", i, i);
    }
    printf("Hash_map's size %d\n", hash_map.size);
    assert(hash_map.size == 512);
    for (int i = 0; i < 512; i++)
    {
        Keyy d = {i, 'A'};
        printf("Hash_map has %d\n",i);
        assert(hash_map_has(hash_map, d));
        assert(hash_map_get(hash_map, d) == i);
    }
    for (int i = 0; i < 512; i++)
    {
        Keyy d = {i, 'A'};
        printf("Removing %d\n",i);
        hash_map_remove(hash_map, d);
    }
    assert(hash_map.size == 0);
    for (int i = 0; i < 512; i++)
    {
        Keyy d = {i, 'A'};
        printf("Hash_map no has %d\n",i);
        assert(!hash_map_has(hash_map, d));
    }
    hash_map_free(hash_map);
}

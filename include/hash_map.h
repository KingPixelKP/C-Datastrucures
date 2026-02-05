#ifndef HASH_MAP_H
#define HASH_MAP_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "unordered_list.h"

#define HASH_MAP_DEFAULT_SIZE 128

#define hash_map_define(K, V)                      \
    list_define_name(K, Bucket_##K);               \
    list_define_name(V, Bucket_##V);               \
    typedef struct UHMap_##T                       \
    {                                              \
        Bucket_##K *keys;                          \
        Bucket_##V *values;                        \
        int size;                                  \
        int capacity;                              \
        int (*hash)(const K key);                  \
        bool (*equal)(const K key1, const K key2); \
    } UHMap_##K##V

#define hash_map_init(hashFn, equalFn) \
    {                                  \
        .keys = NULL,                  \
        .values = NULL,                \
        .size = 0,                     \
        .capacity = 0,                 \
        .hash = hashFn,                \
        .equal = equalFn,              \
    }

#define ___hash_map_init_lists(hash_map)                                                              \
    typeof(hash_map.keys) ___keys = malloc(hash_map.capacity * sizeof(typeof(*hash_map.keys)));       \
    typeof(hash_map.values) ___values = malloc(hash_map.capacity * sizeof(typeof(*hash_map.values))); \
    for (int ___i = 0; ___i < hash_map.capacity; ___i++)                                              \
    {                                                                                                 \
        ___keys[___i] = (typeof(*hash_map.keys))list_init;                                            \
        ___values[___i] = (typeof(*hash_map.values))list_init;                                        \
    }

#define hash_map_free(hash_map)                     \
    {                                               \
        for (int i = 0; i < hash_map.capacity; i++) \
        {                                           \
            list_free(hash_map.keys[i]);            \
            list_free(hash_map.values[i]);          \
        }                                           \
        free(hash_map.keys);                        \
        free(hash_map.values);                      \
    }

#define hash_map_rehash_if_full(hash_map)                                                                           \
    {                                                                                                               \
        do                                                                                                          \
        {                                                                                                           \
            if (0.5 < (float)hash_map.size / (float)hash_map.capacity)                                              \
            {                                                                                                       \
                hash_map.capacity *= 2;                                                                             \
                ___hash_map_init_lists(hash_map) for (int ___i = 0; ___i < hash_map.capacity / 2; ___i++)           \
                {                                                                                                   \
                    for (int ___j = 0; ___j < hash_map.keys[___i].size; ___j++)                                     \
                    {                                                                                               \
                        int newIndex = abs(hash_map.hash(list_get(hash_map.keys[___i], ___j))) % hash_map.capacity; \
                        list_push(___keys[newIndex], list_get(hash_map.keys[___i],___j));                          \
                        list_push(___values[newIndex], list_get(hash_map.values[___i],___j));                        \
                    }                                                                                               \
                    list_free(hash_map.keys[___i]);                                                                 \
                    list_free(hash_map.values[___i]);                                                               \
                }                                                                                                   \
                free(hash_map.keys);                                                                                \
                free(hash_map.values);                                                                              \
                hash_map.keys = ___keys;                                                                            \
                hash_map.values = ___values;                                                                        \
            }                                                                                                       \
            else if (hash_map.capacity == 0)                                                                        \
            {                                                                                                       \
                hash_map.capacity = HASH_MAP_DEFAULT_SIZE;                                                          \
                ___hash_map_init_lists(hash_map)                                                                    \
                    hash_map.keys = ___keys;                                                                        \
                hash_map.values = ___values;                                                                        \
            }                                                                                                       \
        } while (0);                                                                                                \
    }

#define hash_map_put(hash_map, key, value)                                        \
    {                                                                             \
        do                                                                        \
        {                                                                         \
            hash_map_rehash_if_full(hash_map);                                    \
            int ___index = abs(hash_map.hash(key)) % hash_map.capacity;           \
            int ___i = 0;                                                         \
            while (___i < hash_map.keys[___index].size)                           \
            {                                                                     \
                if (hash_map.equal(list_get(hash_map.keys[___index], ___i), key)) \
                    hash_map.values[___index].array[___i] = value;                \
                ___i++;                                                           \
            }                                                                     \
            if (___i == hash_map.keys[___index].size)                             \
            {                                                                     \
                list_push(hash_map.keys[___index], key);                          \
                list_push(hash_map.values[___index], value);                      \
                hash_map.size++;                                                  \
            }                                                                     \
                                                                                  \
        } while (0);                                                              \
    }

#define hash_map_has(hash_map, key)                                                                                  \
    ({                                                                                                               \
        int ___index = abs(hash_map.hash(key)) % hash_map.capacity;                                                  \
        int ___i = 0;                                                                                                \
        while (___i < hash_map.keys[___index].size && !hash_map.equal(list_get(hash_map.keys[___index], ___i), key)) \
            ___i++;                                                                                                  \
        (___i < hash_map.keys[___index].size);                                                                       \
    })

#define hash_map_get(hash_map, key) (                                                                                \
    {                                                                                                                \
        int ___index = abs(hash_map.hash(key)) % hash_map.capacity;                                                  \
        int ___i = 0;                                                                                                \
        while (___i < hash_map.keys[___index].size && !hash_map.equal(list_get(hash_map.keys[___index], ___i), key)) \
            ___i++;                                                                                                  \
        (list_get(hash_map.values[___index], ___i));                                                                 \
    })

#define hash_map_remove(hash_map, key)                                                                               \
    {                                                                                                                \
        int ___index = hash_map.hash(key) % hash_map.capacity;                                                       \
        int ___i = 0;                                                                                                \
        while (___i < hash_map.keys[___index].size && !hash_map.equal(list_get(hash_map.keys[___index], ___i), key)) \
            ___i++;                                                                                                  \
        list_remove(hash_map.keys[___index], ___i);                                                                  \
        list_remove(hash_map.values[___index], ___i);                                                                \
        hash_map.size--;                                                                                             \
    }

#endif
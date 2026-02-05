#pragma once
#ifndef HASH_MAP_H
#define HASH_MAP_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "unordered_list.h"
#include "default_funcitons.h"

#define HASH_MAP_DEFAULT_SIZE 128

#define hash_map_define(K, V)                      \
    ulist_define_name(K, Bucket_##K);              \
    ulist_define_name(V, Bucket_##V);              \
    typedef struct UHMap_##K##V                    \
    {                                              \
        Bucket_##K *keys;                          \
        Bucket_##V *values;                        \
        int size;                                  \
        int capacity;                              \
        int (*hash)(const K key);                  \
        bool (*equal)(const K key1, const K key2); \
    } UHMap_##K##V

#define hash_map_define_name(K, V, name)           \
    ulist_define_name(K, Bucket_##K);              \
    ulist_define_name(V, Bucket_##V);              \
    typedef struct UHMap_##K##V                    \
    {                                              \
        Bucket_##K *keys;                          \
        Bucket_##V *values;                        \
        int size;                                  \
        int capacity;                              \
        int (*hash)(const K key);                  \
        bool (*equal)(const K key1, const K key2); \
    } name

#define hash_map_init(hashFn, equalFn) \
    {                                  \
        .keys = NULL,                  \
        .values = NULL,                \
        .size = 0,                     \
        .capacity = 0,                 \
        .hash = hashFn,                \
        .equal = equalFn,              \
    }

#define hash_map_init_intkey \
    {                        \
        .keys = NULL,        \
        .values = NULL,      \
        .size = 0,           \
        .capacity = 0,       \
        .hash = intHashFn,   \
        .equal = intEqualFn, \
    }
#define hash_map_init_strkey \
    {                        \
        .keys = NULL,        \
        .values = NULL,      \
        .size = 0,           \
        .capacity = 0,       \
        .hash = strHashFn,   \
        .equal = strEqualFn, \
    }

#define ___hash_map_init_ulists(hash_map)                                                             \
    typeof(hash_map.keys) ___keys = malloc(hash_map.capacity * sizeof(typeof(*hash_map.keys)));       \
    if (!___keys)                                                                                     \
    {                                                                                                 \
        printf("Allocation error!\n");                                                                \
        exit(1);                                                                                      \
    }                                                                                                 \
    typeof(hash_map.values) ___values = malloc(hash_map.capacity * sizeof(typeof(*hash_map.values))); \
    if (!___values)                                                                                   \
    {                                                                                                 \
        printf("Allocation error!\n");                                                                \
        exit(1);                                                                                      \
    }                                                                                                 \
    for (int ___i = 0; ___i < hash_map.capacity; ___i++)                                              \
    {                                                                                                 \
        ___keys[___i] = (typeof(*hash_map.keys))ulist_init;                                           \
        ___values[___i] = (typeof(*hash_map.values))ulist_init;                                       \
    }

#define hash_map_free(hash_map)                     \
    {                                               \
        for (int i = 0; i < hash_map.capacity; i++) \
        {                                           \
            ulist_free(hash_map.keys[i]);           \
            ulist_free(hash_map.values[i]);         \
        }                                           \
        free(hash_map.keys);                        \
        free(hash_map.values);                      \
    }

#define hash_map_rehash_if_full(hash_map)                                                                            \
    {                                                                                                                \
        do                                                                                                           \
        {                                                                                                            \
            if (0.5 < (float)hash_map.size / (float)hash_map.capacity)                                               \
            {                                                                                                        \
                hash_map.capacity *= 2;                                                                              \
                ___hash_map_init_ulists(hash_map) for (int ___i = 0; ___i < hash_map.capacity / 2; ___i++)           \
                {                                                                                                    \
                    for (int ___j = 0; ___j < hash_map.keys[___i].size; ___j++)                                      \
                    {                                                                                                \
                        int newIndex = abs(hash_map.hash(ulist_get(hash_map.keys[___i], ___j))) % hash_map.capacity; \
                        ulist_push(___keys[newIndex], ulist_get(hash_map.keys[___i], ___j));                         \
                        ulist_push(___values[newIndex], ulist_get(hash_map.values[___i], ___j));                     \
                    }                                                                                                \
                    ulist_free(hash_map.keys[___i]);                                                                 \
                    ulist_free(hash_map.values[___i]);                                                               \
                }                                                                                                    \
                free(hash_map.keys);                                                                                 \
                free(hash_map.values);                                                                               \
                hash_map.keys = ___keys;                                                                             \
                hash_map.values = ___values;                                                                         \
            }                                                                                                        \
            else if (hash_map.capacity == 0)                                                                         \
            {                                                                                                        \
                hash_map.capacity = HASH_MAP_DEFAULT_SIZE;                                                           \
                ___hash_map_init_ulists(hash_map)                                                                    \
                    hash_map.keys = ___keys;                                                                         \
                hash_map.values = ___values;                                                                         \
            }                                                                                                        \
        } while (0);                                                                                                 \
    }

#define hash_map_put(hash_map, key, value)                                         \
    {                                                                              \
        do                                                                         \
        {                                                                          \
            hash_map_rehash_if_full(hash_map);                                     \
            int ___index = abs(hash_map.hash(key)) % hash_map.capacity;            \
            int ___i = 0;                                                          \
            while (___i < hash_map.keys[___index].size)                            \
            {                                                                      \
                if (hash_map.equal(ulist_get(hash_map.keys[___index], ___i), key)) \
                    hash_map.values[___index].array[___i] = value;                 \
                ___i++;                                                            \
            }                                                                      \
            if (___i == hash_map.keys[___index].size)                              \
            {                                                                      \
                ulist_push(hash_map.keys[___index], key);                          \
                ulist_push(hash_map.values[___index], value);                      \
                hash_map.size++;                                                   \
            }                                                                      \
                                                                                   \
        } while (0);                                                               \
    }

#define hash_map_has(hash_map, key)                                                                                   \
    ({                                                                                                                \
        int ___index = abs(hash_map.hash(key)) % hash_map.capacity;                                                   \
        int ___i = 0;                                                                                                 \
        while (___i < hash_map.keys[___index].size && !hash_map.equal(ulist_get(hash_map.keys[___index], ___i), key)) \
            ___i++;                                                                                                   \
        (___i < hash_map.keys[___index].size);                                                                        \
    })

#define hash_map_get(hash_map, key) (                                                                                 \
    {                                                                                                                 \
        int ___index = abs(hash_map.hash(key)) % hash_map.capacity;                                                   \
        int ___i = 0;                                                                                                 \
        while (___i < hash_map.keys[___index].size && !hash_map.equal(ulist_get(hash_map.keys[___index], ___i), key)) \
            ___i++;                                                                                                   \
        (ulist_get(hash_map.values[___index], ___i));                                                                 \
    })

#define hash_map_remove(hash_map, key)                                                                                \
    {                                                                                                                 \
        int ___index = hash_map.hash(key) % hash_map.capacity;                                                        \
        int ___i = 0;                                                                                                 \
        while (___i < hash_map.keys[___index].size && !hash_map.equal(ulist_get(hash_map.keys[___index], ___i), key)) \
            ___i++;                                                                                                   \
        ulist_remove(hash_map.keys[___index], ___i);                                                                  \
        ulist_remove(hash_map.values[___index], ___i);                                                                \
        hash_map.size--;                                                                                              \
    }

#endif
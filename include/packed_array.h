#pragma once
#ifndef PACKED_ARRAY_H
#define PACKED_ARRAY_H
#include "hash_map.h"

#define PACKED_ARRAY_SIZE 1024
typedef int Entity;

/**
 * Defines a new type of component array with name name and type T
 */
#define packed_array_define(T)                       \
    hash_map_define_name(int, Entity, intEntMap##T); \
    hash_map_define_name(Entity, int, EntintMap##T); \
    typedef struct PArray_##T                        \
    {                                                \
        T data[PACKED_ARRAY_SIZE];                   \
        intEntMap##T index_to_entity;                \
        EntintMap##T entity_to_index;                \
        int size;                                    \
    } PArray_##T

/**
 * Initiates variables in a component array
 */
#define packed_array_init {                  \
    .data = {0},                             \
    .index_to_entity = hash_map_init_intkey, \
    .entity_to_index = hash_map_init_intkey, \
    .size = 0,                               \
}

/**
 * Pushes an entity and a component to the array
 */
#define packed_array_push(packed_array, entity, value)                         \
    do                                                                         \
    {                                                                          \
        packed_array.data[packed_array.size] = value;                          \
        hash_map_put(packed_array.index_to_entity, packed_array.size, entity); \
        hash_map_put(packed_array.entity_to_index, entity, packed_array.size); \
        packed_array.size++;                                                   \
    } while (0)

/**
 * Removes a component from an entity at the given index
 */
#define packed_array_remove_index(packed_array, index)                                                                        \
    do                                                                                                                        \
    {                                                                                                                         \
        packed_array.data[index] = packed_array.data[packed_array.size - 1];                                                  \
        if (!hash_map_has(packed_array.index_to_entity, index))                                                               \
        {                                                                                                                     \
            printf("Index is not associated with an entity\n");                                                               \
            exit(1);                                                                                                          \
        }                                                                                                                     \
        hash_map_put(packed_array.index_to_entity, index, hash_map_get(packed_array.index_to_entity, packed_array.size - 1)); \
        hash_map_put(packed_array.entity_to_index, hash_map_get(packed_array.index_to_entity, index), index);                 \
        hash_map_remove(packed_array.index_to_entity, index);                                                                 \
        packed_array.size--;                                                                                                  \
    } while (0)

/**
 * Removes an entity from the packed array
 */
#define packed_array_remove_entity(packed_array, entity)                                             \
    do                                                                                               \
    {                                                                                                \
        if (!hash_map_has(packed_array.entity_to_index, entity))                                     \
        {                                                                                            \
            printf("Entity does not exist\n");                                                       \
            exit(1);                                                                                 \
        }                                                                                            \
        packed_array_remove_index(packed_array, hash_map_get(packed_array.entity_to_index, entity)); \
    } while (0)

#define packed_array_has_index(packed_array, index) (index < packed_array.size)
#define packed_array_has_entity(packed_array, entity) (hash_map_has(packed_array.entity_to_index, entity))

#define packed_array_get_index(packed_array, index) (packed_array.data[index])
#define packed_array_get_entity(packed_array, entity) (packed_array.data[hash_map_get(packed_array.entity_to_index, entity)])

#endif
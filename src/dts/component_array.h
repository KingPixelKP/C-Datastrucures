#ifndef COMPONENT_ARRAY_H
#define COMPONENT_ARRAY_H

#define COMPONENTS_SIZE 16
typedef int Entity;

/**
 * Defines a new type of component array with name name and type T
 */
#define comparray_define(T)                    \
    typedef struct CmpArray_##T                \
    {                                          \
        T data[COMPONENTS_SIZE];               \
        Entity indexToEntity[COMPONENTS_SIZE]; \
        int entityToIndex[COMPONENTS_SIZE];    \
        int size;                              \
    } CmpArray_##T

/**
 * Initiates variables in a component array
 */
#define comparray_init {  \
    .data = {0},          \
    .indexToEntity = {0}, \
    .entityToIndex = {0}, \
    .size = 0,            \
}

/**
 * Pushes an entity and a component to the array
 */
#define comparray_push(compArray, entity, component)      \
    do                                                    \
    {                                                     \
        compArray.entityToIndex[entity] = compArray.size; \
        compArray.indexToEntity[compArray.size] = entity; \
        compArray.data[compArray.size] = component;       \
        compArray.size++;                                 \
    } while (0)

/**
 * Removes a component from an entity at the given index
 */
#define comparray_remove_index(compArray, index)                                      \
    do                                                                                \
    {                                                                                 \
        compArray.data[index] = compArray.data[compArray.size - 1];                   \
        compArray.entityToIndex[compArray.indexToEntity[compArray.size - 1]] = index; \
        compArray.indexToEntity[index] = compArray.indexToEntity[compArray.size - 1]; \
        compArray.size--;                                                             \
    } while (0)

#endif

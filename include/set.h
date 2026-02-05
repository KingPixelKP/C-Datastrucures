#pragma once
#ifndef SET_H
#define SET_H

#include <stdbool.h>
#include "unordered_list.h"
#include "default_funcitons.h"

#define set_define(T)                      \
    ulist_define(T);                       \
    typedef struct Set_##T                 \
    {                                      \
        bool (*equal)(T value1, T value2); \
        UList_##T list;                    \
    } Set_##T;

#define set_init(equalFn)   \
    {                       \
        .equal = equalFn,   \
        .list = ulist_init, \
    }

#define set_init_intval(equalFn) \
    {                            \
        .equal = intEqualFn,     \
        .list = ulist_init,      \
    }

#define set_init_intstr(equalFn) \
    {                            \
        .equal = strEqualFn,     \
        .list = ulist_init,      \
    }

#define set_has(set, value) ({                           \
    bool found = false;                                  \
    for (int ___i = 0; ___i < set.list.size; ___i++)     \
    {                                                    \
        if (set.equal(ulist_get(set.list, ___i), value)) \
        {                                                \
            found = true;                                \
            break;                                       \
        }                                                \
    }                                                    \
    found;                                               \
})

#define set_size(set) (set.list.size)

#define set_add(set, value)              \
    do                                   \
    {                                    \
                                         \
        if (!set_has(set, value))        \
            ulist_push(set.list, value); \
                                         \
    } while (0)

#define set_remove(set, value)                               \
    do                                                       \
    {                                                        \
        for (int ___i = 0; ___i < set.list.size; ___i++)     \
        {                                                    \
            if (set.equal(ulist_get(set.list, ___i), value)) \
            {                                                \
                ulist_remove(set.list, ___i);                \
            }                                                \
        }                                                    \
    } while (0)

#define set_get(set, index) (ulist_get(set.list, index))

#endif
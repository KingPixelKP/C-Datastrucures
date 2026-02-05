#ifndef SET_H
#define SET_H

#include <stdbool.h>
#include "unordered_list.h"

#define set_define(T)                   \
    ulist_define(T);                    \
    typedef struct Set_##T              \
    {                                   \
        bool equal(T value1, T value2); \
        UList_##T list;                 \
    } Set_##T;

#endif
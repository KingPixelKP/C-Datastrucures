#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>

/**
 * Defines all the necessary structs for a linked list of type T
 */
#define linked_list_define(T)     \
    typedef struct ___Node_##T    \
    {                             \
        T value;                  \
        struct ___Node_##T *next; \
        struct ___Node_##T *prev; \
    } ___Node_##T;                \
    typedef struct LinkList_##T   \
    {                             \
        ___Node_##T *front;       \
        ___Node_##T *back;        \
        int size;                 \
    } LinkList_##T

/**
 * Inits a linked list
 */
#define linked_list_init { \
    .front = NULL,         \
    .back = NULL,          \
    .size = 0,             \
}

/**
 * Inits a linked list's node
 */
#define ___linked_list_node_init \
    (typeof(*list.front))        \
    {                            \
        .next = NULL,            \
        .prev = NULL,            \
    }

#define ___linked_list_get_node(list, index) ({     \
    if (list.size == 0)                             \
    {                                               \
        printf("Nothing to get");                   \
        exit(1);                                    \
    }                                               \
    typeof(list.front) ___worker_node;              \
    if (index < list.size / 2)                      \
    {                                               \
        ___worker_node = list.front;                \
        for (int i = 0; i < index; i++)             \
            ___worker_node = ___worker_node->next;  \
    }                                               \
    else                                            \
    {                                               \
        ___worker_node = list.back;                 \
        for (int i = list.size - 1; i > index; i--) \
            ___worker_node = ___worker_node->prev;  \
    }                                               \
    ___worker_node;                                 \
})

/**
 * Pushes a value to the back of the linked list
 */
#define linked_list_push_back(list, _value)                        \
    do                                                             \
    {                                                              \
        if (list.size == 0)                                        \
        {                                                          \
            list.front = malloc(sizeof(typeof(*list.front)));      \
            if (!list.front)                                       \
            {                                                      \
                printf("Allocation error!\n");                     \
                exit(1);                                           \
            }                                                      \
            *list.front = ___linked_list_node_init;                \
            list.back = list.front;                                \
            list.front->value = _value;                            \
        }                                                          \
        else                                                       \
        {                                                          \
            list.back->next = malloc(sizeof(typeof(*list.front))); \
            if (!list.back->next)                                  \
            {                                                      \
                printf("Allocation error!\n");                     \
                exit(1);                                           \
            }                                                      \
            *list.back->next = ___linked_list_node_init;           \
            list.back->next->prev = list.back;                     \
            list.back = list.back->next;                           \
            list.back->value = _value;                             \
        }                                                          \
        list.size++;                                               \
    } while (0)

/**
 * Pushes a value to the front of the linked list
 */
#define linked_list_push_front(list, _value)                        \
    do                                                              \
    {                                                               \
        if (list.size == 0)                                         \
        {                                                           \
            list.front = malloc(sizeof(typeof(*list.front)));       \
            if (!list.front)                                        \
            {                                                       \
                printf("Allocation error!\n");                      \
                exit(1);                                            \
            }                                                       \
            *list.front = ___linked_list_node_init;                 \
            list.back = list.front;                                 \
            list.front->value = _value;                             \
        }                                                           \
        else                                                        \
        {                                                           \
            list.front->prev = malloc(sizeof(typeof(*list.front))); \
            if (!list.front->prev)                                  \
            {                                                       \
                printf("Allocation error!\n");                      \
                exit(1);                                            \
            }                                                       \
            *list.front->prev = ___linked_list_node_init;           \
            list.front->prev->next = list.front;                    \
            list.front = list.front->prev;                          \
            list.front->value = _value;                             \
        }                                                           \
        list.size++;                                                \
    } while (0)

/**
 * Pops a value from the back of the list
 */
#define linked_list_pop(list) ({                         \
    if (list.size == 0)                                  \
    {                                                    \
        printf("Nothing to pop");                        \
        exit(1);                                         \
    }                                                    \
    typeof(list.front->value) ___ret = list.back->value; \
    typeof(list.back) ___removed_node = list.back;       \
    list.back = list.back->prev;                         \
    free(___removed_node);                               \
    list.size--;                                         \
    if (list.size != 0)                                  \
        list.back->next = NULL;                          \
    ___ret;                                              \
})
/**
 * pops the value at the front of the list
 */
#define linked_list_deque(list)                               \
    ({                                                        \
        if (list.size == 0)                                   \
        {                                                     \
            printf("Nothing to deque");                       \
            exit(1);                                          \
        }                                                     \
        typeof(list.front->value) ___ret = list.front->value; \
        typeof(list.back) ___removed_node = list.front;       \
        list.front = list.front->next;                        \
        free(___removed_node);                                \
        list.size--;                                          \
        if (list.size != 0)                                   \
            list.front->prev = NULL;                          \
        ___ret;                                               \
    })
/**
 * Peeks the back of the linked list
 */
#define linked_list_peek_back(list) (list.back->value)
/**
 * Peeks the front of the linked list
 */
#define linked_list_peek_front(list) (list.front->value)

/**
 * Gets value of node at index
 */
#define linked_list_get(list, index) (___linked_list_get_node(list, index)->value)
/**
 * Sets value of node at index to _value
 */
#define linked_list_set(list, index, _value)                  \
    {                                                         \
        ___linked_list_get_node(list, index)->value = _value; \
    }
/**
 * Inserts node at index with value _value
 */
#define linked_list_insert(list, index, _value)                                     \
    {                                                                               \
        typeof(list.front) ___insert_before = ___linked_list_get_node(list, index); \
        typeof(list.front) ___new_node = malloc(sizeof(typeof(*list.front)));       \
        if (!___new_node)                                                           \
        {                                                                           \
            printf("Allocation error!\n");                                          \
            exit(1);                                                                \
        }                                                                           \
        *___new_node = ___linked_list_node_init;                                    \
        ___new_node->value = _value;                                                \
        ___new_node->next = ___insert_before;                                       \
        ___new_node->prev = ___insert_before->prev;                                 \
        ___insert_before->prev->next = ___new_node;                                 \
        ___insert_before->prev = ___new_node;                                       \
        list.size++;                                                                \
    }
/**
 * remove node with at index index
 */
#define linked_list_remove(list, index)                                         \
    {                                                                           \
        typeof(list.front) ___to_remove = ___linked_list_get_node(list, index); \
        list.size--;                                                            \
        if (___to_remove->next)                                                 \
            ___to_remove->next->prev = ___to_remove->prev;                      \
        else                                                                    \
            list.back = ___to_remove->prev;                                     \
        if (___to_remove->prev)                                                 \
            ___to_remove->prev->next = ___to_remove->next;                      \
        else                                                                    \
            list.front = ___to_remove->next;                                    \
        free(___to_remove);                                                     \
    }
#endif

#pragma once
#ifndef SEARCH_TREE_H
#define SEARCH_TREE_H
#include <stdlib.h>
#include <assert.h>
#include "default_funcitons.h"
#include "unordered_list.h"

#define search_tree_define(K, V)                         \
    typedef struct ___Node_##K##V                        \
    {                                                    \
        K key;                                           \
        V value;                                         \
        struct ___Node_##K##V *parent;                   \
        struct ___Node_##K##V *left;                     \
        struct ___Node_##K##V *right;                    \
    } ___Node_##K##V;                                    \
    ulist_define_name(___Node_##K##V *, recursionStack); \
    typedef struct BSTree_##K##V                         \
    {                                                    \
        int (*cmp)(K key1, K key2);                      \
        ___Node_##K##V *root;                            \
        recursionStack stack;                            \
        int size;                                        \
    } BSTree_##K##V

#define search_tree_init(cmpFn) \
    {                           \
        .cmp = cmpFn,           \
        .root = NULL,           \
        .size = 0,              \
        .stack = ulist_init,    \
    }

#define ___search_tree_node_init(tree) \
    (typeof(*tree.root))               \
    {                                  \
        .left = NULL,                  \
        .right = NULL,                 \
    }

#define ___search_tree_malloc_node (                                    \
    {                                                                   \
        typeof(tree.root) ___node = malloc(sizeof(typeof(*tree.root))); \
        if (!___node)                                                   \
        {                                                               \
            printf("Allocation error\n");                               \
            exit(1);                                                    \
        }                                                               \
        ___node;                                                        \
    })

#define search_tree_put(tree, _key, _value)                                              \
    do                                                                                   \
    {                                                                                    \
        if (tree.size == 0)                                                              \
        {                                                                                \
            tree.root = ___search_tree_malloc_node;                                      \
            *tree.root = ___search_tree_node_init(tree);                                 \
            tree.root->key = _key;                                                       \
            tree.root->value = _value;                                                   \
            tree.root->parent = NULL;                                                    \
            tree.size++;                                                                 \
        }                                                                                \
        else                                                                             \
        {                                                                                \
            ulist_push(tree.stack, tree.root);                                           \
            while (true)                                                                 \
            {                                                                            \
                int ___comparsion = tree.cmp(ulist_peek(tree.stack)->key, _key);         \
                if (___comparsion == 0)                                                  \
                {                                                                        \
                    ulist_peek(tree.stack)->value = _value;                              \
                    break;                                                               \
                }                                                                        \
                else if (___comparsion > 0)                                              \
                {                                                                        \
                    if (!ulist_peek(tree.stack)->right)                                  \
                    {                                                                    \
                        ulist_peek(tree.stack)->right = ___search_tree_malloc_node;      \
                        *ulist_peek(tree.stack)->right = ___search_tree_node_init(tree); \
                        ulist_peek(tree.stack)->right->key = _key;                       \
                        ulist_peek(tree.stack)->right->value = _value;                   \
                        ulist_peek(tree.stack)->right->parent = ulist_peek(tree.stack);  \
                        break;                                                           \
                    }                                                                    \
                    else                                                                 \
                    {                                                                    \
                        ulist_push(tree.stack, ulist_peek(tree.stack)->right);           \
                    }                                                                    \
                }                                                                        \
                else                                                                     \
                {                                                                        \
                    if (!ulist_peek(tree.stack)->left)                                   \
                    {                                                                    \
                        ulist_peek(tree.stack)->left = ___search_tree_malloc_node;       \
                        *ulist_peek(tree.stack)->left = ___search_tree_node_init(tree);  \
                        ulist_peek(tree.stack)->left->key = _key;                        \
                        ulist_peek(tree.stack)->left->value = _value;                    \
                        ulist_peek(tree.stack)->left->parent = ulist_peek(tree.stack);   \
                        break;                                                           \
                    }                                                                    \
                    else                                                                 \
                    {                                                                    \
                        ulist_push(tree.stack, ulist_peek(tree.stack)->left);            \
                    }                                                                    \
                }                                                                        \
            }                                                                            \
            ulist_clear(tree.stack);                                                     \
            assert(tree.stack.size == 0);                                                \
        }                                                                                \
    } while (0)

#define search_tree_get(tree, _key, _miss)                                           \
    (                                                                                \
        {                                                                            \
            typeof(tree.root) ___ret;                                                \
            if (tree.size == 0)                                                      \
            {                                                                        \
                printf("Tree is empty\n");                                           \
                exit(1);                                                             \
            }                                                                        \
            else                                                                     \
            {                                                                        \
                ulist_push(tree.stack, tree.root);                                   \
                while (true)                                                         \
                {                                                                    \
                    int ___comparsion = tree.cmp(ulist_peek(tree.stack)->key, _key); \
                    if (___comparsion == 0)                                          \
                    {                                                                \
                        ___ret = ulist_peek(tree.stack);                             \
                        break;                                                       \
                    }                                                                \
                    else if (___comparsion > 0)                                      \
                    {                                                                \
                        if (!ulist_peek(tree.stack)->right)                          \
                        {                                                            \
                            ___ret = _miss;                                          \
                            break;                                                   \
                        }                                                            \
                        else                                                         \
                        {                                                            \
                            ulist_push(tree.stack, ulist_peek(tree.stack)->right);   \
                        }                                                            \
                    }                                                                \
                    else                                                             \
                    {                                                                \
                        if (!ulist_peek(tree.stack)->left)                           \
                        {                                                            \
                                                                                     \
                            ___ret = _miss;                                          \
                            break;                                                   \
                        }                                                            \
                        else                                                         \
                        {                                                            \
                            ulist_push(tree.stack, ulist_peek(tree.stack)->left);    \
                        }                                                            \
                    }                                                                \
                }                                                                    \
                ulist_clear(tree.stack);                                             \
                assert(tree.stack.size == 0);                                        \
            }                                                                        \
                                                                                     \
            ___ret;                                                                  \
        })

#endif
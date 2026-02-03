#ifndef STACK_H
#define STACK_H

#define STACK_SIZE 16

#define stack_define(T)      \
    typedef struct Stack_##T \
    {                        \
        T array[STACK_SIZE]; \
        int size;            \
    } Stack_##T

#define stack_init { \
    .array = {0},    \
    .size = 0,       \
}

#define stack_push(stack, value) stack.array[stack.size++] = value

#define stack_pop(stack) stack.array[--stack.size]

#endif
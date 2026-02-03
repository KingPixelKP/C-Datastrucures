#ifndef STACK_H
#define STACK_H

#define STACK_SIZE 16

/**
 * Defines a stack of type T
 */
#define stack_define(T)      \
    typedef struct Stack_##T \
    {                        \
        T array[STACK_SIZE]; \
        int size;            \
    } Stack_##T

/**
 * Inits the stack
 */
#define stack_init { \
    .array = {0},    \
    .size = 0,       \
}

/**
 * Pushes a value onto the stack
 */
#define stack_push(stack, value) stack.array[stack.size++] = value

/**
 * Pops a value from the stack
 */
#define stack_pop(stack) stack.array[--stack.size]

#endif
#include <stdio.h>
#include <stdlib.h>

typedef int node_value_t;

#define NODE_DEFAULT_VALUE 0

typedef struct node_t {
    node_value_t value;
    struct node_t* next;
} node_t;

typedef struct stack_t {
    struct node_t* head;
    size_t size;
} custom_stack_t;

void stack_init(custom_stack_t* stack)
{
    stack->head = NULL;
    stack->size = 0u;
}

void stack_push(custom_stack_t* stack, node_value_t value)
{
    node_t* node = malloc(sizeof(node_t));
    node->value = value;
    node->next = stack->head;
    stack->head = node;
    ++stack->size;
}

node_value_t stack_top(custom_stack_t* stack)
{
    if (stack->size != 0u) {
        return stack->head->value;
    }

    return NODE_DEFAULT_VALUE;
}

size_t stack_size(custom_stack_t* stack)
{
    return stack->size;
}

void stack_pop(custom_stack_t* stack)»
{
    if (stack->size != 0u) {
        node_t* temp = stack->head;
        stack->head = stack->head->next;
        --stack->size;
        free(temp);
    }
}

void stack_destroy(custom_stack_t* stack)
{
    while (stack->size != 0u) {
        stack_pop(stack);
    }
}

int main()
{
    custom_stack_t stack;
    stack_init(&stack);

    stack_push(&stack, 5);
    stack_push(&stack, 10);
    stack_push(&stack, 15);

    printf("Size: %zu\n", stack_size(&stack));
    printf("Top: %d\n", stack_top(&stack));

    stack_destroy(&stack);

    printf("Size: %zu\n", stack_size(&stack));
    printf("Top: %d\n", stack_top(&stack));

    return EXIT_SUCCESS;
}

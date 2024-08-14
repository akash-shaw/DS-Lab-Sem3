#include <stdio.h>
#include <stdbool.h>
#define MAX_SIZE 100
// Structure to represent the stack
struct Stack
{
    int items[MAX_SIZE];
    int top;
};
// Function to initialize the stack
void initialize(struct Stack *stack)
{
    stack->top = -1;
}
// Function to check if the stack is empty
bool isEmpty(struct Stack *stack)
{
    return stack->top == -1;
}
// Function to check if the stack is full
bool isFull(struct Stack *stack)
{
    return stack->top == MAX_SIZE - 1;
}

// Function to push an item onto the stack
void push(struct Stack *stack, int item)
{
    if (isFull(stack))
    {
        printf("Stack overflow, cannot push %d\n", item);
        return;
    }
    stack->top++;
    stack->items[stack->top] = item;
}
// Function to pop an item from the stack
int pop(struct Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack underflow, cannot pop\n");
        return -1; // Return an error value
    }
    int poppedItem = stack->items[stack->top];
    stack->top--;
    return poppedItem;
}
// Function to peek at the top item of the stack without removing it
int peek(struct Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack is empty, cannot peek\n");
        return -1; // Return an error value
    }
    return stack->items[stack->top];
}

int main()
{
    struct Stack stack;
    initialize(&stack);

    char str[MAX_SIZE];
    int i = 0;

    printf("Enter string: ");
    gets(str);

    while (str[i] != NULL)
    {
        push(&stack, str[i++]);
    }

    i = 0;
    while (str[i] != NULL)
    {
        if (pop(&stack) != str[i++])
        {
            printf("Not a plaindrome\n");
            return 0;
        }
    }
    printf("Palindrome\n");
    return 0;
}
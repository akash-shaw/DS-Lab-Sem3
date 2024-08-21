#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_SIZE 100

// Structure to represent the stack
struct Stack
{
    char items[MAX_SIZE];
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
void push(struct Stack *stack, char item)
{
    if (isFull(stack))
    {
        printf("Stack overflow, cannot push %c\n", item);
        return;
    }
    stack->top++;
    stack->items[stack->top] = item;
}

// Function to pop an item from the stack
char pop(struct Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack underflow, cannot pop\n");
        return -1; // Return an error value
    }
    char poppedItem = stack->items[stack->top];
    stack->top--;
    return poppedItem;
}

// Function to peek at the top item of the stack without removing it
char peek(struct Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack is empty, cannot peek\n");
        return -1; // Return an error value
    }
    return stack->items[stack->top];
}

// Function to determine if a character is an operator
bool isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

// Function to determine the precedence of operators
int precedence(char op)
{
    switch (op)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    default:
        return 0;
    }
}

// Function to convert infix to postfix
void infixToPostfix(char s[], char postfix[])
{
    struct Stack stack;
    int i = 0, k = 0;
    initialize(&stack);

    while (s[i] != '\0')
    {
        if (s[i] == ' ') {
            i++;
            continue;
        }

        if (isalpha(s[i])) {
            postfix[k++] = s[i];
        }
        else if (s[i] == '(') {
            push(&stack, s[i]);
        }
        else if (s[i] == ')') {
            while (!isEmpty(&stack) && peek(&stack) != '(') {
                postfix[k++] = pop(&stack);
            }
            if (!isEmpty(&stack) && peek(&stack) == '(') {
                pop(&stack); // Remove '(' from stack
            }
        }
        else if (isOperator(s[i])) {
            while (!isEmpty(&stack) && precedence(peek(&stack)) >= precedence(s[i])) {
                postfix[k++] = pop(&stack);
            }
            push(&stack, s[i]);
        }

        i++;
    }

    // At last push everything
    while (!isEmpty(&stack)) {
        postfix[k++] = pop(&stack);
    }
    postfix[k] = '\0';
}

int main()
{
    char infix[100];
    char postfix[100];

    printf("Enter infix expression: ");
    gets(infix);

    infixToPostfix(infix, postfix);

    printf("Postfix expression: %s\n", postfix);
    
    return 0;
}

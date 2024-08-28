#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

#define MAX_SIZE 100

struct Stack
{
    float items[MAX_SIZE];
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
void push(struct Stack *stack, float item)
{
    if (isFull(stack))
    {
        printf("Stack overflow, cannot push %.2f\n", item);
        return;
    }
    stack->top++;
    stack->items[stack->top] = item;
}

// Function to pop an item from the stack
float pop(struct Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack underflow, cannot pop\n");
        return -1; // Return an error value
    }
    float poppedItem = stack->items[stack->top];
    stack->top--;
    return poppedItem;
}

// Function to peek at the top item of the stack without removing it
float peek(struct Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack is empty, cannot peek\n");
        return -1; // Return an error value
    }
    return stack->items[stack->top];
}

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

float charToFloat(char c)
{
    return (float)(c - '0');
}

bool isNum(char c)
{
    return c >= '0' && c <= '9';
}

float eval(float a, float b, char op)
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    case '^':
        return pow(a, b);
    default:
        return 0;
    }
}

float evalPostfix(char s[])
{
    struct Stack stack;
    int i = 0;
    initialize(&stack);

    while (s[i] != '\0')
    {
        if (s[i] == ' ')
        {
            i++;
            continue;
        }

        if (isNum(s[i]))
        {
            push(&stack, charToFloat(s[i]));
        }
        else if (isOperator(s[i]))
        {
            float b = pop(&stack);
            float a = pop(&stack);
            float result = eval(a, b, s[i]);
            push(&stack, result);
        }

        i++;
    }

    return pop(&stack);
}

int main()
{
    char postfixExpression[MAX_SIZE]; // Example postfix expression
    printf("Enter a postfix expression: ");
    gets(postfixExpression);
    float result = evalPostfix(postfixExpression);
    printf("The result of the postfix expression '%s' is: %f\n", postfixExpression, result);
    return 0;
}

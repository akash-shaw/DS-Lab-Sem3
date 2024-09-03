#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 100

// Stack structure for string items (used in postfix to infix conversion)
struct StringStack {
    char items[MAX_SIZE][MAX_SIZE];
    int top;
};

// Function to initialize the string stack
void initializeStringStack(struct StringStack *stack) {
    stack->top = -1;
}

// Function to check if the string stack is empty
bool isEmptyStringStack(struct StringStack *stack) {
    return stack->top == -1;
}

// Function to push a string onto the string stack
void pushString(struct StringStack *stack, char item[]) {
    if (stack->top == MAX_SIZE - 1) {
        printf("Stack overflow, cannot push %s\n", item);
        return;
    }
    stack->top++;
    strcpy(stack->items[stack->top], item);
}

// Function to pop a string from the string stack
void popString(struct StringStack *stack, char *result) {
    if (isEmptyStringStack(stack)) {
        printf("Stack underflow, cannot pop\n");
        return;
    }
    strcpy(result, stack->items[stack->top]);
    stack->top--;
}

// Function to determine if a character is an operator
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

// Function to convert postfix to fully parenthesized infix expression
void postfixToInfix(char s[], char infix[]) {
    struct StringStack stack;
    initializeStringStack(&stack);

    char operand1[MAX_SIZE], operand2[MAX_SIZE], temp[MAX_SIZE];
    for (int i = 0; s[i] != '\0'; i++) {
        if (isalpha(s[i])) {
            char operand[2] = {s[i], '\0'};
            pushString(&stack, operand);
        } else if (isOperator(s[i])) {
            popString(&stack, operand1);
            popString(&stack, operand2);
            sprintf(temp, "(%s%c%s)", operand2, s[i], operand1);
            pushString(&stack, temp);
        }
    }

    popString(&stack, infix);
}

int main() {
    char postfix[MAX_SIZE], infix[MAX_SIZE];

    printf("Enter postfix expression: ");
    gets(postfix);

    // Convert postfix to fully parenthesized infix
    postfixToInfix(postfix, infix);
    printf("Fully parenthesized infix expression: %s\n", infix);

    return 0;
}

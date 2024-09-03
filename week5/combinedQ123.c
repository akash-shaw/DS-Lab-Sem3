#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define MAX_SIZE 100

// Stack structure for characters (used in infix to postfix conversion)
struct Stack {
    char items[MAX_SIZE];
    int top;
};

// Stack structure for float items (used in postfix evaluation)
struct FloatStack {
    float items[MAX_SIZE];
    int top;
};

// Stack structure for string items (used in postfix to infix conversion)
struct StringStack {
    char items[MAX_SIZE][MAX_SIZE];
    int top;
};

// Function to initialize the stack (character stack)
void initialize(struct Stack *stack) {
    stack->top = -1;
}

// Function to initialize the float stack
void initializeFloatStack(struct FloatStack *stack) {
    stack->top = -1;
}

// Function to initialize the string stack
void initializeStringStack(struct StringStack *stack) {
    stack->top = -1;
}

// Function to check if the character stack is empty
bool isEmpty(struct Stack *stack) {
    return stack->top == -1;
}

// Function to check if the float stack is empty
bool isEmptyFloatStack(struct FloatStack *stack) {
    return stack->top == -1;
}

// Function to check if the string stack is empty
bool isEmptyStringStack(struct StringStack *stack) {
    return stack->top == -1;
}

// Function to push an item onto the character stack
void push(struct Stack *stack, char item) {
    if (stack->top == MAX_SIZE - 1) {
        printf("Stack overflow, cannot push %c\n", item);
        return;
    }
    stack->top++;
    stack->items[stack->top] = item;
}

// Function to push an item onto the float stack
void pushFloat(struct FloatStack *stack, float item) {
    if (stack->top == MAX_SIZE - 1) {
        printf("Stack overflow, cannot push %.2f\n", item);
        return;
    }
    stack->top++;
    stack->items[stack->top] = item;
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

// Function to pop an item from the character stack
char pop(struct Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow, cannot pop\n");
        return -1;
    }
    char poppedItem = stack->items[stack->top];
    stack->top--;
    return poppedItem;
}

// Function to pop an item from the float stack
float popFloat(struct FloatStack *stack) {
    if (isEmptyFloatStack(stack)) {
        printf("Stack underflow, cannot pop\n");
        return -1;
    }
    float poppedItem = stack->items[stack->top];
    stack->top--;
    return poppedItem;
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

// Function to peek at the top item of the character stack without removing it
char peek(struct Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty, cannot peek\n");
        return -1;
    }
    return stack->items[stack->top];
}

// Function to determine if a character is an operator
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

// Function to determine the precedence of operators
int precedence(char op) {
    switch (op) {
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
void infixToPostfix(char s[], char postfix[]) {
    struct Stack stack;
    int i = 0, k = 0;
    initialize(&stack);

    while (s[i] != '\0') {
        if (s[i] == ' ') {
            i++;
            continue;
        }

        if (isalpha(s[i])) {
            postfix[k++] = s[i];
        } else if (s[i] == '(') {
            push(&stack, s[i]);
        } else if (s[i] == ')') {
            while (!isEmpty(&stack) && peek(&stack) != '(') {
                postfix[k++] = pop(&stack);
            }
            if (!isEmpty(&stack) && peek(&stack) == '(') {
                pop(&stack);
            }
        } else if (isOperator(s[i])) {
            while (!isEmpty(&stack) && precedence(peek(&stack)) >= precedence(s[i])) {
                postfix[k++] = pop(&stack);
            }
            push(&stack, s[i]);
        }

        i++;
    }

    while (!isEmpty(&stack)) {
        postfix[k++] = pop(&stack);
    }
    postfix[k] = '\0';
}

// Function to evaluate postfix expression
float evalPostfix(char s[]) {
    struct FloatStack stack;
    int i = 0;
    initializeFloatStack(&stack);

    while (s[i] != '\0') {
        if (s[i] == ' ') {
            i++;
            continue;
        }

        if (isdigit(s[i])) {
            pushFloat(&stack, (float)(s[i] - '0'));
        } else if (isOperator(s[i])) {
            float b = popFloat(&stack);
            float a = popFloat(&stack);
            float result;
            switch (s[i]) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': result = a / b; break;
                case '^': result = pow(a, b); break;
                default: result = 0; break;
            }
            pushFloat(&stack, result);
        }

        i++;
    }

    return popFloat(&stack);
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
    char infix[100], postfix[100], finalInfix[100];

    printf("Enter infix expression: ");
    gets(infix);

    // Convert infix to postfix
    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);

    // Evaluate postfix expression (Assuming numeric values)
    // Example evaluation using predefined numeric values (A = 2, B = 3, C = 4, D = 2)
    char numericPostfix[] = "234+*2/";
    float result = evalPostfix(numericPostfix);
    printf("Evaluated result of postfix: %f\n", result);

    // Convert postfix back to fully parenthesized infix
    postfixToInfix(postfix, finalInfix);
    printf("Fully parenthesized infix expression: %s\n", finalInfix);

    return 0;
}

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 100

// Stack structure for character items (used in infix to prefix conversion)
struct CharStack {
    char items[MAX_SIZE];
    int top;
};

// Stack structure for float items (used in prefix evaluation)
struct FloatStack {
    float items[MAX_SIZE];
    int top;
};

// Stack structure for string items (used in prefix to infix conversion)
struct StringStack {
    char items[MAX_SIZE][MAX_SIZE];
    int top;
};

// Function to initialize a char stack
void initializeCharStack(struct CharStack *stack) {
    stack->top = -1;
}

// Function to initialize a float stack
void initializeFloatStack(struct FloatStack *stack) {
    stack->top = -1;
}

// Function to initialize a string stack
void initializeStringStack(struct StringStack *stack) {
    stack->top = -1;
}

// Function to check if a char stack is empty
bool isEmptyCharStack(struct CharStack *stack) {
    return stack->top == -1;
}

// Function to check if a float stack is empty
bool isEmptyFloatStack(struct FloatStack *stack) {
    return stack->top == -1;
}

// Function to check if a string stack is empty
bool isEmptyStringStack(struct StringStack *stack) {
    return stack->top == -1;
}

// Function to push a character onto a char stack
void pushChar(struct CharStack *stack, char item) {
    if (stack->top == MAX_SIZE - 1) {
        printf("Stack overflow, cannot push %c\n", item);
        return;
    }
    stack->top++;
    stack->items[stack->top] = item;
}

// Function to push a float onto a float stack
void pushFloat(struct FloatStack *stack, float item) {
    if (stack->top == MAX_SIZE - 1) {
        printf("Stack overflow, cannot push %.2f\n", item);
        return;
    }
    stack->top++;
    stack->items[stack->top] = item;
}

// Function to push a string onto a string stack
void pushString(struct StringStack *stack, char item[]) {
    if (stack->top == MAX_SIZE - 1) {
        printf("Stack overflow, cannot push %s\n", item);
        return;
    }
    stack->top++;
    strcpy(stack->items[stack->top], item);
}

// Function to pop a character from a char stack
char popChar(struct CharStack *stack) {
    if (isEmptyCharStack(stack)) {
        printf("Stack underflow, cannot pop\n");
        return -1;
    }
    return stack->items[stack->top--];
}

// Function to pop a float from a float stack
float popFloat(struct FloatStack *stack) {
    if (isEmptyFloatStack(stack)) {
        printf("Stack underflow, cannot pop\n");
        return -1;
    }
    return stack->items[stack->top--];
}

// Function to pop a string from a string stack
void popString(struct StringStack *stack, char *result) {
    if (isEmptyStringStack(stack)) {
        printf("Stack underflow, cannot pop\n");
        return;
    }
    strcpy(result, stack->items[stack->top--]);
}

// Function to check if a character is an operator
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

// Function to reverse a string
void reverseString(char s[]) {
    int len = strlen(s);
    for (int i = 0; i < len / 2; i++) {
        char temp = s[i];
        s[i] = s[len - i - 1];
        s[len - i - 1] = temp;
    }
}

// Function to convert infix to prefix
void infixToPrefix(char infix[], char prefix[]) {
    struct CharStack stack;
    initializeCharStack(&stack);
    int k = 0;

    reverseString(infix);

    for (int i = 0; infix[i] != '\0'; i++) {
        if (infix[i] == ')') {
            infix[i] = '(';
        } else if (infix[i] == '(') {
            infix[i] = ')';
        }
    }

    for (int i = 0; infix[i] != '\0'; i++) {
        if (isalpha(infix[i])) {
            prefix[k++] = infix[i];
        } else if (infix[i] == '(') {
            pushChar(&stack, infix[i]);
        } else if (infix[i] == ')') {
            while (!isEmptyCharStack(&stack) && stack.items[stack.top] != '(') {
                prefix[k++] = popChar(&stack);
            }
            popChar(&stack); // remove '(' from stack
        } else if (isOperator(infix[i])) {
            while (!isEmptyCharStack(&stack) && precedence(stack.items[stack.top]) >= precedence(infix[i])) {
                prefix[k++] = popChar(&stack);
            }
            pushChar(&stack, infix[i]);
        }
    }

    while (!isEmptyCharStack(&stack)) {
        prefix[k++] = popChar(&stack);
    }

    prefix[k] = '\0';
    reverseString(prefix);
}

// Function to evaluate a prefix expression
float evalPrefix(char s[]) {
    struct FloatStack stack;
    initializeFloatStack(&stack);
    int len = strlen(s);

    for (int i = len - 1; i >= 0; i--) {
        if (isalpha(s[i])) {
            printf("Error: Cannot evaluate expression with variables.\n");
            return -1;
        } else if (isdigit(s[i])) {
            pushFloat(&stack, s[i] - '0');
        } else if (isOperator(s[i])) {
            float op1 = popFloat(&stack);
            float op2 = popFloat(&stack);
            switch (s[i]) {
                case '+': pushFloat(&stack, op1 + op2); break;
                case '-': pushFloat(&stack, op1 - op2); break;
                case '*': pushFloat(&stack, op1 * op2); break;
                case '/': pushFloat(&stack, op1 / op2); break;
                case '^': pushFloat(&stack, pow(op1, op2)); break;
            }
        }
    }

    return popFloat(&stack);
}

// Function to convert prefix to fully parenthesized infix expression
void prefixToInfix(char s[], char infix[]) {
    struct StringStack stack;
    initializeStringStack(&stack);

    char operand1[MAX_SIZE], operand2[MAX_SIZE], temp[MAX_SIZE];
    int len = strlen(s);

    for (int i = len - 1; i >= 0; i--) {
        if (isalpha(s[i])) {
            char operand[2] = {s[i], '\0'};
            pushString(&stack, operand);
        } else if (isOperator(s[i])) {
            popString(&stack, operand1);
            popString(&stack, operand2);
            sprintf(temp, "(%s%c%s)", operand1, s[i], operand2);
            pushString(&stack, temp);
        }
    }

    popString(&stack, infix);
}

int main() {
    char infix[MAX_SIZE], prefix[MAX_SIZE], infixResult[MAX_SIZE];
    char prefixExpression[MAX_SIZE];
    float evalResult;

    // Question 1: Infix to Prefix
    printf("Enter infix expression: ");
    gets(infix);
    infixToPrefix(infix, prefix);
    printf("Prefix expression: %s\n", prefix);

    // Question 2: Evaluate Prefix Expression
    printf("Enter prefix expression (only numbers): ");
    gets(prefixExpression);
    evalResult = evalPrefix(prefixExpression);
    printf("Evaluated result of prefix: %.6f\n", evalResult);

    // Question 3: Prefix to Fully Parenthesized Infix
    printf("Enter prefix expression: ");
    gets(prefixExpression);
    prefixToInfix(prefixExpression, infixResult);
    printf("Fully parenthesized infix expression: %s\n", infixResult);

    return 0;
}

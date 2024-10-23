#include <stdio.h>
#include <stdlib.h>

// Structure to represent a term in a polynomial
struct PolyNode {
    int coeff; // Coefficient of the term
    int exp;   // Exponent of the term
    struct PolyNode *next; // Pointer to the next term
};

// Function to create a new polynomial node
struct PolyNode* createNode(int coeff, int exp) {
    struct PolyNode *newNode = (struct PolyNode*)malloc(sizeof(struct PolyNode));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a term into the polynomial in sorted order
struct PolyNode* insertTerm(struct PolyNode *poly, int coeff, int exp) {
    struct PolyNode *newNode = createNode(coeff, exp);
    if (poly == NULL || exp > poly->exp) {
        newNode->next = poly;
        return newNode;
    }

    struct PolyNode *current = poly;
    while (current->next != NULL && current->next->exp >= exp) {
        current = current->next;
    }

    if (current->exp == exp) {
        current->coeff += coeff; // Combine coefficients if exponents are the same
        free(newNode); // Free the new node if we combine
    } else {
        newNode->next = current->next;
        current->next = newNode;
    }
    return poly;
}

// Function to add two polynomials
struct PolyNode* addPolynomials(struct PolyNode *poly1, struct PolyNode *poly2) {
    struct PolyNode *result = NULL;

    while (poly1 != NULL) {
        result = insertTerm(result, poly1->coeff, poly1->exp);
        poly1 = poly1->next;
    }

    while (poly2 != NULL) {
        result = insertTerm(result, poly2->coeff, poly2->exp);
        poly2 = poly2->next;
    }

    return result;
}

// Function to display the polynomial
void displayPolynomial(struct PolyNode *poly) {
    if (poly == NULL) {
        printf("0");
        return;
    }
    
    struct PolyNode *current = poly;
    while (current != NULL) {
        printf("%dx^%d", current->coeff, current->exp);
        current = current->next;
        if (current != NULL) {
            printf(" + ");
        }
    }
    printf("\n");
}

// Main function
int main() {
    struct PolyNode *poly1 = NULL;
    struct PolyNode *poly2 = NULL;

    // Creating first polynomial: 3x^2 + 2x^1 + 5
    poly1 = insertTerm(poly1, 3, 2);
    poly1 = insertTerm(poly1, 2, 1);
    poly1 = insertTerm(poly1, 5, 0);

    // Creating second polynomial: 4x^2 + 1x^1 + 3
    poly2 = insertTerm(poly2, 4, 2);
    poly2 = insertTerm(poly2, 1, 1);
    poly2 = insertTerm(poly2, 3, 0);

    // Displaying the polynomials
    printf("Polynomial 1: ");
    displayPolynomial(poly1);

    printf("Polynomial 2: ");
    displayPolynomial(poly2);

    // Adding the polynomials
    struct PolyNode *result = addPolynomials(poly1, poly2);

    // Displaying the result
    printf("Resultant Polynomial: ");
    displayPolynomial(result);

    // Free memory (not shown here for simplicity)
    // Note: In a real application, you should free the allocated memory

    return 0;
}

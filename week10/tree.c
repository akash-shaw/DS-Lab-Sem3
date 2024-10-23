#include <stdio.h>
#include <stdlib.h>

// Definition of a binary tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function for iterative in-order traversal
void inorderIterative(struct Node* root) {
    struct Node* stack[100];
    int top = -1;
    struct Node* current = root;

    while (current != NULL || top != -1) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }
        current = stack[top--];
        printf("%d ", current->data);
        current = current->right;
    }
    printf("\n");
}

// Function for iterative post-order traversal
void postorderIterative(struct Node* root) {
    if (root == NULL) return;

    struct Node* stack[100];
    int top = -1;
    struct Node* current = root;
    struct Node* lastVisited = NULL;

    while (top != -1 || current != NULL) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }

        current = stack[top];
        if (current->right == NULL || current->right == lastVisited) {
            printf("%d ", current->data);
            lastVisited = current;
            top--;
            current = NULL;
        } else {
            current = current->right;
        }
    }
    printf("\n");
}

// Function for iterative pre-order traversal
void preorderIterative(struct Node* root) {
    if (root == NULL) return;

    struct Node* stack[100];
    int top = -1;
    stack[++top] = root;

    while (top != -1) {
        struct Node* current = stack[top--];
        printf("%d ", current->data);
        if (current->right != NULL) {
            stack[++top] = current->right;
        }
        if (current->left != NULL) {
            stack[++top] = current->left;
        }
    }
    printf("\n");
}

// Function to find parent of a given element
struct Node* findParent(struct Node* root, int value) {
    if (root == NULL || (root->left == NULL && root->right == NULL)) {
        return NULL;
    }
    
    if ((root->left != NULL && root->left->data == value) ||
        (root->right != NULL && root->right->data == value)) {
        return root;
    }

    struct Node* leftParent = findParent(root->left, value);
    if (leftParent != NULL) {
        return leftParent;
    }
    return findParent(root->right, value);
}

// Function to calculate depth of the tree
int depth(struct Node* root) {
    if (root == NULL) return 0;
    int leftDepth = depth(root->left);
    int rightDepth = depth(root->right);
    return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
}

// Function to find ancestors of a given element
int findAncestors(struct Node* root, int value) {
    if (root == NULL) return 0;

    if (root->data == value) return 1;

    if (findAncestors(root->left, value) || findAncestors(root->right, value)) {
        printf("%d ", root->data);
        return 1;
    }
    return 0;
}

// Function to count leaf nodes
int countLeafNodes(struct Node* root) {
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return 1;
    return countLeafNodes(root->left) + countLeafNodes(root->right);
}

// Function to free the tree
void freeTree(struct Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// Main function with menu
int main() {
    struct Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    int choice, value;
    while (1) {
        printf("\nMenu:\n");
        printf("1. In-order Traversal\n");
        printf("2. Post-order Traversal\n");
        printf("3. Pre-order Traversal\n");
        printf("4. Print Parent of Given Element\n");
        printf("5. Print Depth of Tree\n");
        printf("6. Print Ancestors of Given Element\n");
        printf("7. Count Leaf Nodes\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("In-order Traversal: ");
                inorderIterative(root);
                break;
            case 2:
                printf("Post-order Traversal: ");
                postorderIterative(root);
                break;
            case 3:
                printf("Pre-order Traversal: ");
                preorderIterative(root);
                break;
            case 4:
                printf("Enter element to find parent: ");
                scanf("%d", &value);
                struct Node* parent = findParent(root, value);
                if (parent != NULL) {
                    printf("Parent of %d is %d\n", value, parent->data);
                } else {
                    printf("Parent not found.\n");
                }
                break;
            case 5:
                printf("Depth of tree: %d\n", depth(root));
                break;
            case 6:
                printf("Enter element to find ancestors: ");
                scanf("%d", &value);
                printf("Ancestors of %d: ", value);
                if (!findAncestors(root, value)) {
                    printf("No ancestors found or element not found.\n");
                }
                printf("\n");
                break;
            case 7:
                printf("Number of leaf nodes: %d\n", countLeafNodes(root));
                break;
            case 8:
                freeTree(root);
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

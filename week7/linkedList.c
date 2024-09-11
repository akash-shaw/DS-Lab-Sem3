#include <stdio.h>
#include <stdlib.h>

struct node {
    int info;
    struct node *link;
} *start = NULL;

void addAtEnd(int data) {
    struct node *q, *tmp;
    tmp = (struct node *)malloc(sizeof(struct node));
    tmp->info = data;
    tmp->link = NULL;

    if (start == NULL) {
        start = tmp;
    } else {
        q = start;
        while (q->link != NULL) {
            q = q->link;
        }
        q->link = tmp;
    }
}

void addAtBeg(int data) {
    struct node *tmp;
    tmp = (struct node *)malloc(sizeof(struct node));
    tmp->info = data;
    tmp->link = start;
    start = tmp;
}

int del(int data) {
    int found = 0;
    struct node *tmp, *q, *pre;
    if (start == NULL) return 0;

    if (start->info == data) {
        tmp = start;
        start = start->link;
        free(tmp);
        found = 1;
    } else {
        found = 0;
        q = start;
        while (q->link != NULL) {
            if (q->link->info == data) {
                found = 1;
                tmp = q->link;
                q->link = tmp->link;
                free(tmp);
                break;
            }
            q = q->link;
        }
    }
    return found;
}

void display() {
    struct node *tmp;
    if (start == NULL) {
        printf("Empty list\n");
        return;
    }
    tmp = start;
    while (tmp != NULL) {
        printf("%d ", tmp->info);
        tmp = tmp->link;
    }
    printf("\n");
}

void delAltNode() {
    struct node *tmp = start;
    while (tmp != NULL && tmp->link != NULL) {
        struct node *toDelete = tmp->link;
        tmp->link = toDelete->link;
        free(toDelete);
        tmp = tmp->link;
    }
}

void insertInSorted(int data) {
    struct node *tmp, *q;
    if (start == NULL || start->info >= data) {
        addAtBeg(data);
        return;
    }
    q = start;
    while (q->link != NULL && q->link->info < data) {
        q = q->link;
    }
    tmp = (struct node *)malloc(sizeof(struct node));
    tmp->info = data;
    tmp->link = q->link;
    q->link = tmp;
}

void rev() {
    struct node *p1, *p2, *p3;
    if (start == NULL || start->link == NULL) return;

    p1 = start;
    p2 = p1->link;
    p1->link = NULL;

    while (p2 != NULL) {
        p3 = p2->link;
        p2->link = p1;
        p1 = p2;
        p2 = p3;
    }
    start = p1;
}

// Function to insert a node into the sorted part of the list
void sortedInsert(struct node** sortedHead, struct node* newNode) {
    struct node* current;
    if (*sortedHead == NULL || (*sortedHead)->info >= newNode->info) {
        newNode->link = *sortedHead;
        *sortedHead = newNode;
    } else {
        current = *sortedHead;
        while (current->link != NULL && current->link->info < newNode->info) {
            current = current->link;
        }
        newNode->link = current->link;
        current->link = newNode;
    }
}

// Function to sort the list using insertion sort
void sort() {
    struct node *sorted = NULL;
    struct node *current = start;
    struct node *nextNode;

    while (current != NULL) {
        nextNode = current->link;  // Store next node
        current->link = NULL;      // Isolate current node
        sortedInsert(&sorted, current);  // Insert current node into sorted list
        current = nextNode;        // Move to the next node
    }
    start = sorted;  // Update start to point to the new sorted list
}

int main() {
    int choice, n;

    while (1) {
        printf("\n0. Exit\n1. Insert at end\n2. Insert at start\n3. Delete a given no\n4. Display\n5. Delete alternate nodes\n6. Insert element in sorted list\n7. Reverse\n8. Sort");

        printf("\nEnter Choice: ");
        scanf(" %d", &choice);

        switch (choice) {
        case 0:
            return 0;
        case 1:
            printf("Data: ");
            scanf("%d", &n);
            addAtEnd(n);
            break;
        case 2:
            printf("Data: ");
            scanf("%d", &n);
            addAtBeg(n);
            break;
        case 3:
            printf("Data: ");
            scanf("%d", &n);
            if (!del(n)) {
                printf("Element %d not found\n", n);
            }
            break;
        case 4:
            printf("List: ");
            display();
            break;
        case 5:
            delAltNode();
            break;
        case 6:
            printf("Data: ");
            scanf("%d", &n);
            insertInSorted(n);
            break;
        case 7:
            rev();
            break;
        case 8:
            sort();
            break;
        default:
            printf("Wrong choice, try again!\n");
            break;
        }
    }
    return 0;
}

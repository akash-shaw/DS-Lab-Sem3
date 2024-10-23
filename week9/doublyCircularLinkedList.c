#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *prev, *next;
} *head = NULL;

void displayList() {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    struct node *current = head;
    do {
        printf("%d ", current->data);
        current = current->next;
    } while (current != head);
    printf("\n");
}

void insertAtRear(int d) {
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = d;

    if (head == NULL) {
        head = temp;
        head->next = head;
        head->prev = head;
    } else {
        struct node *tail = head->prev;
        tail->next = temp;
        temp->prev = tail;
        temp->next = head;
        head->prev = temp;
    }
}

int deleteFromRear() {
    if (head == NULL) {
        printf("Empty List\n");
        return -1;
    }

    struct node *tail = head->prev;
    int deletedItem = tail->data;

    if (tail == head) { // Only one node in the list
        free(tail);
        head = NULL;
    } else {
        struct node *newTail = tail->prev;
        newTail->next = head;
        head->prev = newTail;
        free(tail);
    }

    return deletedItem;
}

void insertAtPos(int d, int pos) {
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = d;

    if (pos == 1) {
        if (head == NULL) {
            insertAtRear(d);
            return;
        }

        struct node *tail = head->prev;
        temp->next = head;
        temp->prev = tail;
        tail->next = temp;
        head->prev = temp;
        head = temp;
        return;
    }

    struct node *current = head;
    for (int i = 1; i < pos - 1; i++) {
        current = current->next;
        if (current == head) {
            printf("Invalid Position\n");
            free(temp);
            return;
        }
    }

    temp->next = current->next;
    temp->prev = current;
    current->next->prev = temp;
    current->next = temp;
}

int deleteAtPos(int pos) {
    if (head == NULL) {
        printf("Empty List\n");
        return -1;
    }

    struct node *current = head;
    for (int i = 1; i < pos; i++) {
        current = current->next;
        if (current == head) {
            printf("Invalid Position\n");
            return -1;
        }
    }

    int deletedItem = current->data;

    if (current == head) {
        if (current->next == head) { // Only one node
            free(current);
            head = NULL;
        } else {
            struct node *tail = head->prev;
            head = head->next;
            tail->next = head;
            head->prev = tail;
            free(current);
        }
    } else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
        free(current);
    }

    return deletedItem;
}

int main() {
    int choice, data, pos;

    while (1) {
        printf("\n0. Exit\n1. Insert an element at the rear end of the list\n2. Delete an element from the rear end of the list\n3. Insert an element at a given position of the list\n4. Delete an element from a given position of the list\n5. Traverse the list\n");
        printf("\nChoice: ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice) {
            case 0:
                printf("Exiting...\n");
                return 0;

            case 1:
                printf("Data: ");
                scanf("%d", &data);
                insertAtRear(data);
                break;

            case 2:
                data = deleteFromRear();
                if (data != -1) {
                    printf("%d deleted\n", data);
                }
                break;

            case 3:
                printf("Position: ");
                scanf("%d", &pos);
                printf("Data: ");
                scanf("%d", &data);
                insertAtPos(data, pos);
                break;

            case 4:
                printf("Position: ");
                scanf("%d", &pos);
                data = deleteAtPos(pos);
                if (data != -1) {
                    printf("%d deleted\n", data);
                }
                break;

            case 5:
                displayList();
                break;

            default:
                printf("Invalid Choice\n");
                break;
        }
    }

    return 0;
}

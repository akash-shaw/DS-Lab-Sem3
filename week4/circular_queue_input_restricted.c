#include <stdio.h>

#define Q_SIZE 10

struct Queue
{
    int front, rear;
    int q[Q_SIZE];
};

void initQueue(struct Queue *queue)
{
    queue->front = queue->rear = -1;
}

void insertq(struct Queue *queue, int item)
{
    if ((queue->rear + 1) % Q_SIZE == queue->front)
    {
        printf("Queue overflow\n");
        return;
    }

    if (queue->front == -1)
    {
        queue->front = 0;
    }

    queue->rear = (queue->rear + 1) % Q_SIZE;
    queue->q[queue->rear] = item;
}

int delqFront(struct Queue *queue)
{
    if (queue->front == -1)
        return -1;

    int deletedItem = queue->q[queue->front];

    if (queue->front == queue->rear)
    {
        queue->front = queue->rear = -1;
    }
    else
    {
        queue->front = (queue->front + 1) % Q_SIZE;
    }

    return deletedItem;
}
int delqBack(struct Queue *queue)
{
    if (queue->front == -1)
        return -1;

    int deletedItem = queue->q[queue->rear];

    if (queue->front == queue->rear)
    {
        queue->front = queue->rear = -1;
    }
    else
    {
        queue->rear = (queue->rear - 1) % Q_SIZE;
    }

    return deletedItem;
}

void display(struct Queue *queue)
{
    if (queue->front == -1)
    {
        printf("Empty queue\n");
        return;
    }

    printf("Contents:");
    int i = queue->front;
    while (1)
    {
        printf(" %d", queue->q[i]);
        if (i == queue->rear)
            break;
        i = (i + 1) % Q_SIZE;
    }
    printf("\n");
}

int main()
{
    struct Queue queue;
    initQueue(&queue);

    int choice, item;
    while (1)
    {
        printf("\n1. Insert an element\n");
        printf("2. Delete an element from front\n");
        printf("3. Delete an element from back\n");
        printf("4. Display the queue\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter the element to insert: ");
            scanf("%d", &item);
            insertq(&queue, item);
            break;
        case 2:
            item = delqFront(&queue);
            if (item != -1)
                printf("Deleted item: %d\n", item);
            else
                printf("Queue is empty.\n");
            break;
        case 3:
            item = delqBack(&queue);
            if (item != -1)
                printf("Deleted item: %d\n", item);
            else
                printf("Queue is empty.\n");
            break;
        case 4:
            display(&queue);
            break;
        case 5:
            printf("Exiting the program.\n");
            return 0;
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

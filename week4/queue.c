#include <stdio.h>

#define Q_SIZE 5

struct Queue
{
    int front, rear;
    int q[Q_SIZE];
};

void initQueue(struct Queue *queue){
    queue->front = 0;
    queue->rear = -1;
}

void insertq(struct Queue *queue, int item)
{
    if (queue->rear == Q_SIZE - 1)
    {
        printf("Queue overflow\n");
        return;
    }
    queue->rear++;
    queue->q[queue->rear] = item;
}

int delq(struct Queue *queue)
{
    if (queue->front > queue->rear)
        return -1;
    int deletedItem = queue->q[queue->front];
    queue->front++;
    return deletedItem;
}

void display(struct Queue *queue)
{
    if (queue->front > queue->rear)
    {
        printf("Empty queue\n");
        return;
    }
    printf("Contents:");
    for (int i = queue->front; i <= queue->rear; i++)
        printf(" %d", queue->q[i]);
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
        printf("2. Delete an element\n");
        printf("3. Display the queue\n");
        printf("4. Exit\n");
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
            item = delq(&queue);
            if (item != -1)
                printf("Deleted item: %d\n", item);
            else
                printf("Queue is empty.\n");
            break;
        case 3:
            display(&queue);
            break;
        case 4:
            printf("Exiting the program.\n");
            return 0;
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

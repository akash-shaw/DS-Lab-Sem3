#include<stdio.h>
#include<stdlib.h>
struct  node
{
    int data;
    struct node *prev, *next;
}*start = NULL, *end=NULL;

void displayList(){
    struct node *q=start;
    while(q!=NULL){
        printf("%d ",q->data);
        q = q->next;
    }
    printf("\n");
}

void insertAtRear(int d){
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->data=d;
    temp->next=NULL;
    temp->prev=NULL;

    if(start==NULL){
        start = end = temp;
        // start->next=end;
        // end->prev=start;
        return;
    }

    temp->prev = end;
    end->next=temp;
    end=temp;

}

int deleteFromRear(){
    if(start==NULL){
        printf("Empty List\n");
        return -1;
    }

    int deletedItem = end->data;

    end = end->prev;
    end->next=NULL;

    return deletedItem;
}

void insertAtPos(int d, int pos){
    struct node *temp, *q;
    temp = (struct node*)malloc(sizeof(struct node));

    temp->data=d;
    temp->prev=NULL;
    temp->next=NULL;

    if(pos==1){
        if(start==NULL){
            insertAtRear(d);
        }
        temp->next = start;
        start->prev=temp;
        start=temp;
        return;
    }

    q=start;

    for(int i=0;i<pos-2;i++){
        if(q==NULL || q->next==NULL){
            printf("Invalid Position\n");
            return;
        }
        q = q->next;
    }
    if(q==end){
        insertAtRear(d);
        return;
    }
    temp->prev=q;
    temp->next=q->next;
    q->next=temp;
    temp->next->prev=temp;
}

int delAtPos(int pos){
    struct node *q;
    int deletedItem;
    q=start;

    for(int i=0;i<pos-1;i++){
        if(q==NULL || q->next==NULL){
            printf("Invalid Position\n");
            return;
        }
        q = q->next;
    }
    q->prev->next=q->next;
    q->next->prev=q->prev;
    deletedItem = q->data;
    free(q);

    return deletedItem;
}

void insertAfterAnotherElement(int item, int data){
    struct node *q;
    int pos=1;
    q=start;
    while(q->data != item){
        pos++;
        q= q->next;
    }
    insertAtPos(data,pos+1);
}

void insertBeforeAnotherElement(int item, int data){
    struct node *q;
    int pos=1;
    q=start;
    while(q->data != item){
        pos++;
        q= q->next;
    }
    insertAtPos(data,pos);
}

void traverseList(){
    displayList();
}

void reverseList() {
    struct node *current = start;
    struct node *temp = NULL;

    while (current != NULL) {
        temp = current->next;
        current->next = current->prev;
        current->prev = temp;
        current = temp;
    }

    temp = start;
    start = end;
    end = temp;

    start->prev = NULL;
    end->next = NULL;
}


int main(){

    int choice,data,pos,item;

    while (1)
    {
        printf("\n0. Exit\n1. Insert an element  at the rear end of the  list\n2. Delete an element  from  the rear end of the list\n3. Insert an element  at a given position of the list\n4. Delete an element  from  a given position of the  list\n5. Insert an element  after another  element\n6. Insert an element  before another  element\n7. Traverse the list\n8. Reverse the list\n");

        printf("\nChoice: ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice)
        {
        case 0:
            printf("Exiting...\n");
            return 0;

        case 1:
            printf("Data: ");
            scanf(" %d", &data);
            insertAtRear(data);
            break;

        case 2:
            item = deleteFromRear();
            printf("%d deleted\n", item);
            break;

        case 3:
            printf("Position: ");
            scanf(" %d", &pos);
            printf("Data: ");
            scanf(" %d", &data);
            insertAtPos(data,pos);
            break;

        case 4:
            printf("Position: ");
            scanf(" %d", &pos);
            item = delAtPos(pos);
            printf("%d deleted\n",item);
            break;

        case 5:
            printf("Element to enter after: ");
            scanf(" %d", &item);
            printf("Element to enter: ");
            scanf(" %d", &data);
            insertAfterAnotherElement(item, data);
            break;

        case 6:
            printf("Element to enter before: ");
            scanf(" %d", &item);
            printf("Element to enter: ");
            scanf(" %d", &data);
            insertBeforeAnotherElement(item, data);
            break;

        case 7:
            traverseList();
            break;

        case 8:
            reverseList();
            break;

        default:
        printf("Invalid Choice\n");
            break;
        }
    }


    // insertAtRear(1);
    // insertAtRear(2);
    // insertAtRear(3);
    // // insertAtRear(4);
    // insertAtRear(5);
    // insertAtRear(6);
    // insertAtRear(7);
    // insertAtRear(8);
    // insertAtRear(9);
    // insertAtRear(10);
    // insertAtRear(11);
    // displayList();

    // insertAtPos(4,4);
    // displayList();

    // // delAtPos(5);
    // insertAfterAnotherElement(5,50);
    // displayList();
    // insertBeforeAnotherElement(7,69);
    // displayList();

    // reverse();
    // displayList();

    return 0;
}

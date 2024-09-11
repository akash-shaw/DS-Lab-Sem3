#include<stdio.h>
#include<stdlib.h>
struct  node
{
    int data;
    struct node *prev, *next;
}*start1 = NULL, *end1=NULL;*start2 = NULL, *end2=NULL;

void displayList1(){
    struct node *q=start1;
    while(q!=NULL){
        printf("%d ",q->data);
        q = q->next;
    }
    printf("\n");
}

void insertAtRear1(int d){
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->data=d;
    temp->next=NULL;
    temp->prev=NULL;

    if(start==NULL){
        start1 = end1 = temp;
        // start->next=end;
        // end->prev=start;
        return;
    }

    temp->prev = end1;
    end1->next=temp;
    end1=temp;

}

void displayList2(){
    struct node *q=start2;
    while(q!=NULL){
        printf("%d ",q->data);
        q = q->next;
    }
    printf("\n");
}

void insertAtRear2(int d){
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->data=d;
    temp->next=NULL;
    temp->prev=NULL;

    if(start==NULL){
        start2 = end2 = temp;
        // start->next=end;
        // end->prev=start;
        return;
    }

    temp->prev = end2;
    end2->next=temp;
    end2=temp;

}

void concat(){
    end1->next = start2;
    start2->prev = end1;
    end1 = end2;
}

int main(){
    //TODO
    /*
    switch case with exit,  add for 1, add for 2, display 1, display 2, concat
    */
   return 0;
}
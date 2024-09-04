// https://drive.google.com/drive/folders/11T1i8J8wSxqTFnska4Jh4HQ5xdhB3u23

#include<stdio.h>
#include<stdlib.h>


struct node
{
    int info;
    struct node *link;
}*start;

//int create_list(int),addatbeg(int),addafter(int,int),del(int),display(),count(),rev(),search(int);

//TODO: Check it once
void insertAtPos(int data, int pos){
    if(start==NULL){
        addAtBeg(data);
    }
    struct node *tmp,*q;
    tmp = (struct node *)malloc(sizeof(struct node));

    tmp->info = data;
    tmp->link=NULL;

    q = start;
    int i=0
    while(i<pos){
        i++;
        q = q->link;
    }
    temp->link=q->link;
    q->link=temp;
}
void addAtEnd (int data){
    struct node *q,*tmp;
    tmp=(struct node *) malloc(sizeof(struct node));

    tmp->info=data;
    tmp->link=NULL;

    if(start==NULL){
        start = tmp;
    }
    else{
        q=start;
        while(q->link != NULL){
            q = q->link;
        }
        q->link=tmp;
    }
}

void addAtBeg(int data){
    struct node *tmp;

    tmp =(struct node *)malloc(sizeof(struct node));

    tmp->info =data;
    tmp->link=NULL;

    if(start==NULL)
        start=tmp;
    else{
        tmp->link =start;
        start=tmp;
    }
}

int del(int data)
{
	int found=0;
	struct node *tmp,*q,*pre;
	if(start->info == data)
	{
		tmp=start;
		start=start->link;  /*First element deleted*/
		free(tmp);
		found=1;
	}
	else
	{
		found=0;
		q=start;
		while(q->link!=NULL)
		{

			if(q->info==data)     /*Element deleted in between*/
			{
				found=1;
				pre->link=q->link;
				tmp=q;
				free(tmp);
				break;
			}
			pre=q;
			q=q->link;

        }
		if(q->info==data)    /*Last element deleted*/
		{
			tmp=q;
			free(tmp);
			pre->link=NULL;
			found=1;
		}
	}
	if(found==0){
		printf("Element %d not found\n",data);
	}

}

void delAltNode(){
    struct node *tmp;

    // tmp = (struct node *) malloc(sizeof(struct node));

    tmp = start;

    while(tmp->link!=NULL && tmp->link->link!=NULL){
        tmp->link = (tmp->link)->link;
        tmp=tmp->link;
    }
    tmp->link=NULL;
}

void insertInSorted(int data){
    if(data<start->info){
        addAtBeg(data);
        return;
    }
    struct node *q,*tmp;
    
    q=start;
    while(q->link!=NULL){
        if(q->link->info>=data){
            tmp=(struct node*)malloc(sizeof(struct node));
            tmp->info = data;
            tmp->link=q->link;
            q->link=tmp;
            return;
        }
        q = q->link;
    }
    addAtEnd(data);
}

void display(){
    struct node *tmp;
    tmp = (struct node *)malloc(sizeof(struct node));

    if(start==NULL){
        printf("Empty list\n");
        return;
    }
    tmp=start;
    while(tmp!=NULL){
        printf("%d ",tmp->info);
        tmp = tmp->link;
    }
}

void rev()
{
	struct node *p1,*p2,*p3;
	if(start->link==NULL)    /*only one element*/
        return;

	p1=start;
	p2=p1->link;
	p3=p2->link;
	p1->link=NULL;
	p2->link=p1;
	while(p3!=NULL)
	{
		p1=p2;
		p2=p3;
		p3=p3->link;
		p2->link=p1;
	}
	start=p2;
}
/*
void sort(){
    struct node *tmp;
    if(start==NULL){
        printf("Empty list\n");
        return;
    }
    tmp = start;

}
*/
int main(){

    int choice,n;

    while (1)
    {
        // printf("\ni) Insert an element  before another  element  in the existing  list");
        // printf("\nii) Insert an element  after another  element  in the  existing  list");
        // printf("\niii) Delete a given element  from  the  list");
        // printf("\niv) Traverse the list");
        // printf("\nv) Reverse the list");
        // printf("\nvi) Sort the  list");
        // printf("\nvii) Delete every alternate node in the  list");
        // printf("\nviii) Insert an element  in a sorted list such  that the  order is maintained.");

        printf("\n0. Exit\n1. Insert at end\n2. Insert at start\n3. Delete a given no\n4. Display\n5. Delete alternate nodes\n6. Insert element in sorted list\n7. Reverse");

        printf("\nEnter Choice: ");
        scanf(" %d", &choice);

        switch (choice)
        {
        case 0:
            return 0;
        case 1:
            printf("Data: ");
            scanf("%d",&n);
            addAtEnd(n);
            break;
        case 2:
            printf("Data: ");
            scanf("%d",&n);
            addAtBeg(n);
            break;
        case 3:
            printf("Data: ");
            scanf("%d",&n);
            del(n);
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
            scanf("%d",&n);
            insertInSorted(n);
            break;
        case 7:
            rev();
            break;
        default:
            printf("Wrong choice, try again!\n");
            break;
        }
    }
    return 0;
}

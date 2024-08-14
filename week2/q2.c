#include<stdio.h>

struct student {
    char name[100];
    int rollno;
    int grade;
}s[100];

void read(int n){
    int i;
    for ( i = 0; i < n; i++)
    {
        fflush(stdin);
        printf("Name: ");
        gets(s[i].name);
        fflush(stdin);
        printf("Roll no: ");
        scanf("%d",&s[i].rollno);
        printf("Grade: ");
        scanf("%d",&s[i].grade);
    }
}

void display(int n){
    int i;
    for ( i = 0; i < n; i++)
    {
        printf(" Name: ");
        puts(s[i].name);
        printf(" Roll no: ");
        printf("%d",s[i].rollno);
        printf(" Grade: ");
        printf("%d\n",s[i].grade);
    }
}

void sort(int n){
    int i,j;
    struct student temp;
    for ( i = 0; i < n; i++)
    {
        for (j = 0; j < n-i-1; j++)
        {
            if(s[j].grade>s[j+1].grade){
                temp = s[j];
                s[j]=s[j+1];
                s[j+1]=temp;
            }
        }

    }
}

int main(){

    int n;
    printf("Enter number of students: ");
    scanf("%d",&n);
    read(n);
    printf("Entered details: \n");
    display(n);
    sort(n);
    printf("After sorting: \n");
    display(n);
}

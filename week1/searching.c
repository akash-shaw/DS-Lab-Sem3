#include<stdio.h>
/*
int isSorted(int* arr, int len){
    int i;
    if( arr[1]>arr[0]){
        for(i=1;i<len;i++){
            if(*(arr+i)<*(arr+i))
        }
    }
    for(i=0;i<len;i++){
    }
}
*/
int linearSearch(int* arr, int len, int key){
    int i;
    for(i=0;i<len;i++){
        if(key==arr[i]){
            return i+1;
        }
    }
    return 0;
}

int binarySearch(int *arr, int len, int key){
    
    int i;
    int left = 0, right = len-1, mid;
    while (left!=right)
    {
        mid = (left+right)/2;
        if (arr[mid]==key)
        {
            return mid+1;
        }
        else if (arr[mid]>key)
        {
            right = mid-1;
        }
        else{
            left = mid+1;
        }
    }
    return 0;    
}

int main(){
    int len;
    int arr[100];
    int key, pos, i;
    printf("Enter array length: ");
    scanf("%d",&len);
    printf("Enter array elements: ");
    for ( i = 0; i < len; i++)
    {
        scanf(" %d", &arr[i]);
    }
    printf("Entered array: ");
    for ( i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\nEnter item to search: ");
    scanf("%d", &key);


    pos = binarySearch(arr,len,key);
    pos = linearSearch(arr,len,key);
    
    
    if(pos){
        printf("%d found at position %d\n",key,pos);
    }
    else{
        printf("%d not found\n",key);
    }
    return 0;
}

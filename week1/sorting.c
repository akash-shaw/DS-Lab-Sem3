#include<stdio.h>

void bubbleSort(int* arr, int len){
    int i,j,temp;

    for ( i = 0; i < len-1; i++){
        for ( j = 0; j < len-i-1; j++){
            if(arr[j]>arr[j+1]){
                temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }

}

void selectionSort(int* arr, int len){
    int i, j, imin, temp;
    for(i = 0; i<len-1; i++) {
        imin = i;
        for(j = i+1; j<len; j++){
            if(arr[j] < arr[imin]){
                imin = j;
            }
        }
        temp = arr[i];
        arr[i] = arr[imin];
        arr[imin] = temp;
   }
}

void insertionSort(int* arr, int len){
    int i,j;
    int key;
    for ( j = 0; j < len; j++){
        key=arr[j];
        for ( i = j-1; i >=0 && arr[i]>key; i--){
            arr[i+1]=arr[i];
        }
        arr[i+1]=key;
    }
}

int main(){
    int len;
    int arr[100];
    int i;

    printf("Enter array length: ");
    scanf("%d",&len);

    printf("Enter array elements: ");
    for ( i = 0; i < len; i++){
        scanf(" %d", &arr[i]);
    }

    printf("Entered array: ");
    for ( i = 0; i < len; i++){
        printf("%d ", arr[i]);
    }

    // bubbleSort(arr, len);
    // selectionSort(arr, len);
    insertionSort(arr, len);

    printf("\nSorted array: ");
    for ( i = 0; i < len; i++){
        printf("%d ", arr[i]);
    }
    
    return 0;
}

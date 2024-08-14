#include<Stdio.h>

#define MAX_SIZE 100

struct sparse_matrix
{
    // int rows;
    // int cols;
    // int items;
    int sm[3][MAX_SIZE];
};

void initSP(struct sparse_matrix *sparse_matrix){
    int m,n,items;
    printf("Enter no of rows: ");
    scanf("%d",&m);
    printf("Enter no of columns: ");
    scanf("%d",&n);
    printf("Enter no of items: ");
    scanf("%d",&items);
    sparse_matrix->sm[0][0] = m;
    sparse_matrix->sm[1][0] = n;
    sparse_matrix->sm[2][0]= items;
}

void insertSP(struct sparse_matrix *sparse_matrix){
    int row, column, value;

    for (int i = 1; i <= sparse_matrix->sm[2][0]; i++)
    {
        printf("%d. Enter row, column, value: ",i);
        scanf(" %d %d %d", &row, &column, &value);

        sparse_matrix->sm[0][i] = row-1;
        sparse_matrix->sm[1][i] = column-1;
        sparse_matrix->sm[2][i] = value;

    }

}


void displaySP(struct sparse_matrix *sparse_matrix){

    // for (int j = 0; j < 3; i++)
    // {
    //     for (int i = 0; i < sparse_matrix->sm[2][0]+1; j++)
    //     {
    //         printf("%d\t",sparse_matrix->sm[i][j]);
    //     }
    //     printf("\n");
    // }


    int a[ sparse_matrix->sm[0][0] ][ sparse_matrix->sm[1][0] ];
    for (int i = 0; i < sparse_matrix->sm[0][0]; i++)
    {
        for (int j = 0; j < sparse_matrix->sm[1][0]; j++)
        {
            a[i][j]=0;
        }
    }

    for (int i = 1; i <= sparse_matrix->sm[2][0]; i++)
    {
        a[ sparse_matrix->sm[0][i] ][ sparse_matrix->sm[1][i] ] = sparse_matrix->sm[2][i];
    }

    for (int i = 0; i < sparse_matrix->sm[0][0]; i++)
    {
        for (int j = 0; j < sparse_matrix->sm[1][0]; j++)
        {
            printf("%d\t", a[i][j]);
        }
        printf("\n");
    }
}

void fastTransposeSP(struct sparse_matrix *sparse_matrix){

}


int main(){

    struct sparse_matrix sparse_matrix;

    initSP(&sparse_matrix);
    insertSP(&sparse_matrix);
    displaySP(&sparse_matrix);

    return 0;
}

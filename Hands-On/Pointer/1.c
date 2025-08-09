#include<stdio.h>
#include<stdlib.h>

void print_array(int ** a, int m, int n){
    for(int i = 0; i<m; i++){
        for(int j  = 0; j<n; j++){
            printf("%d ", *(*(a+i)+j));
        }
        printf("\n");
    }
}

void swap_row(int ** a, int x, int y){
    int diff = *(a+y)-*(a+x);

    *(a+x) = *(a+x) + diff;
    *(a+y) = *(a+y) - diff;
}

void swap_col(int ** a, int x, int y, int m, int n){
    for(int i = 0; i<m; i++){
        int t = *(*(a+i)+x);
        *(*(a+i)+x) = *(*(a+i)+y);
        *(*(a+i)+y) = t;
        
    }
}

int main(){
    int m, n;
    scanf("%d %d", &m, &n);
    int ** num = (int **) malloc(m*sizeof(int *));

    for(int i = 0;i<m;i++){
        *(num+i) = (int *) malloc(n*sizeof(int));
    }

    for(int i = 0; i<m; i++){
        for(int j  = 0; j<n; j++){
            scanf("%d", *(num+i)+j);
        }
    }

    int max = **(num);
    int min = **(num);

    for(int i = 0; i<m; i++){
        for(int j  = 0; j<n; j++){
            if(*(*(num+i)+j)>max){
                max = *(*(num+i)+j);
            }
            if(*(*(num+i)+j)<min){
                min = *(*(num+i)+j);
            }
        }
    }


    printf("max: %d min: %d\n", min, max);

    int row_x, row_y;
    printf("Enter two rows to swap:");
    scanf("%d %d", &row_x, &row_y);

    swap_row(num, row_x, row_y);
    print_array(num, m, n);

    int col_x, col_y;
    printf("Enter two cols to swap:");
    scanf("%d %d", &col_x, &col_y);

    swap_col(num, col_x, col_y, m, n);
    print_array(num, m, n);

    for(int i = 0; i<m; i++){
        free(*(num+i));
    }
    free(num);
    return 0;
}
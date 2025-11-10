#include<stdio.h>
#include<stdlib.h>

void sort_col(int ** a, int m, int n){
    for(int i = 0;i<n; i++){
        for(int j = 0; j<m;j++){
            int min = *(*(a+j)+i);
            int min_idx = j;
            for(int k = j+1; k<m;k++){
                if(*(*(a+k)+n) < min){
                    min = *(*(a+k)+i);
                    min_idx = k;
                }
            }
            *(*(a+min_idx)+i) = *(*(a+j)+i);
            *(*(a+j)+i) = min;
            
        }
    }
}


void print_array(int ** a, int m, int n){
    for(int i = 0; i<m; i++){
        for(int j  = 0; j<n; j++){
            printf("%d ", *(*(a+i)+j));
        }
        printf("\n");
    }
}


int main(){
    int m,n;
    scanf("%d %d", &m, &n);
    int ** a = (int **) malloc(m*sizeof(int *));
    for(int i = 0;i < m; i++){
        *(a+i) = (int *) malloc(n*sizeof(int));
    }

    for(int i = 0; i<m; i++){
        for(int j  = 0; j<n; j++){
            scanf("%d", *(a+i)+j);
        }
    }

    
    for(int i = 0;i<n; i++){
        for(int j = 0; j<m;j++){
            int min = *(*(a+j)+i);
            int min_idx = j;
            for(int k = j+1; k<m;k++){
                if(*(*(a+k)+i) < min){
                    min = *(*(a+k)+i);
                    min_idx = k;
                }
            }
            *(*(a+min_idx)+i) = *(*(a+j)+i);
            *(*(a+j)+i) = min;
            
        }
    }
    
    printf("\n");
    print_array(a, m, n);

    for(int i = 0; i<m; i++){
        free(*(a+i));
    }
    free(a);
    return 0;
}
#include<stdio.h>
#include<stdlib.h>

void transpose(int ** a, int ** ans, int m, int n){
    for(int i=0;i<m;i++){
        for(int j = 0; j<n; j++){
            *(*(ans+j)+i) = *(*(a+i)+j);
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
    int m, n;
    scanf("%d %d", &m, &n);
    
    int ** num = (int **) malloc(m*sizeof(int*));
    for(int i = 0;i<m;i++){
        *(num+i) = (int *) malloc(n*sizeof(int));
    }
    

    for(int i = 0; i<m; i++){
        for(int j  = 0; j<n; j++){
            scanf("%d", *(num+i)+j);
        }
    }

    int ** trn = (int **) malloc(n*sizeof(int *));
    for(int i = 0;i<n;i++){
        *(trn+i) = (int *) malloc(m*sizeof(int));
    }

    transpose(num, trn, m, n);
    print_array(trn, n, m);

    for(int i = 0; i<m; i++){
        free(*(num+i));
    }
    free(num);

    for(int i = 0; i<n; i++){
        free(*(trn+i));
    }
    free(trn);
    return 0;
}
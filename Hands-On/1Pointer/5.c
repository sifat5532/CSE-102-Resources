#include<stdio.h>
#include<stdlib.h>

int get_sum(int ** a, int ** kernel,int start_m,int start_n,int k){
    int sum = 0;
    int kernel_m_c = 0;
    for(int i = start_m; i<(start_m+k); i++){
        int kernel_n_c = 0;
        for(int j = start_n; j<(start_n+k); j++){
            sum = sum + (*(*(a+i)+j))*(*(*(kernel+kernel_m_c)+kernel_n_c));
            kernel_n_c++;
        }
        kernel_m_c++;
    }
    return sum;
}

void get_sub_array(int ** a, int ** kernel,int ** out, int m, int n, int k){
    for(int i = 0; (i+k)<=m; i++){
        for(int j = 0; (j+k)<=n; j++){
            *(*(out+i)+j) = get_sum(a, kernel, i, j, k);
        }
    }
}

void free_mem(int ** a, int m){
    for(int i = 0; i<m ; i++){
        free(*(a+i));
    }
    free(a);
}

void print_array(int ** a, int m, int n){
    for(int i = 0; i<m; i++){
        for(int j = 0; j<n; j++){
            printf("%d ", *(*(a+i)+j));
        }
        printf("\n");
    }
}

int main(){
    int m, n, k;
    scanf("%d %d", &m, &n);
    int ** a = (int **) malloc(m*sizeof(int *));
    for(int i = 0; i<m; i++){
        *(a+i) = (int *) malloc(n*sizeof(int));
    }

    for(int i = 0; i<m; i++){
        for(int j= 0; j<n; j++){
            scanf("%d", *(a+i)+j);
        }
    }

    printf("Enter the num k: ");
    scanf("%d", &k);

    int ** kernel = (int **) malloc(k*sizeof(int *));
    for(int i = 0; i<k; i++){
        *(kernel+i) = (int *) malloc(k*sizeof(int));
    }

    for(int i = 0; i<k; i++){
        for(int j= 0; j<k; j++){
            scanf("%d", *(kernel+i)+j);
        }
    }

    int ** out = (int **) malloc((m-k+1)*sizeof(int *));
    for(int i = 0; i<(m-k+1); i++){
        *(out+i) = (int *) malloc((n-k+1)*sizeof(int));
    }

    get_sub_array(a, kernel, out, m, n, k);
    printf("\n");
    print_array(out, m-k+1, n-k+1);

    free_mem(a, m);
    free_mem(kernel, k);
    free_mem(out, m-k+1);
    
    return 0;
}
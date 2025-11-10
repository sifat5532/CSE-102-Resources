#include <stdio.h>
#include <stdlib.h>
void rotate(int **arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            int t = *(*(arr + i) + j);
            *(*(arr + i) + j) = *(*(arr + j) + i);
            *(*(arr + j) + i) = t;
        }
    }

    // now rotate col
    for (int i = 0; i <= (n / 2) - 1; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int t = *(*(arr + j) + i);
            *(*(arr + j) + i) = *(*(arr + j) + n - 1 - i);
            *(*(arr + j) + n - 1 - i) = t;
        }
    }
}
int main()
{
    int n;
    scanf("%d", &n);
    int **arr = (int **)malloc(n * sizeof(int *));

    for (int i = 0; i < n; i++)
    {
        *(arr + i) = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++)
        {
            scanf("%d", (*(arr + i) + j));
        }
    }
    rotate(arr, n);
    // print matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", *(*(arr + i) + j));
        }
        printf("\n");
    }

    // free memory
    for (int i = 0; i < n; i++)
    {
        free(*(arr + i));
    }
    free(arr);
    return 0;
}
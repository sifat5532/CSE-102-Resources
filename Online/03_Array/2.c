#include<stdio.h>
int main(){
    int n1;
    scanf("%d", &n1);
    int a[n1];
    for(int i = 0; i<n1; i++){
        scanf("%d", &a[i]);
    }
    int n2;
    scanf("%d", &n2);
    int b[n2];
    for(int i = 0; i<n2; i++){
        scanf("%d", &b[i]);
    }

    int min, max, large_array;

    if(n1>=n2){
        max = n1;
        min = n2;
        large_array = 1;

    }else{
        max = n2;
        min = n1;
        large_array = 2;
    }
    int hand = 0;
    int ans[max+1];
    ans[max] = -1;


    for(int i = 0; i<max+1; i++){
        if(i<=min-1){
            ans[i] = (a[i] + b[i]+hand)%10;
            hand = (a[i] + b[i]+hand)/10;
        }else if(i<max){
            if(large_array == 1){
                ans[i] = (a[i] + hand)%10;
                hand = (a[i] + hand)/10;
            }else{
                ans[i] = (b[i] + hand)%10;
                hand = (b[i] + hand)/10;
            }
        }else{
            if(hand!=0){
                ans[i] = hand;
            }
        }


    }

    if(ans[max] == -1){
        for(int i = 0; i< max; i++){
        printf("%d ", ans[i]);
        }
    }else{
        for(int i = 0; i< max+1; i++){
        printf("%d ", ans[i]);
        }
    }

    return 0;
}

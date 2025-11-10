#include<stdio.h>
int main(){
    int n;
    scanf("%d", &n);
    int a[n];
    for(int i=0; i<n; i++){
        scanf("%d", &a[i]);
    }
    int max_area = 0;
    int w, h;
    for(int i=0; i<n; i++){
        for(int j =i+1; j<n; j++){
            w = j-i;
            if(a[i]>=a[j]){
                h = a[j];
            }else{
                h = a[i];
            }

            int area = w*h;
            if(area>max_area){
                max_area = area;
            }
        }
    }
    printf("%d", max_area);
    return 0;
}

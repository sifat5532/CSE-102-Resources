#include<stdio.h>
int main(){
    int n;
    scanf("%d",&n);
    int t = n;
    int a = n%10; n = n/10;
    int b = n%10; n = n/10;
    int c = n%10;
    if( t == (a*a*a + b*b*b + c*c*c)){
        printf("Armstrong Number\n");
    }else{
        printf("Not Armstrong Number\n");
    }
    return 0;
}
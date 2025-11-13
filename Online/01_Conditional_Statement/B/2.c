#include<stdio.h>

int main(){
    int x1, y1, x2, y2, x3, y3, x4, y4;
    scanf("%d %d\n%d %d\n%d %d\n%d %d", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);
    float m1, m2;
    if(x1-x2 == 0 || x3-x4 == 0){
        if(x1-x2 == 0 && x3-x4 == 0){
            if(x1 == x3){
                printf("Coincident\n");
            }else{
                printf("Parallel\n");
            }
        }else{
            printf("Intersecting\n");
        }
    }else{
        m1 = (y2-y1)/(x2-x1);
        m2 = (y4-y3)/(x4-x3);
        if(m1 != m2){
            printf("Intersecting\n");
        }else{
            if((y3-y1)-m1*(x3-x1) == 0){
                printf("Coincident\n");
            }else{
                printf("Parallel\n");
            }
        }
    }
    return 0;
}
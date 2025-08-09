#include<stdio.h>
int main(){
    int n;
    scanf("%d", &n);
    int i;
    int total_en = 0;
    for(i=1;i<=n;i++){
        int sum =0, alt_sum = 0, odd_sum = 0, even_sum = 0;
        int c = 1;
        int reverse_num = 0;
        int cond_satis = 0;
        int en_level = 0;
        int k, x;
        scanf("%d", &k);
        while(k--){
            scanf("%d", &x);
            sum = sum+x;
            if(c%2==0){
                even_sum = even_sum + x;
                alt_sum = alt_sum - x;
            }else{
                odd_sum = odd_sum + x;
                alt_sum = alt_sum + x;
            }
            c++;
        }
        // prime-active chk
        int divisors =  0;
        
        for(c=1;c*c<sum;c++){
            if(sum%c == 0){
                divisors += 2;
            }
        }
        if(c*c==sum){
            divisors++;
        }
        if(divisors == 2){
            en_level += 5;
            cond_satis++;
        }

        // palindrome-active chk
        int sum_temp = sum;
        while(sum_temp>0){
            reverse_num = reverse_num*10 + (sum_temp%10);
            sum_temp /=10;
        }
        if(reverse_num == sum){
            en_level += 3;
            cond_satis++;
        }

        // harmonic chk
        if(alt_sum%7 == 0){
            en_level += 4;
            cond_satis++;
        }

        // balanced chk

        if(odd_sum == even_sum){
            en_level += 2;
            cond_satis++;
        }

        // final ans

        if(cond_satis == 4){
            printf("Row %d: ULTRA - Energy Level %d\n", i, en_level);
        }else if(cond_satis == 3){
            printf("Row %d: HIGH - Energy Level %d\n", i, en_level);
        }else if(cond_satis == 2){
            printf("Row %d: MEDIUM - Energy Level %d\n", i, en_level);
        }else if(cond_satis == 1){
            printf("Row %d: LOW - Energy Level %d\n", i, en_level);
        }else{
            printf("Row %d: INACTIVE - Energy Level %d\n", i, en_level);
        }

        total_en = total_en + en_level;
        
    }
    
    printf("Total Energy: %d", total_en);

    return 0;
}

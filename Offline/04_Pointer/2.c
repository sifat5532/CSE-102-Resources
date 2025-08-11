#include<stdio.h>
#include<stdlib.h>

#define wordLength 25

void wordSwap(char ** a, char ** b){
    int diff = *b-*a;
    *a = *a+diff;
    *b = *b-diff;
}

void wordCmpr(char ** x, char ** y){
    int no_diff = 0;

    for(int i = 0;i < wordLength; i++){
        if(*(*x+i) == '.' || *(*y+i) == '.'){
            if(no_diff == 1){
                if(*(*y+i) == '.' && *(*x+i) != '.'){
                    wordSwap(x, y);
                    break;
                }else{
                    break;
                }
            }else{
                break;
            }
        }else{
            if(*(*x+i) > *(*y+i)){
                wordSwap(x, y);
                break;
            }else if(*(*x+i) < *(*y+i)){
                break;
            }else{
                no_diff = 1;
            }
        }
    }
}

int main(){
    int n;
    scanf("%d", &n);

    char ** words = (char **) malloc(n *  sizeof(char *));

    for(int i = 0; i<n; i++){
        *(words+i) = (char *) malloc(wordLength*sizeof(char));
        scanf("%s", *(words+i));
    }



    for(int i = 0; i<n-1; i++){
        for(int j = 0; j<(n-i-1); j++){
            wordCmpr((words+j), (words+j+1));
        }
    }

    printf("\n");
    for(int i = 0; i<n; i++){
        printf("%s\n", *(words+i));
    }

    for(int i = 0; i<n; i++){
        free(*(words+i));
    }
    free(words);
    return 0;
}
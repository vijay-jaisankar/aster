#include<stdio.h>
#include<stdlib.h>

int main(void){
    int x = 5;
    x&=x;
    x = x &3;
    int y = 1 && 0;
    int z = 1 || 0;
    int comp = 2 <<3;
    int comp2 = 2 > 3;
    if(x!=5){
        printf("x is not 5\n");
    }
    else{
        printf("x is 5\n");
    }
}
#include <stdio.h>
#include <stdlib.h>

int main(void){
    int x =4;
    x ^=x;
    int y = x ^2;
    y = y%3;
    y %=2;
    return 0;
}

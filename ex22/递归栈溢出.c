#include<stdio.h>

int add_1(int start){
    start += 1;
    return add_1(start);
}

int main(void){
    int start = 1;
    add_1(start);
    return 0;
}
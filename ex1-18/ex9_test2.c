#include <stdio.h>

int main(void){
    
    char arr[5] = {'1', '2','3', '4', '\0'};
    char* p = arr;
    char* p2 = arr;
    for(int i = 0; i < sizeof(arr); i++){
        
        printf("%c",*p);
        p++;
    }

    printf("\n");
    printf("%s\n", p2);
    return 0;
}
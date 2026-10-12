#include<stdio.h>

char full_name[] = {
        'Z','e','d',
        ' ','A','.',' ',
        'S','h','a', 'w','\0'
    };

int main(void){
    
    char name[] = "Zed";
    int areas[] = {10,12,13,14,20};

    //这里我不用依据注释更改代码，因为linux是支持%ld的
    printf("the size of an int: %ld\n",sizeof(int));
    printf("the size of areas (int[]]): %ld\n",
        sizeof(areas));
    printf("the numbers of ints i nareas: %ld\n",
        sizeof(areas)/sizeof(int));
    printf("the first areas is %d, the 2nd %d .\n",
        areas[0], areas[1]);
    printf("the size of a char :%ld\n",sizeof(char));
    printf("the size of name (char[]): %ld\n",
    sizeof(name));
    printf("the number of chars: %ld\n",
    sizeof(name)/sizeof(char));
    printf("the size of full_name (char[]): %ld\n",
    sizeof(full_name));
    printf("the number of chars: %ld\n",
    sizeof(full_name)/sizeof(char));
    printf("name = \"%s\" and full_name = \"%s\"\n",
    name, full_name);
    
    return 0;

}
#include<stdio.h>

int main(void){

    int numbers[4] = {'G', 'o', 'D'};
    char name[4] = {'1', '2', '3', '4'};

    //首先，把它们打印出来
    printf("%d",numbers[0]);
    printf("%d",numbers[1]);
    printf("%d",numbers[2]);

    printf("%d",name[0]);
    printf("%d",name[1]);
    printf("%d",name[2]);

    printf("name each: %c %c %c %c\n",name[0], name[1], name[2], name[3]);

    printf("name:%s\n",name);

    //设置数字
    numbers[0] = 'G';
    numbers[1] = 'p';
    numbers[2] = 3;
    numbers[3] = 4;

    //setup the name
    name[0] = 'Z';
    name[1] = 'e';
    name[2] = 'd';
    name[3] = 'A';
    
    //然后打印出被初始化后的它们
    printf("numbers: %d %d %d %d\n",numbers[0], numbers[1], numbers[2], numbers[3]);
    printf("name each: %c %c %c %c\n",name[0], name[1], name[2], name[3]);

    printf("name:%s\n",name);
    //使用名字的另一种方法
    char *another = "Zed";

    printf("another: %s\n",another);

    printf("another each: %c %c %c %c\n",another[0], another[1],another[2],another[3]);
    return 0;
    
}
#include <stdio.h>

int main(int argc, char *argv[]){
    int i = 0;

    //遍历argv中的每一个字符串
    //为什么我要跳过argv[0]呢？
    for(i = 0; i < argc; i++){
        printf("arg %d:%s\n", i, argv[i]);
    }

    //让我们来写我们自己的字符串数组
    char *states[] = {
        "California","Oregon",
        "Washington", "Texas"
    };
    int num_states = 4;

    for(i = 0; i < num_states; i++){
        printf("state %d:%s\n", i, states[i]);

    }
    return 0;

}
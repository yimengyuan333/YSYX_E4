#include <stdio.h>

int main(int argc, char *argv[])
{
    // go through each string in argv

    int i = argc;
    while(i != 0) {
        printf("arg %d: %s\n", i, argv[i]);
        i--;
    }

    // let's make our own array of strings
    char *states[] = {
        "California", "Oregon",
        "Washington", "Texas"
    };

    int num_states = 4;
    i = 0;  // watch for this
    while(i < num_states) {
        printf("state %d: %s\n", i, states[i]);
        i++;
    }

    int j = 1;

    printf("下面将argv的内容赋值给states。\n");
    while (j <= 4){
        states[j] = argv[j];//其实这里没对齐，但是无所谓了，学习原理即可
        printf("new states %d: %s\n", j, states[j]);
        j++; 
    }
    
    return 0;
}
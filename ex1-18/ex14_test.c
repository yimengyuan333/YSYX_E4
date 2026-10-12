#include <stdio.h>
#include <ctype.h>

void print_arguments(int argc, char *argv[])    //别忘了argv是二维数组
{
    for (int i = 0; i < argc; i++) {
        for (int j = 0; argv[i][j] != '\0'; j++) {
            char ch = argv[i][j];
            if (isalpha(ch) || isblank(ch)) {
                printf("'%c' == %d ", ch, ch);
            }
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    print_arguments(argc, argv);
    return 0;
}
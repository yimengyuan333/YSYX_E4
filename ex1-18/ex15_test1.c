#include <stdio.h>

int main(int argc, char* argv[]){
    //创建两个我们关心的数组
    int ages[] = {23, 43, 12, 89, 2};
    char *names[] = {
        "Alan", "Frank",
        "Mary", "John", "Lisa"
    };

    char** arg_p = argv;

    int count = sizeof(ages) / sizeof(int);
    int i = 0;

    //第一种方式:用索引
    for(i = 0; i < count; i++){
        printf("%s has %d years alive.\n",
        names[i], ages[i]);
    }

    printf("---\n");

    //设置指向数组开头的指针
    int *cur_age = ages;
    char **cur_name = names;
    int *fake_cur_age = ages;   //假装使用了指针，后面把这个指针当数组用了
    char **fake_cur_name = names;
//cur_name是二层指针，对其赋值的是names，即names
//的第一个元素names[0]的地址，则*cur_name是一层指针，是names[0]本身，但是names[0]本身
//也是一个地址，指向'A'，因此**cur_name就是'A'
//然而，我们不需要精确访问每一个字符，只需要一层指针，用于传给%s即可

    //第二种方式：使用指针，此处倒打印
    for(i = count - 1; i >= 0; i--) {
        printf("%s(%p)) is %d(%p)) years old.\n",
                *(cur_name+i), (cur_name + i), *(cur_age+i), (cur_age + i));
    }

    printf("---\n");

    //第三种方法：二级指针可以直接当指针数组用，但是注意！
    //一级指针不能直接当数组用。
    for(i = 0; i < count; i++) {
        printf("%s is %d years old again.\n",
                cur_name[i], cur_age[i]);
    }

    printf("---\n");

    //再写一个用数组替代指针的
    for(i = 0; i < count; i++){
        printf("Hi ! %s is %d years old okey.\n", fake_cur_name[i], fake_cur_age[i]);
    }

    printf("---\n");
    for(int i = 0; i < argc; i++, arg_p++){
        printf("this argument is %s\n", *arg_p);
    }

    return 0;
}
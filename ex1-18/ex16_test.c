#include <stdio.h>
#include <assert.h>
#include <string.h>

struct Person {
    char *name;//注意是一个指针
    int age;
    int height;
    int weight;
};

struct Person Person_create(char *name, int age, int height, int weight)
{
    struct Person who;

    who.name = strdup(name);//返回一个指针
    who.age = age;
    who.height = height;
    who.weight = weight;

    return who;
}

void Person_print(struct Person who){
    printf("Name:%s\n", who.name);
    printf("\tAge:%d\n", who.age);
    printf("\theight:%d\n", who.height);
    printf("\tWeight:%d\n", who.weight);
}

int main(int argc, char *argv[]){
    //创造两个人的结构体
    struct Person joe = Person_create("joe Alex", 32, 64, 140);

    struct Person frank = Person_create("Frank Blank", 20, 72, 180);

    //把他们和他们所在的内存打印出来
    printf("Joe is at memory location %p \n", &joe);
    Person_print(joe);

    printf("Frank is at memory location %p \n", &frank);
    Person_print(frank);

    //给每个人设置加20岁，然后重新打印
    printf("----------------\n");
    joe.age += 20;
    joe.height -= 2;
    joe.weight += 40;
    Person_print(joe);

    frank.age += 20;
    frank.weight += 20;
    Person_print(frank);

    //删除他们(注释掉来调试)
    // Person_destroy(joe);
    // //Person_destroy(NULL);
    // Person_destroy(frank);

    return 0;
}
#include <stdio.h>
//这个文件将用函数封装两种打印的方法，在main函数中调用
int print_by_index(int num_of_ele, char** name_arr, int* age_arr){
    int i = 0;
    for(i = 0; i < num_of_ele; i++){
        printf("%s has %d years alive.\n", name_arr[i], age_arr[i]);
    }
    printf("---\n");
    return 0;
}

int print_by_point(int num_of_ele, char** name_arr, int* age_arr){
    int i = 0;
    for(i = 0; i < num_of_ele; i++){
        printf("%s is %d years old.\n", *(name_arr + i), *(age_arr + i));
    }
    printf("---\n");
    return 0;
}

int main(int argc, char *argv[])
{
    // create two arrays we care about
    int ages[] = {23, 43, 12, 89, 2};
    char *names[] = {
        "Alan", "Frank",
        "Mary", "John", "Lisa"
    };

    print_by_index(sizeof(ages)/sizeof(ages[0]), names, ages);
    printf("---\n");
    print_by_point(sizeof(ages)/sizeof(ages[0]), names, ages);

    return 0;
}
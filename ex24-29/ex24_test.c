#include <stdlib.h>
#include <stdio.h>
#include "dbg.h"
#include <ctype.h>//isspace判断一个字符是否为空白

#define MAX_DATA 100

typedef enum EyeColor {
    BLUE_EYES, GREEN_EYES, BROWN_EYES,
    BLACK_EYES, OTHER_EYES
} EyeColor;

const char *EYE_COLOR_NAMES[] = {
    "Blue", "Green", "Brown", "Black", "Other"
};

typedef struct Person {
    int age;
    char first_name[MAX_DATA];
    char last_name[MAX_DATA];
    EyeColor eyes;
    float income;
} Person;

static void remove_whitespace(char *s)
{
    char *dst = s;
    for (; *s != '\0'; s++) {
        if (!isspace((unsigned char)*s)) {
            *dst++ = *s;
        }
    }
    *dst = '\0';//末尾手动补\0
}
//第三个作业
int read_file_to_string(const char *filename, char *buffer, int size)
{
    // 参数校验
    if(filename == NULL || buffer == NULL || size <= 0) {
        return -1;
    }

    FILE *fp = fopen(filename, "r");
    if(fp == NULL) {
        buffer[0] = '\0';   // 即使失败也保证字符串合法
        return -1;
    }

    int counter = 0;
    char ch;

    while(counter < size - 1){
        if(fscanf(fp, "%c", &ch) != 1){
            break;
        }

        buffer[counter] = ch;
        counter++;
    }

    buffer[counter] = '\0';
    fclose(fp);
    return counter;
}

int main(int argc, char *argv[])
{
    Person you = {.age = 0};
    int i = 0;
    char *in = NULL;

    printf("What's your First Name? ");
    in = fgets(you.first_name, MAX_DATA-1, stdin);
    remove_whitespace(you.first_name);
    check(in != NULL, "Failed to read first name.");

    printf("What's your Last Name? ");
    in = fgets(you.last_name, MAX_DATA-1, stdin);
    remove_whitespace(you.last_name);
    check(in != NULL, "Failed to read last name.");

    printf("How old are you? ");
    int rc = scanf("%d", &you.age);
    check(rc > 0, "You have to enter a number.");

    printf("What color are your eyes:\n");
    for(i = 0; i <= OTHER_EYES; i++) {
        printf("%d) %s\n", i+1, EYE_COLOR_NAMES[i]);
    }
    printf("> ");

    int eyes = -1;
    rc = scanf("%d", &eyes);
    check(rc > 0, "You have to enter a number.");

    you.eyes = eyes - 1;
    check(you.eyes <= OTHER_EYES && you.eyes >= 0, "Do it right, that's not an option.");

    printf("How much do you make an hour? ");
    rc = scanf("%f", &you.income);
    check(rc > 0, "Enter a floating point number.");

    printf("----- RESULTS -----\n");

    printf("First Name: %s", you.first_name);
    printf("Last Name: %s", you.last_name);
    printf("Age: %d\n", you.age);
    printf("Eyes: %s\n", EYE_COLOR_NAMES[you.eyes]);
    printf("Income: %f\n", you.income);

    return 0;
error:

    return -1;
}
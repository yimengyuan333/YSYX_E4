#include <stdlib.h>
#include <stdio.h>
#include "dbg.h"

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


int main(int argc, char *argv[])
{
    Person you = {.age = 0};
    int i = 0;
    char *in = NULL;

    printf("What's your First Name? ");
    in = fgets(you.first_name, MAX_DATA-1, stdin);
    check(in != NULL, "Failed to read first name.");

    printf("What's your Last Name? ");
    in = fgets(you.last_name, MAX_DATA-1, stdin);
    check(in != NULL, "Failed to read last name.");

    printf("How old are you? ");
    
    char *buf1 = NULL;
    buf1 = malloc(MAX_DATA);//有点浪费
    fgets(buf1, MAX_DATA - 1, stdin);
    int rc = atoi(buf1);
    check(rc > 0, "You have to enter a number.");
    you.age = rc;

    printf("What color are your eyes:\n");
    for(i = 0; i <= OTHER_EYES; i++) {
        printf("%d) %s\n", i+1, EYE_COLOR_NAMES[i]);
    }
    printf("> ");

    int eyes = -1;
    char *buf2 = NULL;
    buf2 = malloc(MAX_DATA);
    fgets(buf2, MAX_DATA - 1, stdin);
    rc = atoi(buf2);
    check(rc > 0, "You have to enter a number.");
    eyes = rc;

    you.eyes = eyes - 1; 
    check(you.eyes <= OTHER_EYES && you.eyes >= 0, "Do it right, that's not an option.");

    printf("How much do you make an hour? ");
    char *buf3 = NULL;
    buf3 = malloc(MAX_DATA);
    fgets(buf3, MAX_DATA - 1, stdin);
    double rcc = atof(buf3);
    check(rcc >= 0, "Enter a floating point number.");
    you.income = rcc;

    printf("----- RESULTS -----\n");

    printf("First Name: %s", you.first_name);
    printf("Last Name: %s", you.last_name);
    printf("Age: %d\n", you.age);
    printf("Eyes: %s\n", EYE_COLOR_NAMES[you.eyes]);
    printf("Income: %f\n", you.income);

    free(buf1);
    free(buf2);
    free(buf3);

    return 0;
error:
    free(buf1);
    free(buf2);
    free(buf3);
    return -1;
}
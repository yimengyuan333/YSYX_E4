#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/** Our old friend die from ex17. */
void die(const char *message)
{
    if(errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    exit(1);
}

static void swap(void *a, void *b, size_t size)
{
    char temp;
    char *p1 = (char *)a;
    char *p2 = (char *)b;

    for (size_t i = 0; i < size; i++) {
        temp = p1[i];
        p1[i] = p2[i];
        p2[i] = temp;
    }
}


// a typedef creates a fake type, in this
// case for a function pointer
typedef int (*compare_cb)(int a, int b);

/**
 * A classic bubble sort function that uses the
 * compare_cb to do the sorting.
 */
int *bubble_sort(int *numbers, int count, compare_cb cmp)
{
    int temp = 0;
    int i = 0;
    int j = 0;
    int *target_b = malloc(count * sizeof(int));

    if(!target_b) die("Memory error.");

    memcpy(target_b, numbers, count * sizeof(int));

    for(i = 0; i < count; i++) {
        for(j = 0; j < count - 1; j++) {
            if(cmp(target_b[j], target_b[j+1]) > 0) {
                temp = target_b[j+1];
                target_b[j+1] = target_b[j];
                target_b[j] = temp;
            }
        }
    }

    return target_b;
}

int *qucik_sort(void *base_addr, int count, compare_cb cmp)
{
    int *target_q = malloc(count * sizeof(int));
    if(!target_q) die("Memory error.");
    memcpy(target_q, base_addr, count * sizeof(int));

    for (size_t i = 0; i < count - 1; i++) {
        for (size_t j = 0; j < count - 1 - i; j++) {
            if (cmp(target_q[j], target_q[j + 1]) > 0) {
                swap(&target_q[j], &target_q[j + 1], sizeof(int));
            }
        }
    }
    return target_q;
}


int sorted_order(int a, int b)
{
    return a - b;
}

int reverse_order(int a, int b)
{
    return b - a;
}

int strange_order(int a, int b)
{
    if(a == 0 || b == 0) {
        return 0;
    } else {
        return a % b;
    }
}

/**
 * Used to test that we are sorting things correctly
 * by doing the sort and printing it out.
 */
void test_bsorting(int *numbers, int count, compare_cb cmp)
{
    int i = 0;
    int *sorted = bubble_sort(numbers, count, cmp);

    if(!sorted) die("Failed to sort as requested.");

    for(i = 0; i < count; i++) {
        printf("%d ", sorted[i]);
    }
    printf("\n");

    free(sorted);
}

void test_qsorting(int *numbers, int count, compare_cb cmp)
{
    int i = 0;
    int *sorted = qucik_sort(numbers, count, cmp);

    if(!sorted) die("Failed to sort as requested.");

    for(i = 0; i < count; i++) {
        printf("%d ", sorted[i]);
    }
    printf("\n");

    free(sorted);
}

int main(int argc, char *argv[])
{
    if(argc < 2) die("USAGE: ex18 4 3 1 5 6");

    int count = argc - 1;
    int i = 0;
    char **inputs = argv + 1;

    int *numbers = malloc(count * sizeof(int));
    if(!numbers) die("Memory error.");

    for(i = 0; i < count; i++) {
        numbers[i] = atoi(inputs[i]);
    }

    test_bsorting(numbers, count, sorted_order);
    test_bsorting(numbers, count, reverse_order);
    test_bsorting(numbers, count, strange_order);

    test_qsorting(numbers, count, sorted_order);
    test_qsorting(numbers, count, reverse_order);
    test_qsorting(numbers, count, strange_order);

    free(numbers);

    return 0;
}
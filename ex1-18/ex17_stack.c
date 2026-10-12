#include <stdio.h>

#define MAX_SIZE 100

struct Stack {
    int data[MAX_SIZE];
    int top;            // 栈顶下标，-1 表示空栈
};

void init(struct Stack *s) {
    s->top = -1;
}

int is_empty(struct Stack *s) {
    return s->top == -1;
}

int is_full(struct Stack *s) {
    return s->top == MAX_SIZE - 1;
}

void push(struct Stack *s, int value) {
    if (is_full(s)) {
        printf("Stack overflow\n");
        return;
    }
    s->data[++s->top] = value;
}

int pop(struct Stack *s) {
    if (is_empty(s)) {
        printf("Stack underflow\n");
        return -1;
    }
    return s->data[s->top--];
}

int peek(struct Stack *s) {
    if (is_empty(s)) {
        printf("Stack is empty\n");
        return -1;
    }
    return s->data[s->top];
}

int main() {
    struct Stack s;
    init(&s);

    push(&s, 10);
    push(&s, 20);
    push(&s, 30);

    printf("top: %d\n", peek(&s));    // 30
    printf("pop: %d\n", pop(&s));     // 30
    printf("pop: %d\n", pop(&s));     // 20
    printf("empty: %d\n", is_empty(&s)); // 0

    return 0;
}
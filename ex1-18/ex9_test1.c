#include <stdlib.h>
#include <stdio.h>

int main() {
    int *p = malloc(10 * sizeof(int));  // 分配 10 个 int
    if (p == NULL) {
        return 1;
    }

    // 越界写入
    p[10] = 100;

    // 越界读取
    printf("%d\n", p[10]);

    free(p);
    return 0;
}
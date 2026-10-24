#include <stdio.h>

void learn(int array[], int size)
{
    printf("Pointer size: %zu bytes\n", sizeof(array));
    printf("Element size: %zu bytes\n", sizeof(*array));
    printf("Array size: %d\n", size);
}

int main(void)
{
    int a[5] = {10, 20, 30, 40, 50};

    int sz = sizeof(a) / sizeof(a[0]);

    printf("Array size in main: %d\n", sz);

    learn(a, sz);

    return 0;
}

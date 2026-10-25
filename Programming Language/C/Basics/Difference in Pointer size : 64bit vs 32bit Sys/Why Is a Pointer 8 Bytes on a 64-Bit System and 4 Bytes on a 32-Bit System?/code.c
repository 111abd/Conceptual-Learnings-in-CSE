#include <stdio.h>

int main(void)
{
    int x = 10;
    int *ptr = &x;

    printf("Size of int: %zu bytes\n", sizeof(x));
    printf("Size of pointer: %zu bytes\n", sizeof(ptr));

    return 0;
}

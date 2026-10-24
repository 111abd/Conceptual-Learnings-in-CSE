# Understanding Arrays and Pointers in C

## Introduction

In C, arrays and pointers are closely related, but **they are not the same thing**.

One common point of confusion is why `sizeof(array)` returns the total size of an array in `main()`, but returns the size of a pointer when used inside a function.

Let's understand why this happens with examples.

## 1\. Calculating the Size of an Array

Consider the following code:

c

```
#include <stdio.h>

int main(void)
{
    int a[5] = {10, 20, 30, 40, 50};

    int sz = sizeof(a) / sizeof(a[0]);

    printf("Array size: %d\n", sz);

    return 0;
}
```

### Output

text

```
Array size: 5
```

### Explanation

Here, `a` is an actual array containing five integers.

Assuming `sizeof(int)` is 4 bytes:

- `sizeof(a)` = 5 × 4 = 20 bytes
- `sizeof(a[0])` = 4 bytes

Therefore:

c

```
sizeof(a) / sizeof(a[0])
```

Calculates the number of elements:

text

```
20 / 4 = 5
```

**Important:** This technique works when `a` is an actual array, not when it is a pointer parameter inside a function.

## 2\. What Happens When We Pass an Array to a Function?

Consider the following example:

c

```
#include <stdio.h>

void learn(int array[], int size)
{
    int sz = sizeof(array) / sizeof(int);

    printf("Calculated size: %d\n", sz);
}

int main(void)
{
    int a[5] = {10, 20, 30, 40, 50};

    int sz = sizeof(a) / sizeof(a[0]);

    printf("Array size in main: %d\n", sz);

    learn(a, sz);

    return 0;
}
```

### Output on a Typical 64-bit System

Assuming pointers occupy 8 bytes and integers occupy 4 bytes:

text

```
Array size in main: 5
Calculated size: 2
```

Why does this happen?

## 3\. Array Parameters Are Adjusted to Pointers

In a function parameter declaration, this:

c

```
void learn(int array[], int size)
```

is adjusted by the C language to the equivalent parameter type:

c

```
void learn(int *array, int size)
```

This means `array` is a pointer parameter inside the function, not an actual array object.

The pointer refers to the first element of the original array.

For example:

c

```
int a[5] = {10, 20, 30, 40, 50};

learn(a, 5);
```

The function receives a pointer to `a[0]` and the element count `5`.

**Passing an array to a function does not turn the original array into a pointer.** Instead, the function receives a pointer to its first element.

## 4\. Why Does `sizeof(array)` Return 8 Bytes?

Inside the function:

c

```
sizeof(array)
```

measures the size of the pointer parameter.

On a typical system where pointers occupy 8 bytes and integers occupy 4 bytes:

text

```
sizeof(array) = 8 bytes
sizeof(int)   = 4 bytes
```

Therefore:

c

```
sizeof(array) / sizeof(int)
```

becomes:

text

```
8 / 4 = 2
```

That's why the result is `2`, not `5`.

On a system where both pointers and integers occupy 4 bytes, the result would be `1`.

**Note:** Pointer size depends on the platform and implementation. A 64-bit system does not universally guarantee that every pointer occupies 8 bytes.

## 5\. Understanding `array`, `*array`, and `sizeof`

These expressions have different meanings:

| Expression | Meaning | Typical result |
| --- | --- | --- |
| `array` | The pointer value (address) | Address of the first element |
| `*array` | The value of the first element | `10` |
| `sizeof(array)` | Size of the pointer parameter | `8` bytes |
| `sizeof(*array)` | Size of one integer element | `4` bytes |
| `sizeof(int)` | Size of an integer | `4` bytes |

### Why Isn't `sizeof(array)` Equal to 4 Bytes?

The size of a pointer is different from the size of the object it points to.

A pointer stores an address. Dereferencing the pointer using `*array` accesses the object at that address.

For example:

c

```
printf("%zu\n", sizeof(array));   // Size of the pointer
printf("%zu\n", sizeof(*array));  // Size of one int
printf("%d\n", *array);           // First element's value
```

The first expression measures the pointer, the second measures one integer, and the third prints the integer's value.

## 6\. The Correct Way to Get the Array Length Inside a Function

The simplest solution is to pass the number of elements as an argument.

c

```
#include <stdio.h>

void learn(int array[], int size)
{
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
```

### Output

text

```
Array size in main: 5
Array size: 5
```

Here, `sz` is calculated while `a` is still an actual array. The result is then passed to `learn()`.

The function uses the `size` parameter instead of trying to calculate the array length from the pointer.

### Accessing Array Elements Inside the Function

The array parameter can still be used to access individual elements.

c

```
#include <stdio.h>

void learn(int array[], int size)
{
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }

    printf("\n");
}

int main(void)
{
    int a[5] = {10, 20, 30, 40, 50};

    int sz = sizeof(a) / sizeof(a[0]);

    learn(a, sz);

    return 0;
}
```

### Output

text

```
10 20 30 40 50
```

The pointer provides access to the elements, while the `size` parameter tells the function how many elements it can process.

## 7\. Key Takeaways

- An actual array and a pointer are different types of objects.
- `sizeof(array)` gives the total size in bytes when `array` is an actual array.
- In a function parameter, `int array[]` is adjusted to `int *array`.
- `sizeof(array)` inside that function measures the pointer, not the original array.
- `sizeof(*array)` measures the size of one element.
- To determine the number of elements inside a function, pass the count explicitly.
- The expression `sizeof(a) / sizeof(a[0])` is useful for calculating an array's element count in the scope where `a` is an actual array.

## Conclusion

The main idea is simple:

**A pointer tells you where an array begins, but it does not tell you how many elements the array contains.**

That is why C programs commonly pass both an array and its length to a function.

Understanding this distinction is an important step toward mastering arrays, pointers, and function parameters in C.

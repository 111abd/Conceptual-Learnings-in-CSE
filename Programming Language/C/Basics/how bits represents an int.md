# Understanding Integers and Bits in C

## 1\. Introduction

When we write a program in C, we often use variables to store numbers.

For example:

```
int a = 5;
```

Here, `int` is a data type, and `a` is a variable that stores an integer value.

But have you ever wondered how a computer actually stores the number `5`?

A computer represents data using **bits**, which can have only two values: `0` and `1`.

Understanding bits, bytes, binary numbers, and integer representation helps us understand how variables work at a lower level.

---

## 2\. What Is a Bit?

A **bit** (binary digit) is the smallest unit of digital information.

A bit can have one of two values:

- `0`
- `1`

Think of a bit like a switch that can be OFF (`0`) or ON (`1`).

Examples of bit values:

```
0
1
```

With one bit, we can represent two different states.

### How many combinations can bits represent?

Each additional bit doubles the number of possible combinations.

| Number of bits | Possible combinations |
| --- | --- |
| 1 | 2 |
| 2 | 4 |
| 3 | 8 |
| 4 | 16 |
| 8 | 256 |
| 16 | 65,536 |
| 32 | 4,294,967,296 |

The formula is:

**Number of combinations = 2ⁿ**

Here, `n` is the number of bits.

For example:

- 1 bit → 2¹ = 2 combinations
- 2 bits → 2² = 4 combinations
- 4 bits → 2⁴ = 16 combinations
- 8 bits → 2⁸ = 256 combinations

Each bit has two possible values, so `n` bits produce $2^n$ possible combinations.

---

## 3\. What Is a Byte?

A byte is a unit of digital information consisting of 8 bits in C's byte model.

For example:

```
1 byte = 8 bits

00000000
```

Each bit can be either `0` or `1`.

Therefore, one byte has:

$$
2^8 = 256
$$

possible bit combinations.

These combinations can represent unsigned values from `0` to `255`.

For example:

```
00000000 = 0
00000001 = 1
00000010 = 2
00000011 = 3
11111111 = 255
```

In C, `sizeof(char)` is always `1`, but a C byte is not necessarily 8 bits on every implementation. On modern mainstream computers, one byte is typically 8 bits.

---

## 4\. How Does Binary Represent Numbers?

Our everyday number system is decimal, which uses ten digits:

```
0 1 2 3 4 5 6 7 8 9
```

Computers commonly represent integers using binary, which uses only two digits:

```
0 1
```

In decimal, each position represents a power of 10.

For example:

$$
352 = 3 \times 100 + 5 \times 10 + 2
$$

In binary, each position represents a power of 2.

Consider the binary number:

```
00000101
```

Reading from right to left, the place values are:

| Bit position | Power of 2 | Bit value | Contribution |
| --- | --- | --- | --- |
| 7 | 128 | 0 | 0 |
| 6 | 64 | 0 | 0 |
| 5 | 32 | 0 | 0 |
| 4 | 16 | 0 | 0 |
| 3 | 8 | 0 | 0 |
| 2 | 4 | 1 | 4 |
| 1 | 2 | 0 | 0 |
| 0 | 1 | 1 | 1 |

Adding the contributions:

$$
4 + 1 = 5
$$

Therefore:

```
Binary:  00000101
Decimal: 5
```

Another example:

```
Binary:  00001010
Decimal: 10
```

Because:

$$
8 + 2 = 10
$$

**Important:** A bit pattern has a meaning determined by how we interpret it. The same bits can represent different things depending on the data type and representation.

---

## 5\. What Happens When We Declare an `int`?

Consider this C code:

```
int a = 5;
```

Let's break it down:

- `int` specifies the integer data type.
- `a` is the variable name.
- `5` is the initial value assigned to the variable.

On a system where `int` occupies 4 bytes and a byte contains 8 bits:

```
1 int = 4 bytes
      = 4 × 8 bits
      = 32 bits
```

The number `5` can be represented using 32 bits as:

```
00000000 00000000 00000000 00000101
```

The spaces are added only to make the bit pattern easier to read.

The computer uses the bits to represent the integer value stored in `a`.

### Does one `int` store many values at once?

No. A variable stores one value at a time.

For example:

```
int a = 5;
a = 10;
a = 20;
```

The value changes from `5` to `10`, and then to `20`.

The variable `a` does not store all three values simultaneously. Each assignment updates its value.

---

## 6\. Different Bit Combinations

Let's look at how the same 32-bit storage can represent different integer values.

The following examples assume a 32-bit signed `int` using two's-complement representation.

### Example 1: Storing the number 5

```
00000000 00000000 00000000 00000101
```

The last four bits are:

```
0101
```

Their place values are:

```
0 × 8 = 0
1 × 4 = 4
0 × 2 = 0
1 × 1 = 1
```

Total:

```
4 + 1 = 5
```

### Example 2: Storing the number 10

```
00000000 00000000 00000000 00001010
```

The last four bits are:

```
1010
```

Their place values are:

```
1 × 8 = 8
0 × 4 = 0
1 × 2 = 2
0 × 1 = 0
```

Total:

```
8 + 2 = 10
```

### Example 3: Storing the number 20

```
00000000 00000000 00000000 00010100
```

The last five bits are:

```
10100
```

Their place values are:

```
1 × 16 = 16
0 × 8  = 0
1 × 4  = 4
0 × 2  = 0
0 × 1  = 0
```

Total:

```
16 + 4 = 20
```

### Comparing the bit combinations

| Decimal value | 32-bit representation |
| --- | --- |
| 5 | `00000000 00000000 00000000 00000101` |
| 10 | `00000000 00000000 00000000 00001010` |
| 20 | `00000000 00000000 00000000 00010100` |

Notice that all three values use 32 bits, but the combinations of `0`s and `1`s differ.

This is the central idea:

**A fixed number of bits can represent many different values. The bit pattern determines the value according to the chosen representation.**

---

## 7\. What Is a Signed Integer?

A signed integer can represent both negative and positive values, including zero.

For a typical 32-bit signed integer using two's-complement representation, the range is:

```
-2,147,483,648 to 2,147,483,647
```

Mathematically:

$$
-2^{31} \text{ to } 2^{31}-1
$$

Why?

A 32-bit integer has:

$$
2^{32} = 4,294,967,296
$$

possible bit patterns.

In two's-complement representation, these patterns are divided between negative and nonnegative values.

The minimum is:

$$
-2^{31} = -2,147,483,648
$$

The maximum is:

$$
2^{31}-1 = 2,147,483,647
$$

Why subtract `1` from $2^{31}$?

Because the nonnegative range includes zero. It contains $2^{31}$ values:

```
0 through 2,147,483,647
```

That is why the maximum is one less than $2^{31}$.

### How is a negative number represented?

In two's-complement representation, a negative number is encoded using a particular pattern of bits.

For example, `-5` in 8-bit two's-complement representation is:

```
00000101  = 5
11111010  = invert the bits
11111011  = add 1
```

Therefore:

```
-5 = 11111011
```

The leading `1` indicates a negative value when this pattern is interpreted as an 8-bit signed two's-complement integer.

This is a simplified 8-bit example. The same principle applies to a 32-bit signed integer.

---

## 8\. What Is an Unsigned Integer?

An unsigned integer represents only nonnegative values.

For example:

```
unsigned int a = 5;
```

On a system with a 32-bit `unsigned int`, the range is:

```
0 to 4,294,967,295
```

The formula is:

$$
0 \text{ to } 2^{32}-1
$$

Unlike a signed integer, an unsigned integer uses all 32 bits to represent nonnegative values.

### Signed vs. unsigned

| Property | Signed 32-bit integer | Unsigned 32-bit integer |
| --- | --- | --- |
| Minimum | -2,147,483,648 | 0 |
| Maximum | 2,147,483,647 | 4,294,967,295 |
| Negative values | Yes | No |
| Number of possible values | 2³² | 2³² |

Both types have the same number of possible bit patterns, but they interpret those patterns differently.

---

## 9\. Is Every `int` Always 32 Bits?

No.

The C language does not require `int` to be exactly 32 bits on every implementation.

Its size depends on the implementation.

You can check its size using the `sizeof` operator:

```
#include <stdio.h>

int main(void)
{
    printf("Size of int: %zu bytes\n", sizeof(int));
    printf("Size of int in bits: %zu bits\n",
           sizeof(int) * 8);

    return 0;
}
```

Example output on a common system:

```
Size of int: 4 bytes
Size of int in bits: 32 bits
```

The multiplication by `8` assumes that a byte contains 8 bits, which is true on modern mainstream systems.

For a portable program, the number of bits in a byte can be obtained from `CHAR_BIT` in `<limits.h>`:

```
#include <stdio.h>
#include <limits.h>

int main(void)
{
    printf("Bits per byte: %d\n", CHAR_BIT);
    printf("Size of int: %zu bytes\n", sizeof(int));
    printf("Bits occupied by int: %zu\n",
           sizeof(int) * CHAR_BIT);

    return 0;
}
```

---

## 10\. What Happens If We Exceed the Integer Range?

Suppose a signed 32-bit `int` can store values only up to:

```
2,147,483,647
```

What happens if we try to add `1`?

```
int a = 2147483647;
a = a + 1;
```

In C, signed integer overflow causes undefined behavior. The language does not guarantee that the value will wrap around to a negative number.

For an unsigned 32-bit integer, arithmetic wraps modulo $2^{32}$:

```
unsigned int a = 4294967295U;
a = a + 1U;
```

On a system with a 32-bit `unsigned int`, `a` becomes `0`.

Always make sure that a variable's type can represent the values your program needs.

---

## 11\. A Complete C Example

The following program demonstrates integer assignment, changing values, and inspecting the size and range of `int`.

```
#include <stdio.h>
#include <limits.h>

int main(void)
{
    int a = 5;

    printf("Initial value: %d\n", a);

    a = 10;
    printf("Updated value: %d\n", a);

    a = -20;
    printf("Updated value: %d\n", a);

    printf("Size of int: %zu bytes\n", sizeof(int));
    printf("Minimum int value: %d\n", INT_MIN);
    printf("Maximum int value: %d\n", INT_MAX);

    return 0;
}
```

Example output on a common 32-bit-`int` system:

```
Initial value: 5
Updated value: 10
Updated value: -20
Size of int: 4 bytes
Minimum int value: -2147483648
Maximum int value: 2147483647
```

The program uses `INT_MIN` and `INT_MAX` from `<limits.h>` to display the implementation's actual `int` range.

---

## 12\. Key Takeaways

1. A bit is a binary digit: `0` or `1`.
2. A byte contains 8 bits on modern mainstream systems.
3. `n` bits can represent $2^n$ distinct bit patterns.
4. An `int` stores one integer value at a time.
5. A common `int` occupies 4 bytes, or 32 bits, but this is not guaranteed by C.
6. For a 32-bit signed two's-complement integer, the range is -2,147,483,648 to 2,147,483,647.
7. For a 32-bit unsigned integer, the range is 0 to 4,294,967,295.
8. Different bit patterns represent different values according to the data type and representation.
9. Use `sizeof`, `INT_MIN`, and `INT_MAX` to inspect your system's `int`.
10. Signed integer overflow is undefined behavior in C; unsigned arithmetic follows modular arithmetic rules.

## 13\. Practice Questions

Try answering these questions without looking at the explanations above.

1. How many combinations can 4 bits represent?
2. What decimal number does the binary pattern `00000111` represent?
3. What is the difference between a bit and a byte?
4. Why is the maximum value of a 32-bit signed integer 2,147,483,647 rather than 2,147,483,648?
5. Does `int a;` store multiple values simultaneously?
6. Is an `int` guaranteed to occupy exactly 4 bytes in C?
7. What is the difference between `int` and `unsigned int`?
8. What happens when a signed integer exceeds its representable range?

### Final Thought

Whenever you write:

```
int a = 5;
```

you are assigning an integer value to a variable. The implementation stores that value using a representation supported by its C implementation and hardware.

Understanding how bits combine to represent values is one of the foundations of understanding computer memory and programming in C.

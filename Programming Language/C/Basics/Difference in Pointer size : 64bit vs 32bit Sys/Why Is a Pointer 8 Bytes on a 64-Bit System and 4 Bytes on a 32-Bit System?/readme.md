# Why Is a Pointer 8 Bytes on a 64-Bit System and 4 Bytes on a 32-Bit System?

## 1. Introduction

In C, a pointer is a variable that stores the memory address of another object.

For example:

```c
int x = 10;
int *ptr = &x;
```

* `x` stores the integer value `10`.
* `&x` gives the memory address of `x`.
* `ptr` stores that memory address.

But why does a pointer typically occupy 4 bytes on a 32-bit system and 8 bytes on a 64-bit system?

The answer is related to how addresses are represented and how much memory a system can address.

## 2. What Is a Bit?

A bit is the smallest unit of digital information. It can represent either `0` or `1`.

* 1 byte = 8 bits
* 4 bytes = 32 bits
* 8 bytes = 64 bits

Each additional bit doubles the number of possible bit patterns.

For `n` bits, the number of possible patterns is:

$$
2^n
$$

For example:

* 8 bits can represent \(2^8 = 256\) patterns.
* 32 bits can represent \(2^{32}\) patterns.
* 64 bits can represent \(2^{64}\) patterns.

## 3. Why Is a Pointer Typically 4 Bytes on a 32-Bit System?

A typical 32-bit system uses pointers that occupy 32 bits, or 4 bytes.

With 32 bits, there are:

$$
2^{32}=4,294,967,296
$$

possible bit patterns.

If each address identifies one byte, this corresponds to a theoretical address space of 4 GiB (gibibytes).

This is why pointers on many 32-bit systems occupy 4 bytes.

## 4. Why Is a Pointer Typically 8 Bytes on a 64-Bit System?

A typical 64-bit system uses pointers that occupy 64 bits, or 8 bytes.

With 64 bits, there are:

$$
2^{64}=18,446,744,073,709,551,616
$$

possible bit patterns.

This allows a much larger theoretical address space than a 32-bit representation.

Therefore, pointers on many 64-bit systems occupy 8 bytes.

**Important:** A 64-bit system does not necessarily use all 64 bits for virtual memory addresses. The processor and operating system may support fewer address bits.

## 5. Visual Comparison

| Feature                            | Typical 32-bit system | Typical 64-bit system |
| ---------------------------------- | --------------------: | --------------------: |
| Pointer width                      |               32 bits |               64 bits |
| Pointer size                       |               4 bytes |               8 bytes |
| Possible bit patterns              |            \(2^{32}\) |            \(2^{64}\) |
| Theoretical byte-addressable space |                 4 GiB |                16 EiB |

Here, EiB means exbibytes. The address-space figures are theoretical and do not represent the amount of physical RAM a computer can necessarily use.

## 6. Why Isn't an `int` Also 8 Bytes on a 64-Bit System?

A pointer and an integer serve different purposes.

Consider this code:

```c
#include <stdio.h>

int main(void)
{
    int x = 10;
    int *ptr = &x;

    printf("Size of int: %zu bytes\n", sizeof(x));
    printf("Size of pointer: %zu bytes\n", sizeof(ptr));

    return 0;
}
```

Typical output on a system with 4-byte integers and 8-byte pointers:

```text
Size of int: 4 bytes
Size of pointer: 8 bytes
```

Why?

* `x` stores an integer value.
* `ptr` stores a memory address.

The size of an integer does not have to match the size of a pointer.

On many 64-bit systems, `int` remains 4 bytes, while ordinary data pointers occupy 8 bytes.

However, C does not universally require `int` to be 4 bytes or pointers to be 8 bytes. These sizes depend on the implementation.

## 7. What Does a Pointer Actually Store?

Consider:

```c
int x = 10;
int *ptr = &x;
```

Conceptually, memory might look like this:

```text
ptr
+------------------+
| Address of x     |
| e.g. 0x1000      |
+------------------+
         |
         | points to
         v
x
+------------------+
| Value: 10        |
+------------------+
```

The address `0x1000` is only an illustrative example.

The pointer stores the address, not the value `10` itself.

* `ptr` gives the stored pointer value.
* `*ptr` accesses the integer at that address.
* `sizeof(ptr)` measures the pointer's size.
* `sizeof(*ptr)` measures the size of the integer being pointed to.

For example:

```c
printf("%zu\n", sizeof(ptr));   // Typically 8 on a 64-bit system
printf("%zu\n", sizeof(*ptr));  // Typically 4 for int
printf("%d\n", *ptr);           // Prints 10
```

## 8. Does a 64-Bit System Use All 64 Bits for Addresses?

Not necessarily.

A pointer may occupy 64 bits even when the processor implements fewer than 64 bits of virtual addressing.

The processor architecture and operating system determine which virtual addresses are supported and how they are used.

Therefore, a 64-bit pointer does not mean that the computer has 16 EiB of physical RAM or that a program can necessarily access that much memory.

## 9. How Can You Check Pointer Size on Your Computer?

Compile and run this program:


*[Check code.c for the source code](./code.c)*

```c
#include <stdio.h>

int main(void)
{
    int x = 10;
    int *ptr = &x;

    printf("Size of int: %zu bytes\n", sizeof(x));
    printf("Size of pointer: %zu bytes\n", sizeof(ptr));

    return 0;
}
```

Compile with GCC:

```bash
gcc -Wall -Wextra -o pointer_size pointer_size.c
```

Run it on Linux or macOS:

```bash
./pointer_size
```

The output shows the sizes used by your compiler and target environment.

You can also check GCC's target architecture with:

```bash
gcc -dumpmachine
```

This identifies the compiler's target platform, although it does not directly print the size of a pointer.

## 10. Key Takeaways

* A pointer stores a memory address.
* A bit can represent two possible states: `0` or `1`.
* A typical 32-bit system uses 4-byte pointers.
* A typical 64-bit system uses 8-byte pointers.
* Wider pointers can represent a much larger range of addresses.
* The size of a pointer does not have to equal the size of the object it points to.
* `sizeof(ptr)` measures the pointer, while `sizeof(*ptr)` measures the pointed-to object.
* A 64-bit system does not necessarily use all 64 bits for virtual addresses.
* The C language does not mandate that all pointers be 4 bytes on 32-bit systems or 8 bytes on 64-bit systems.

## Conclusion

The key idea is that pointers store addresses, and the size of a pointer depends on how the target C implementation represents those addresses.


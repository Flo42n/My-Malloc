# Custom Malloc

This project is a custom implementation of the standard C memory allocation functions, developed as part of a systems programming project at EPITA.

The goal was to understand how dynamic memory allocation works by implementing a memory allocator using `mmap` and `munmap`, without relying on the standard allocation functions.

## Features

- Implementation of `malloc`, `free`, `calloc` and `realloc`
- Memory allocation using `mmap`
- Best-fit strategy to find suitable free memory blocks
- Memory management using doubly linked blocks
- Splitting and merging blocks to reuse available memory
- Memory alignment
- Releasing unused memory mappings with `munmap`
- Handling special cases such as NULL pointers, zero-size allocations and allocation overflow

## Compilation and Usage

The project is designed to run on Linux and requires GCC and Make.

From the repository root:

```bash
cd malloc
make
```

This generates the shared library `libmalloc.so`.

The allocator can be loaded using `LD_PRELOAD` to replace the standard memory allocation functions used by a program.

For example:

```bash
LD_PRELOAD=./libmalloc.so ls
```

## Tests

The project includes C tests covering memory allocation, reallocation, memory alignment, data preservation and block reuse.

A shell script also tests the allocator with several Linux commands using `LD_PRELOAD`.

Run the tests with:

```bash
make check
```

To remove compiled files:

```bash
make clean
```

## Notes

This project focuses on low-level memory management in C, particularly pointer manipulation, memory allocation strategies and interactions with the operating system.

It is an educational implementation rather than a production-ready replacement for the system allocator.

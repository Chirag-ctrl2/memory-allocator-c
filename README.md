# Simple Memory Allocator in C

A minimal first-fit memory allocator implemented from scratch in C using `sbrk()`.

This project was built to understand how dynamic memory allocation works internally by recreating some of the core ideas behind `malloc()` and `free()`.

## Features

- Custom memory allocation (`my_alloc`)
- Custom memory deallocation (`my_free`)
- First-fit allocation strategy
- Linked-list based heap management
- Free block reuse
- Block metadata stored before user memory
- Heap expansion using `sbrk()`

## Memory Layout

Each allocated block contains a metadata header followed by user-accessible memory.

```text
+-------------------------+------------------+
| Block Metadata          | User Memory      |
+-------------------------+------------------+
^                         ^
block                     pointer returned
```

### Metadata Structure

```c
typedef struct block {
    size_t size;
    bool free;
    struct block *next;
} block_t;
```

The allocator stores:

- Block size
- Allocation status
- Pointer to the next block

## Allocation Process

1. Search the linked list for a free block large enough to satisfy the request.
2. If found, reuse that block.
3. Otherwise, request additional heap memory using `sbrk()`.
4. Return a pointer to the memory immediately after the metadata header.

## Free Process

1. Recover the block header from the user pointer.
2. Mark the block as free.
3. Future allocations may reuse the block.

## Example

```c
char *a = my_alloc(100);
char *b = my_alloc(50);

my_free(a);

char *c = my_alloc(70);
```

Since the freed block is large enough:

```text
c == a
```

The allocator reuses the previously freed memory block.

## Build

```bash
gcc -Wall -Wextra -Wpedantic -g my_malloc.c -o my_malloc.o
```

## Run

```bash
./allocator
```

## Current Limitations

This is a learning project and does not yet implement:

- Block splitting
- Block coalescing
- Memory alignment
- `calloc()`
- `realloc()`
- Thread safety
- Detection of invalid frees
- Detection of double frees

## Concepts Explored

- Heap memory management
- Pointer arithmetic
- Linked lists
- Metadata headers
- Process memory layout
- Dynamic allocation internals
- Low-level systems programming in C

## Future Improvements

- Implement block splitting
- Implement block coalescing
- Add alignment support
- Implement `calloc`
- Implement `realloc`
- Add heap statistics and debugging tools

## Author

Chirag

## License

MIT License

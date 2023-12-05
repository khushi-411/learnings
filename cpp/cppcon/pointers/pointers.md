# Back to Basics: Pointers

> **Mike Shah Talk**: [https://www.youtube.com/watch?v=0zd8eznWv4k](https://www.youtube.com/watch?v=0zd8eznWv4k)

- **Raw pointer**: A variable that stores memory address of a specific object types.
- Things we'll learn-- creating data structures, passing data into functions, dynamically allocated arrays, and functions pointers.
- Next-- nullpts, double frees, memory leaks.

#### A basic example
- `px` is a pointer of type `int*`.
- `&` to retrieve the address of the variable.
- `px` stores the address of x.
- `*px` means retrive the value of the varibale (called **dereferencing**).
- `int*` (pointer to int), is also a variable and has a address like other variables.
```cpp
// basic.cpp
int* px = &x;
```

#### Let's visualize memory
- Different types of memory: Regiters, Cache, DRAM, Hard Drive(s), Non-local memorys, etc.
- Memory is our machine is represented as a linear array of addresses.
    - At each address we can store a value (i.e., same amount of bytes).
![visualize_memory_pointer]("images/visualize_memory_pointer.png")

#### Dereferencing a pointer


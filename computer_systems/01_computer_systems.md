# A Tour of Computer System

- Computer system = Software + Hardware
- Learn how to avoid strange numerical errors caused by the way computer represent numbers.
- Learn how to optimize our C code vy exploiting designs of modern processors and memory systems.
- Learn how compiler implements procedure calls and how to use this calls to avoid buffer overflow.
- Learn how to recognize and avoid nasty errors.
- Learn how to write your own Unix shell, dynamic storage allocation package, and own web server.
- Learn the promses and pitfalls of concurrency.

In this chapter, we'll learn what happens when we run hello on our system.

### Information Is Bits + Context
- Source program is a sequence of bits, each of value $0$ or $1$, organized in $8$-bit chucks called *bytes*.
- Most computer represent text charcters using ASCII standard.
- Files that consists of ASCII characters are called text files. All other files are known as *binary files*.
- All information in a system is represented as a bunch of bits.
    - Eg, disk files, programs stored in memory, user data stored in memory, data transferred accross the network.
- Difference is in which context we view them; like integer, floating-point number, character string, or machine instruction.

### Programs are translated by other Programs into Different Forms
- To run C program, in the system they should be translated to low-level machine language instructions.
- These instructions are packed into executable object files.
- And stored as a binary disk file.
- In Unix system, this translation from source file to object file is preformed by compiler driver.

<div align="center">
![Compilation system](images/compilation_system.png)
</div>

Here's how GCC compiler driver reads the source file hello.c.
1. **Preprocessing phase (cpp)**
    - It modifies the C program according to the directives that begin with the `#` character.
    - i.e., creates another program with the $.i$ suffix, where all the contents are inserted in the file.
2. **Compilation phase (cc1)**
    - Translate the text file ($.i$) into another text file with $.s$ extention.
    - It contains an assembly-language program.
    - Assembly language provides a common output language for different compilers for different high-level language.
3. **Assembly phase**
    - Assemble (as) translates $.s$ files into machine language instructions, package them in the form known as a relocatable object program.
    - And stores in the object file with extention $.o$.
    - It is a binary file containing $17$ bytes to encode the instructions for function main.
4. **Linking phase**
    - Our program calls printf function, since it's a part of standard C library, *printf* function resides in a separate precompiled object file called $print.o$.
    - This should be merged with $hello.o$ file. The linker **ld** handles ths merging.
    - The result is an executable object file that is ready to be loaded into memory and executed by the system.

> **GNU Project**: Gcc is one of the many tools developed by it. It's goal is to build UNIX systems. This project has developed major components of UNIX operating system, expect kernel (developed by Linux). Other projects by GNU are: EMACS editor, GCC compiler, GDB debugger, assembler, linker, utilities for manipulating binaries etc. Supports many programming language. Linux owes its popularity to GNU tools.

### It Pays to Understand How Compilation Systems Work
Other improtant reasons about how compilation system work:
1. **Optimizing program performance**
    - Is switch statement always more efficient than a sequence of if-else?
    - How much overhead is incurred by a function call?
    - Is while loop more efficient than a for loop?
    - Are pointer references more efficient than array indexes?
    - Why loop runs faster if we sum into a local variable instead of an argument passed by reference?
    - How can a function run faster when we rearrange the parentheses in an arithmetic expression?
2. **Understanding link-time errors**
    - What does it mean when linker reports it cannot resolve a reference?
    - What is the difference between static variable and global variable?
    - What happens if we define two global variables in different C files with the same name?
    - What is the difference between static library and a dynamic library?
    - Why does it matter what order we list libraries on the command line?
    - Why do some linker-related errors not appear until run time?
3. **Avoiding security holes**
    - Cover the stack discipline and buffer overflow vulnerabilities.

### Processors Read and Interpret Instructions Stored in Memory
- At this point the object file is generated and stored in the disk.
- **Shell**
    - A command line interpreter that prints a prompt.
    - Waits to write a command by the user, then performs the command.
    - If it's not a built-in shell command, it loads the executable file and run.

#### Hardware Organization of a System

<div align="center">
![Hardware organization](images/hardware_organization.png)
</div>

1. **Buses**
    - Carry information back and forth between the components.
    - Designed to transfer fixed-size chunks of bytes known as *words*.
    - Most machines have a word size of either $4$ bytes or $8$ bytes.
2. **I/O Devices**
    - It is the system's connection to the external world.
    - Initially, the executable program resides on the disk.
    - I/O device is connected to the I/O bus by controller or an adapter.
    - Controller: chip sets in the device or system's main printed circuit board (motherboard).
    - Adapter: card that plug into a slot on the motherboard.
3. **Main Memory**
    - Temporary storage device that holds both a program and the data while the processor is executing the program.
    - Consists of DRAM chips.
    - Logically, memory is organized as a linear array of bytes.
    - Each machine may have variable number of bytes stored.
    - Eg, `x86-64` running on Linux, data type short require 2 bytes, type int and float 4 bytes, and types long and double 8 bytes.
4. **Processor**
    - Engine that executes the instructions stored in main memory as pointed by PC and update it to point the next instruction.
    - It is strict we cannot change the sequence.
    - At its core is a word-size storage device (or register) called program counter (PC).
    - It points to machine level instructions in main memory.
    - **Instruction set architecture**: a processor appears to operate according to it.
    - How CPU carray out the request of an instruction?
        - ***Load***: Copy a byte or a word from main memory into a register, overwriting the previous contents of the register,
        - ***Store***: Copy a byte or a word from a register to a location in main memory, overwriting the previous contents of that location.
        - ***Operate***: Copy the contents of two registers to the ALU, perform an arithmetic operation on the two words, and store the result in a register, overwriting the previous contents of that register.
        - ***Jump***: Extract a word from the instruction itself and copy that word into the program counter (PC), overwriting the previous value of the PC.

#### Running the `hello` program
- As we execute the object files, the shell program reads/loads each one into a register and then stores the data in the main memory.
- The data includes the string of characters.
- This technique is known as *direct memory access*. Does not pass through the processor.
- Once its loaded it begins to execute the machine language instructions.
- These instructions copy the bytes in the string from memory to the register file, and from there to the display device, where it is displayed on the screen.

### Caches Matter


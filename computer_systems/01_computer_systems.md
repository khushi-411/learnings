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

![Compilation system]("images/compilation_system.png")

Here's how GCC compiler driver reads the source file hello.c.
1. **Preprocessing phase (cpp)**
    - It modifies the C program according to the directives that begin with the $#$ character.
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

> **GNU Project**:
1. Gcc is one of the many tools developed by it. It's goal is to build UNIX systems.
2. This project has developed major components of UNIX operating system, expect kernel (developed by Linux).
3. Other projects by GNU are: EMACS editor, GCC compiler, GDB debugger, assembler, linker, utilities for manipulating binaries etc.
4. Supports many programming language.
5. Linux owes its popularity to GNU tools.

### It Pays to Understand How Compilation Systems Work
Other improtant reasons about how compilation system work:
1. **Optimizing program performance**

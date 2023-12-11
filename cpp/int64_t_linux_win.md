### int64_t - Linux vs Windows
1. **What is the difference between `int64_t` and `long` (`long int`)?**
    - int64_t is a signed integer type with exactly 64 bits. The latter is a signed integer type with at least 32 bits
    - It is declared in `<cstdint>` / `<cinttypes>` or in `<stdint.h>` / `<inttypes.h>
2. **How `long long` and `long int` similar or different?**
The sizes are the same, but their data types are different. Consider the following code:
    ```cpp
    #include <iostream>
    #include <typeinfo>
    int main() {
        auto k = sizeof(long long);
        auto s = sizeof(long int);
        std::cout << k << " " << s << std::endl;
        std::cout << typeid(long long).name() << " " << typeid(long int).name();
        return 0;
    }
    ```
    - **For Linux**
Output on `x86-64 gcc` and `x86-64 clang 16.0.0`:
        ```
        8 8
        x l
        ```
    - **For Microsoft Visual C++**
Output on `x86 msvc`: (this is weird because output values are not printing in Godbolt; I only got this. :)
        ```
        example.cpp
        Compiler returned: 0
        ```
        But the expected values are:
        ```
        8 4
        __int64 int
       ```
        Notice that `long int` has different values in `Linux` and `Windows`. Now, the question is how big libraries support cross-platform. Well, there are 2-3 ways we could deal with it.

3. **Enabling cross-platform support**
    - **Case I**: scan values using `SCN` (character string literals for the fscanf() and fwscanf() family of functions).
        Let's take an example, in `gcc` and `clang`, to print `int64_t`, data type `%ld` is used while in `msvc`, `%lld` is used to denote `int64_t` value. Consider the following code:
        ```cpp
        #include <iostream>
        #include <inttypes.h>  // to use SCNd64
        int main() {
            [[maybe_unused]] int64_t *p;
            scanf("%ld", p);
            // scanf("%" SCNd64, p);  // to remove warnings use SCNd64
            return 0;
        }
        ```
        *Note:*
        1. we can also use `__attribute__((unused))` for gcc and clang compilers instead of `[[maybe_unused]]`.
        2. `[[maybe_unused]]` was introduced in C++17. It indicates the function/variable/struct etc might not be used by the program. GCC and Clang compilers don't throw any warning, but MSVC does in Godbolt.
        
       *Output on GCC and clang:*
        ```
        ASM generation compiler returned: 0
        Execution build compiler returned: 0
        Program returned: 0
        ```
        *Output on MSVC:*
        ```
        example.cpp
        <source>(5): warning C5051: attribute 'maybe_unused' requires at least 
        '/std:c++17'; ignored
        <source>(6): warning C4477: 'scanf' : format string '%ld' requires an 
        argument of type 'long *', but variadic argument 1 has type 'int64_t *'
        <source>(6): note: consider using '%lld' in the format string
        <source>(6): note: consider using '%I64d' in the format string
        <source>(6) : warning C4700: uninitialized local variable 'p' used
        cl : Command line warning D9002 : ignoring unknown option '- 
        march=skylake'
        Compiler returned: 0
        ```
        To resolve the conflict between different platforms, we can use `SCNd64` as shown above in the commented part of the code.
    - **Case II**: Don't rely on any precise type.
        Let's take an example; in the example below, it first checks if `int64_t` and `long` are the same or not; if not, it substitutes its value; if it is equal, it returns a given value.
        ```cpp
        long foo(long x);  // declaration of func
        std::enable_if<!std::is_same<int64_t, long>::value, int64_t>::type foo(int64_t);
        ````

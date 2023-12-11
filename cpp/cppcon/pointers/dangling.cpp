#include <iostream>


// dangling pointer: points to memory that does not exists
// use address sanitizers to help us catch this
char* dangerousReturnLocalValue() {
    char c = 'c';
    return &c;
}

int main() {
    char *danglingPointer1 = dangerousReturnLocalValue();
    std::cout << "danglingPointer1 = " << *danglingPointer1 << std::endl;
    return 0;
}

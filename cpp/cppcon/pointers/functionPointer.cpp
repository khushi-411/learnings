#include <iostream>

int add(int x,int y){
    return x + y;
}

int multiply(int x, int y){
    return x * y;
}

int main(){

    int (*pfn_arithmetic)(int, int);
    pfn_arithmetic = add;
    std::cout << "pfn_arithmetic(2, 7) = " << pfn_arithmetic(2, 7) << std::endl;

    pfn_arithmetic = multiply;
    std::cout << "pfn_arithmetic(2, 7) = " << pfn_arithmetic(2, 7) << std::endl;

    return 0;
}

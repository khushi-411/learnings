#include <iostream>
#include <functional>

int add(int x,int y){
    return x + y;
}

int multiply(int x, int y){
    return x * y;
}

int main(){
    std::function<int(int, int)> f_arithmetic = add;
    f_arithmetic = add;
    std::cout << "f_arithmetic(2, 7) = " << f_arithmetic(2, 7) << std::endl;

    f_arithmetic = multiply;
    std::cout << "f_arithmetic(2, 7) = " << f_arithmetic(2, 7) << std::endl;

    return 0;
}

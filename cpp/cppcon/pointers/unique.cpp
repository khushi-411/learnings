#include <iostream>
#include <memory>

class Object {
public:
    Object() { std::cout << "Constructor\n"; }
    ~Object() { std::cout << "Destructor\n"; }
};

int main() {

    { std::unique_ptr<Object> p_uniquePtr(new Object); }

    { std::unique_ptr<Object> p_uniquePtr = std::make_unique<Object>(); }

    return 0;
}

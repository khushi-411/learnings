#include <iostream>

class Entity
{
public:
    float x, y;

    // Don't have to use Init() method everytime, if we use this.
    // Entity() {
    //     x = 0.0f;
    //     y = 0.0f;
    // }

    // Method - II
    // Entity (float X, float Y) {
    //     x = X;
    //     y = Y;
    // }

    // we have to manually initialize variable in cpp unlike python or java
    void Init() {
        x = 0.0f;
        y = 0.0f;
    }

    void Print() {
        std::cout << x << ", " << y << std::endl;
    }
};

int main() {
    Entity e;
    // Method - II
    // Enitity e (10.0f, 5.0f);
    e.Init();
    // std::cout << e.x << std::endl;
    e.Print();
    std::cin.get();
}

#include <iostream>
#include <string>


enum struct Values {
    value1 = 1,
    value2 = 2,
};


std::string to_string(const Values v) {
    using enum Values;  // with C++20

    switch (v) {
	    case value1:  // with C++11: Values::value1
            return "value1";
        case value2:
            return "value2";
    }
    return "unknown value";
}


// with C++20
// Note can also use with Namespace
namespace NS {
    using enum Values;
}


// with C++20
// Using with struct
struct S {
    using enum Values;
    Values curr_val = value1;
};


int main() {
    auto val = NS::value1;
    return 0;
}

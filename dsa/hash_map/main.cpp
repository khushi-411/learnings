#include <iostream>
#include <string>

#include "HashMap.h"


struct keyHash {
    unsigned long operator()(const int& k) const
    {
        return k % 10;
    }
};


int main() {
    HashMap<int, std::string, 10, keyHash> hash_map;
    hash_map.put(1, "1");
    hash_map.put(2, "2");
    hash_map.put(3, "3");

    std::string value;
    std::string result = hash_map.get(2, value);
    std::cout << result << "\n";

    result = hash_map.get(3, value);
    std::cout << result << "\n";

    hash_map.remove(3);
    return 0;
}

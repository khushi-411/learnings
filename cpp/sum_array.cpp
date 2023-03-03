// https://stackoverflow.com/questions/20163469

#include <iostream>

/*template <class T>
T sum_array(T (&a)[10], int size) {
    T result = 0;
    for (int i = 0; i < size; i++) {
        result = a[i] + result;
    }
    return result;
}

int main() {
    int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::cout << sum_array(a, 10) <<std::endl;
    return 0;
}*/
 
template <class T>
T sum_array(T a[], int size) {
    T result = 0;
    for (int i = 0; i < size; i++) {
        result = a[i] + result;
    }
    return result;
}

int main() {
    int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::cout << sum_array(a, 10) <<std::endl;
    return 0;
}

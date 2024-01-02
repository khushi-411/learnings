// https://stackoverflow.com/questions/1143262

#include <iostream>

template <typename T>
struct MaybeOwnedTraitsGenericImpl {
    using owned_type = T;
    using borrow_type = const T*;
 
    static borrow_type createBorrow(const owned_type& from) {
        return &from;
    }

    static void assignBorrow(borrow_type& lhs, borrow_type rhs) {
        lhs = rhs;
    }

    static const owned_type& referenceFromBorrow(const borrow_type& borrow) {
        return *borrow;
    }

    static const owned_type* pointerFromBorrow(const borrow_type& borrow) {
        return borrow;
    }
};

int main() {
    MaybeOwnedTraitsGenericImpl<float> obj;
    float val = 411.0;

    const float* borrowPtr = obj.createBorrow(val);
    std::cout << "borrowPtr: " << *borrowPtr << std::endl;

    const float new_val = 405.0;
    obj.assignBorrow(borrowPtr, &new_val);
    std::cout << "new_val: " << new_val << std::endl;

    const float& ref = obj.referenceFromBorrow(borrowPtr);
    std::cout << "ref: " << ref << std::endl;

    const float* ptr = obj.pointerFromBorrow(borrowPtr);
    std::cout << "ptr: " << *ptr << std::endl;
    
    return 0;
}

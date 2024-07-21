// https://github.com/aozturk/HashMap/blob/master/hashmap/KeyHash.h


#pragma once


template <typename K, size_t tableSize>
struct KeyHash {
    unsigned long operator()(const K& key) const {
        return reinterpret_cast<unsigned long>(key) % tableSize;
    }
};

// https://github.com/aozturk/HashMap/blob/master/hashmap/HashNode.h


#pragma once

#include <iostream>


template <typename K, typename V>
class HashNode {
private:
    K key;
    V value;
    HashNode* next;
    HashNode(const HashNode&);
public:
    HashNode(const K& key, const V& value) : key(key), value(value), next(NULL) {}

    K getKey() const {
        return key;
    }

    V getValue() const {
        return value;
    }

    void setValue(V value) {
        value = value;
    }

    HashNode *getNext() const {
        return next;
    }

    HashNode *setNext(HashNode* next) {
        next = next;
    }
};

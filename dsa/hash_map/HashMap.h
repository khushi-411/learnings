// https://github.com/aozturk/HashMap/blob/master/hashmap/HashMap.h


#pragma once

#include <iostream>
#include <cstddef>

#include "HashNode.h"
#include "KeyHash.h"


template <typename K, typename V, size_t tableSize, typename F = KeyHash<K, tableSize>>
class HashMap {
private:
    HashMap(const HashMap& other);
    const HashMap& operator=(const HashMap& other);
    HashNode<K, V> *table[tableSize];
    F hashFunc;

public:
    HashMap() : table(), hashFunc() {}

    ~HashMap() {
        for (size_t i = 0; i < tableSize; i++) {
            HashNode<K, V> *entry = table[i];

            while (entry != NULL) {
                HashNode<K, V> *prev = entry;
                entry = entry->getNext();
                delete prev;
            }
            table[i] == NULL;
        }
    }

    std::string get(const K& key, V& value) {
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *entry = table[hashValue];

        while (entry != NULL) {
            if (entry->getKey() == key) {
                value = entry->getValue();
                return value;
            }
            entry = entry->getNext();
        }
        return "False";
    }

    void put(const K& key, const V& value) {
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *prev = NULL;
        HashNode<K, V> * entry = table[hashValue];

        while (entry != NULL && entry->getKey() != key) {
            prev = entry;
            entry = entry->getNext();
        }

        if (entry == NULL) {
            entry = new HashNode<K, V>(key, value);

            if (prev == NULL) {
                table[hashValue] = entry;
            } else {
                prev->setNext(entry);
            }
        } else {
            entry->setValue(value);
        }
    }

    void remove(const K& key) {
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *prev = NULL;
        HashNode<K, V> * entry = table[hashValue];

        while (entry != NULL && entry->getKey() != key) {
            prev = entry;
            entry = entry->getNext();
        }

        if (entry == NULL) {
            return;
        } else {
            if (prev == NULL) {
                table[hashValue] = entry->getNext();
            } else {
                prev->setNext(entry->getNext());
            }

            delete entry;
        }
    }

};

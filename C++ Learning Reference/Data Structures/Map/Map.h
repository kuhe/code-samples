#ifndef CPPREF_MAP_H
#define CPPREF_MAP_H

#include <c++/sstream>
#include "_map_common.h"

namespace Lehr {
    template <typename K, typename V>
    class KeyValuePair {
    public:
        KeyValuePair() {}
        KeyValuePair(const K& key, const V& value) : key(key), value(value) {}
        K key;
        V value;
        operator KeyValuePair() {
            return value;
        }
        void operator =(V& value) {
            this->value = value;
        }
        void operator =(V* value) {
            this->value = *value;
        }
        void operator =(V value) {
            this->value = value;
        }
        KeyValuePair* next = nullptr;
    };

    template <typename K>
    class Hash {
    public:
        int size;
        Hash(int size = 128) : size(size) {}
        int operator()(const K* key) {
            string name;
            if (std::is_same<K, string>::value) {
                name = *key;
            } else {
                const void *address = static_cast<const void *>(key);
                std::stringstream ss;
                ss << address;
                name = ss.str();
            }
            return hashString(name);
        }
        int hashString(string key) {
            int h = 0;
            for (char &c : key) {
                h = h << 1 ^ c;
            }
            return h % size;
        }
    };

    template <typename K, typename V>
    class Map {
    public:
        Map() {
            table = new KeyValuePair<K,V>[tableSize];
        }

        ~Map() {
            delete[] table;
        }

        V& operator [](const K& key) {
            int hash_index = hash(&key);
            KeyValuePair<K,V>& bucket = table[hash_index];
            KeyValuePair<K,V>* candidate = &bucket;
            do {
                if (candidate->key == key) {
                    return candidate->value;
                }
                if (nullptr != candidate->next) {
                    candidate = candidate->next;
                }
            } while(candidate->next != nullptr);
            if (candidate->key != key) {
                candidate->key = key;
            }
            return candidate->value;
        }
    private:
        int tableSize = 128;
        KeyValuePair<K,V>* table;
        int hash(const K* key) const {
            Hash<K> h(128);
            return h(key);
        }
    };
}

#endif //CPPREF_MAP_H

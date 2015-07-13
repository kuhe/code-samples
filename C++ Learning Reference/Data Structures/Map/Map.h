#ifndef CPPREF_MAP_H
#define CPPREF_MAP_H

#include "_map_common.h"

namespace Lehr {
    template <typename K, typename V>
    struct KeyValuePair {
        KeyValuePair(const K& key, const V& value) : key(key), value(value) {}
        K key;
        V value;
    };

    template <typename K, typename V>
    class Map {
    public:
        Map();

        ~Map();

        V& operator [](const K& key);
    private:
        ArrayList<ArrayList<KeyValuePair<K,V>>> list;
        int tableSize = 128;
        unsigned int hash(const K& key) {
            return reinterpret_cast<unsigned int>(key) % tableSize;
        }
    };
}

#endif //CPPREF_MAP_H

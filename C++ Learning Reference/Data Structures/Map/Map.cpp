#include "Map.h"

namespace Lehr {
    template <typename K, typename V>
    Map<K,V>::Map() {}

    template <typename K, typename V>
    Map<K,V>::~Map() {}

    template <typename K, typename V>
    V& Map<K,V>::operator [](const K& key) {
        ArrayList<V>& bucket = list[hash(key)];
        unsigned int n = 0;
        do {
            KeyValuePair<K,V>& candidate = bucket[n];
            if (candidate.key == key) {
                return candidate.value;
            }
            n++;
        } while(n < bucket.count());
        V& error;
        return error;
    }

}
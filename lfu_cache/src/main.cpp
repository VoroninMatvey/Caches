#include <iostream>
#include "lfu_cache.hpp"

template<typename T, typename KeyT = int>
int check_hits(int capacity, int amount, Cache::lfu_cache<T, KeyT>& lfu_final) {

        int hits = 0;
        int key = 0;
        if(capacity == 0) {
                return 0;
        }

        for(int i = 0; i < amount; ++i) {
                std::cin >> key;
                hits += lfu_final.lookup_update(key, slow_get_page(key));
        }
        return hits;
}

int main() {

        int capacity = 0;
        std::cin >> capacity;

        int amount = 0;
        std::cin >> amount;

        Cache::lfu_cache lfu_final(capacity);
        std::cout << check_hits(capacity, amount, lfu_final) << '\n';

        return 0;
}

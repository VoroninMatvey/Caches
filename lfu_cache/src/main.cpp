#include <iostream>
#include "lfu_cache.hpp"

int check_hits(int capacity, int amount, const Cache::lfu_cache& lfu_final) {

        int hits = 0;
        int page = 0;
        if(capacity == 0) {
                return 0;
        }

        for(int i = 0; i < amount; ++i) {
                std::cin >> page;
                hits += lfu_final.lookup_update(page);
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

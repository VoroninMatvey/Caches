#include <iostream>
#include "perfect_cache.hpp"

template<typename T, typename KeyT>
int check_hits(int capacity, int numb_of_page, Cache::perfect_cache<T, KeyT>& perfect_final) {

    int hits = 0;
    int key = 0;
    if(capacity == 0) return 0;

    perfect_final.initial_assembly();
    for(int i = 0; i < numb_of_page; ++i) {

        key = perfect_final.get_incoming_page(i);
        hits += perfect_final.lookup_update(key, slow_get_page);
    }
    return hits;
}

int main() {

    int capacity = 0;
    std::cin >> capacity;

    int numb_of_page = 0;
    std::cin >> numb_of_page;

    Cache::perfect_cache<int, int> perfect_final(capacity, numb_of_page);
    std::cout << check_hits(capacity, numb_of_page, perfect_final) << '\n';

    return 0;
}

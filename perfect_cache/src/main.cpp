#include <iostream>
#include "perfect_cache.hpp"

int check_hits(int capacity, int numb_of_page, Cache::perfect_cache& perfect_final) {

    int hits = 0;
    int page = 0;
    if(capacity == 0) return 0;

    perfect_final.initial_assembly();
    for(int i = 0; i < numb_of_page; ++i) {

        page = perfect_final.get_incoming_page(i);
        hits += perfect_final.lookup_update(page, i);
    }
    return hits;
}

int main() {

    int capacity = 0;
    std::cin >> capacity;

    int numb_of_page = 0;
    std::cin >> numb_of_page;

    Cache::perfect_cache perfect_final(capacity, numb_of_page);
    std::cout << check_hits(capacity, numb_of_page, perfect_final) << '\n';

    return 0;
}

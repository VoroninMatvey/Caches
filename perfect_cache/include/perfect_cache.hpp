#include <list>
#include <unordered_map>
#include <vector>
#include <iterator>
#include <utility>
#include <cstdlib>

typedef int(*func_pointer)(int);
int slow_get_page(int key) {

    return key;
}

namespace Cache {

template<typename T, typename KeyT>
class perfect_cache {

        using page_t = std::pair<KeyT, T>;

        struct cache_item {
            page_t page_;
            int numbefnext_;

            cache_item(page_t page, int numbefnext) : page_{page}, numbefnext_{numbefnext}  {}
        };

        struct un_buf_item {
            int amount_ = 0;
            std::vector<int> history_;

        };

        using cache_item_iter = typename std::list<cache_item>::iterator;
        using un_buf_iter = typename std::unordered_map<KeyT, un_buf_item>::iterator;
        using find_iter = typename std::unordered_map<KeyT, cache_item_iter>::iterator;

public:
         perfect_cache(int capacity, int number) : capacity_{capacity}, numb_of_page_{number} {}
         void initial_assembly();
         int lookup_update(KeyT key, int counter, func_pointer slow_get_page);
         KeyT get_incoming_page(int counter);

private:

        const int capacity_;
        const int numb_of_page_;
        std::unordered_map<KeyT, un_buf_item> unordered_buffer_; // saves the page arrival history
        std::list<cache_item> cache_;
        std::vector<KeyT> ordered_buffer_; // saves the data received from input
        std::unordered_map<KeyT, cache_item_iter> elem_finder_; // finds element with corresponding value in cache_

        int calculation_length(KeyT key, int counter);
        void insert_elem(KeyT key, int counter, func_pointer slow_get_page);
        void decrease_of_numb();
        void it_is_hit(KeyT key, int counter);
        void remove_elem(KeyT key);
        KeyT victim_finder(KeyT key, int length);//looking for a victim from the elements of cache and incoming page, also decrease of numbefnext_ all list's elements
        bool cache_is_full();
}; // <-- Class perfect_cache

template<typename T, typename KeyT>
bool perfect_cache<T, KeyT>::cache_is_full() {

    return elem_finder_.size() == capacity_;
}

template<typename T, typename KeyT>
KeyT perfect_cache<T, KeyT>::get_incoming_page(int counter) {

    return ordered_buffer_[counter];
}

template<typename T, typename KeyT>
void perfect_cache<T, KeyT>::initial_assembly() {

    KeyT key = 0;
    un_buf_iter it;

    for(int i = 0; i < numb_of_page_; ++i) {

        std::cin >> key;
        ordered_buffer_.push_back(key);
        it = unordered_buffer_.find(key);

        if(it != unordered_buffer_.end()) {

            (it -> second).history_.push_back(i);
        } else {

            un_buf_item c;
            unordered_buffer_[key] = c;
            (unordered_buffer_.find(key) -> second).history_.push_back(i);
        }
    }
}

template<typename T, typename KeyT>
int perfect_cache<T, KeyT>::calculation_length(KeyT key, int counter) {

    un_buf_iter it = unordered_buffer_.find(key);
    if(((it -> second).history_.begin() + (it -> second).amount_) != (it -> second).history_.end()) {

        int length = (it -> second).history_[(it -> second).amount_] - counter;
        return length;
    } else {
        return -1;
    }
}

template<typename T, typename KeyT>
void perfect_cache<T, KeyT>::insert_elem(KeyT key, int counter, func_pointer slow_get_page) {

    int length = calculation_length(key, counter);
    cache_item c(std::make_pair(key, slow_get_page(key)), length);
    cache_.push_front(c);
    elem_finder_[key] = cache_.begin();
}

template<typename T, typename KeyT>
void perfect_cache<T, KeyT>::decrease_of_numb() {

    cache_item_iter it = cache_.begin();
    while(it != cache_.end()) {

        --(it -> numbefnext_);
        ++it;
    }
}

template<typename T, typename KeyT>
void perfect_cache<T, KeyT>::it_is_hit(KeyT key, int counter) {

    int length = calculation_length(key, counter);
    elem_finder_.find(key) -> second -> numbefnext_ = length;
    decrease_of_numb();
}

template<typename T, typename KeyT>
void perfect_cache<T, KeyT>::remove_elem(KeyT key) {

    cache_item_iter it1 = elem_finder_.find(key) -> second;
    find_iter it2 = elem_finder_.find(key);
    elem_finder_.erase(it2);
    cache_.erase(it1);
}

template<typename T, typename KeyT>
KeyT perfect_cache<T, KeyT>::victim_finder(KeyT key, int length) {

    cache_item_iter it = cache_.begin();
    KeyT cor_key = it -> page_.first;
    int cor_length = it -> numbefnext_;
    ++it;

    while(it != cache_.end()) {

        if(it -> numbefnext_ > cor_length) {

            cor_key = it -> page_.first;
            cor_length = it -> numbefnext_;
        } else if (it -> numbefnext_ < 0) {

            cor_key = it -> page_.first;
            return cor_key;
        }
        ++it;
    }
    return cor_key;
}

template<typename T, typename KeyT>
int perfect_cache<T, KeyT>::lookup_update(KeyT key, int counter, func_pointer slow_get_page) {

    ++((unordered_buffer_.find(key) -> second).amount_);

    if(cache_is_full() && elem_finder_.find(key) == elem_finder_.end()) {

        int length = calculation_length(key, counter);
        KeyT victim;
        if(length < 0) {

            victim = key;
        } else {

            victim = victim_finder(key, length);
        }

        if(victim != key) {
            remove_elem(victim);
            insert_elem(key, counter, slow_get_page);
            decrease_of_numb();
        }
        return 0;
    } else if(!cache_is_full() && elem_finder_.find(key) == elem_finder_.end()) {

        insert_elem(key, counter, slow_get_page);
        decrease_of_numb();
        return 0;
    } else {

        it_is_hit(key, counter);
        return 1;
    }
}
} // <-- namespace Cache

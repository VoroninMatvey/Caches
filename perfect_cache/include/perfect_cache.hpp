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
            int nextappearance_;

            cache_item(page_t page, int nextappearance) : page_{page}, nextappearance_{nextappearance}  {}
        };

        struct un_buf_item {
            int amount_ = 0;
            std::vector<int> history_;

        };

        using cache_item_iter = std::list<cache_item>::iterator;
        using un_buf_iter     = std::unordered_map<KeyT, un_buf_item>::iterator;
        using find_iter       = std::unordered_map<KeyT, cache_item_iter>::iterator;

public:
        perfect_cache(int capacity, int number) : capacity_{capacity}, numb_of_page_{number} {}
        void initial_assembly();
        int lookup_update(KeyT key, func_pointer slow_get_page);
        KeyT get_incoming_page(int counter) const;

private:

        const int capacity_;
        const int numb_of_page_;
        std::unordered_map<KeyT, un_buf_item> unordered_buffer_; // saves the page arrival history
        std::list<cache_item> cache_;
        std::vector<KeyT> ordered_buffer_; // saves the data received from input
        std::unordered_map<KeyT, cache_item_iter> elem_finder_; // finds element with corresponding value in cache_

        int calculation_next_appearance(KeyT key) const;
        void insert_elem(KeyT key, func_pointer slow_get_page);
        void it_is_hit(KeyT key);
        void remove_elem(KeyT key);
        KeyT victim_finder(KeyT key, int next) const;//looking for a victim from the elements of cache and incoming page, also decrease of numbefnext_ all list's elements
        bool cache_is_full() const;
}; // <-- Class perfect_cache

template<typename T, typename KeyT>
bool perfect_cache<T, KeyT>::cache_is_full() const {

    return elem_finder_.size() == capacity_;
}

template<typename T, typename KeyT>
KeyT perfect_cache<T, KeyT>::get_incoming_page(int counter) const {

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
int perfect_cache<T, KeyT>::calculation_next_appearance(KeyT key) const {

    auto it = unordered_buffer_.find(key);
    if(((it -> second).history_.begin() + (it -> second).amount_) != (it -> second).history_.end()) {

        return (it -> second).history_[(it -> second).amount_];
    } else {
        return -1;
    }

}

template<typename T, typename KeyT>
void perfect_cache<T, KeyT>::insert_elem(KeyT key, func_pointer slow_get_page) {

    int next = calculation_next_appearance(key);
    cache_item c(std::make_pair(key, slow_get_page(key)), next);
    cache_.push_front(c);
    elem_finder_[key] = cache_.begin();
}

template<typename T, typename KeyT>
void perfect_cache<T, KeyT>::it_is_hit(KeyT key) {

    int next = calculation_next_appearance(key);
    elem_finder_.find(key) -> second -> nextappearance_ = next;
}

template<typename T, typename KeyT>
void perfect_cache<T, KeyT>::remove_elem(KeyT key) {

    cache_item_iter it1 = elem_finder_.find(key) -> second;
    find_iter it2 = elem_finder_.find(key);
    elem_finder_.erase(it2);
    cache_.erase(it1);
}

template<typename T, typename KeyT>
KeyT perfect_cache<T, KeyT>::victim_finder(KeyT key, int next) const {

    auto it = cache_.cbegin();
    KeyT cor_key = it -> page_.first;
    int cor_next = it -> nextappearance_;
    ++it;

    while(it != cache_.end()) {

        if(it -> nextappearance_ > cor_next) {

            cor_key = it -> page_.first;
            cor_next = it -> nextappearance_;
        } else if (it -> nextappearance_ < 0) {

            return it -> page_.first;
        }
        ++it;
    }
    return cor_key;
}

template<typename T, typename KeyT>
int perfect_cache<T, KeyT>::lookup_update(KeyT key, func_pointer slow_get_page) {

    auto& hist = unordered_buffer_.find(key) -> second;
    ++hist.amount_;

    if(cache_is_full() && elem_finder_.find(key) == elem_finder_.end()) {

        int next = calculation_next_appearance(key);
        KeyT victim;
        if(next < 0) {

            victim = key;
        } else {

            victim = victim_finder(key, next);
        }

        if(victim != key) {
            remove_elem(victim);
            insert_elem(key, slow_get_page);
        }
        return 0;
    } else if(!cache_is_full() && elem_finder_.find(key) == elem_finder_.end()) {

        insert_elem(key, slow_get_page);
        return 0;
    } else {

        it_is_hit(key);
        return 1;
    }
}
} // <-- namespace Cache
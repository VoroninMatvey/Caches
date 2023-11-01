#include <list>
#include <unordered_map>
#include <vector>
#include <iterator>
#include <utility>
#include <cstdlib>

namespace Cache {

class perfect_cache {

        struct cache_item {
            const int page_;
            int numbefnext_;

            cache_item(int page, int numbefnext) : page_{page}, numbefnext_{numbefnext}  {}
        };

        struct un_buf_item {
            int amount_ = 0;
            std::vector<int> history_;

        };

        using cache_item_iter = typename std::list<cache_item>::iterator;
        using un_buf_iter = typename std::unordered_map<int, un_buf_item>::iterator;
        using find_iter = typename std::unordered_map<int, cache_item_iter>::iterator;

public:
         perfect_cache(int capacity, int number) : capacity_{capacity}, numb_of_page_{number} {}
         void initial_assembly();
         int lookup_update(int page, int counter);
         int get_incoming_page(int counter);

private:

        const int capacity_;
        const int numb_of_page_;
        std::unordered_map<int, un_buf_item> unordered_buffer_; // saves the page arrival history
        std::list<cache_item> cache_;
        std::vector<int> ordered_buffer_; // saves the data received from input
        std::unordered_map<int, cache_item_iter> elem_finder_; // finds element with corresponding value in cache_

        int calculation_length(int page, int counter);
        void insert_elem(int page, int counter);
        void decrease_of_numb();
        void it_is_hit(int page, int counter);
        void remove_elem(int page);
        int victim_finder(int page, int length);//lookinf for a victim from the elements of cache and incoming page, also decrease of numbefnext_ all list's elements
        bool cache_is_full();
}; // <-- Class perfect_cache

bool perfect_cache::cache_is_full() {

    return elem_finder_.size() == capacity_;
}

int perfect_cache::get_incoming_page(int counter) {

    return ordered_buffer_[counter];
}

void perfect_cache::initial_assembly() {

    int page = 0;
    un_buf_iter it;

    for(int i = 0; i < numb_of_page_; ++i) {

        std::cin >> page;
        ordered_buffer_.push_back(page);
        it = unordered_buffer_.find(page);

        if(it != unordered_buffer_.end()) {

            (it -> second).history_.push_back(i);
        } else {

            un_buf_item c;
            unordered_buffer_[page] = c;
            (unordered_buffer_.find(page) -> second).history_.push_back(i);
        }
    }
}

int perfect_cache::calculation_length(int page, int counter) {

    un_buf_iter it = unordered_buffer_.find(page);
    if(((it -> second).history_.begin() + (it -> second).amount_) != (it -> second).history_.end()) {

         int length = (it -> second).history_[(it -> second).amount_] - counter;
        return length;
    } else {
        return -1;
    }
}

void perfect_cache::insert_elem(int page, int counter) {

    int length = calculation_length(page, counter);
    cache_item c(page, length);
    cache_.push_front(c);
    elem_finder_[page] = cache_.begin();
}

void perfect_cache::decrease_of_numb() {

    cache_item_iter it = cache_.begin();
    while(it != cache_.end()) {

        --(it -> numbefnext_);
        ++it;
    }
}

void perfect_cache::it_is_hit(int page, int counter) {

    int length = calculation_length(page, counter);
    elem_finder_.find(page) -> second -> numbefnext_ = length;
    decrease_of_numb();
}

void perfect_cache::remove_elem(int page) {

    cache_item_iter it1 = elem_finder_.find(page) -> second;
    find_iter it2 = elem_finder_.find(page);
    elem_finder_.erase(it2);
    cache_.erase(it1);
}

int perfect_cache::victim_finder(int page, int length) {

    cache_item_iter it = cache_.begin();
    int cor_page = it -> page_;
    int cor_length = it -> numbefnext_;
    ++it;

    while(it != cache_.end()) {

        if(it -> numbefnext_ > cor_length) {

            cor_page = it -> page_;
            cor_length = it -> numbefnext_;
        } else if (it -> numbefnext_ < 0) {

            cor_page = it -> page_;
            return cor_page;
        }
        ++it;
    }
    return cor_page;
}

int perfect_cache::lookup_update(int page, int counter) {

    ++((unordered_buffer_.find(page) -> second).amount_);

    if(cache_is_full() && elem_finder_.find(page) == elem_finder_.end()) {

        int length = calculation_length(page, counter);
        int victim;
        if(length < 0) {

            victim = page;
        } else {

            victim = victim_finder(page, length);
        }

        if(victim != page) {
            remove_elem(victim);
            insert_elem(page, counter);
            decrease_of_numb();
        }
        return 0;
    } else if(!cache_is_full() && elem_finder_.find(page) == elem_finder_.end()) {

        insert_elem(page, counter);
        decrease_of_numb();
        return 0;
    } else {

        it_is_hit(page, counter);
        return 1;
    }
}
} // <-- namespace Cache

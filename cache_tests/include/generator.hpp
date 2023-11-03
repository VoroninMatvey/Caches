#include <vector>
#include <list>
#include <random>
#include <utility>
#include <functional>
#include <algorithm>
#include <fstream>
#include <filesystem>

namespace Tests {

//-------------------------------------------------------------------------------------------------------------------------------------

class slow_lfu{

        using list_iter = typename std::list<std::pair<const int, int>>::iterator;

public:
        slow_lfu(int capacity, int numb_of_page) : capacity_{capacity}, numb_of_page_{numb_of_page} {}
        int lookup_update(int page);

private:
        const int capacity_;
        const int numb_of_page_;
        std::list<std::pair<const int, int>> cache_;

        bool cache_is_full();
        void insert_one_node(int page);
        list_iter victim_finder();
        list_iter is_it_hit(int page); //return iterator an element with equivalent to page, if no such element is found, past-the-end iterator is returned

}; // <-- class slow_lfu

bool slow_lfu::cache_is_full() {

    return cache_.size() == capacity_;
}

void slow_lfu::insert_one_node(int page) {

    cache_.emplace_front(page, 1);
}

slow_lfu::list_iter slow_lfu::victim_finder() {

    list_iter it = cache_.begin();
    list_iter cor_it = it;
    int cor_freq = it -> second;
    ++it;

    while(it != cache_.end()) {

        if(it -> second <= cor_freq) {

            cor_it = it;
            cor_freq = it -> second;
        }
        ++it;
    }
    return cor_it;
}

slow_lfu::list_iter slow_lfu::is_it_hit(int page) {

    list_iter it = cache_.begin();

    while(it != cache_.end()) {

        if(it -> first == page) return it;
        ++it;
    }

    return cache_.end();
}

int slow_lfu::lookup_update(int page) {

    if(is_it_hit(page) == cache_.end() && cache_is_full()) {

        list_iter it = victim_finder();
        cache_.erase(it);
        insert_one_node(page);
        return 0;
    } else if(is_it_hit(page) != cache_.end()) {

        ++(is_it_hit(page) -> second);
        return 1;
    } else {

        insert_one_node(page);
        return 0;
    }
}
//-------------------------------------------------------------------------------------------------------------------------------------

class slow_perfect {

        using list_iter = typename std::list<int>::iterator;
        using buf_iter = typename std::vector<int>::iterator;

public:
        slow_perfect(int capacity, int number) : capacity_{capacity}, numb_of_page_{number} {}
        void one_iteration_initial(int page);
        int lookup_update(int page, int counter); 
        int get_page(int counter);

private:
        const int capacity_;
        const int numb_of_page_;
        std::vector<int> buffer_;
        std::list<int> cache_;

        bool cache_is_full();
        list_iter is_it_hit(int page);
        list_iter victim_finder(int page, int counter); //returns an iterator to the corresponding page in cache, or past-the-end iterator if it is an incoming page 

}; // <-- class slow_perfect

int slow_perfect::get_page(int counter) {

    return buffer_[counter];
}

void slow_perfect::one_iteration_initial(int page) {

    buffer_.push_back(page);
}

bool slow_perfect::cache_is_full() {

    return cache_.size() == capacity_;
}

slow_perfect::list_iter slow_perfect::is_it_hit(int page) {

    list_iter it = std::find(cache_.begin(), cache_.end(), page);
    return it;
}

slow_perfect::list_iter slow_perfect::victim_finder(int page, int counter) {

    buf_iter it1 = std::find(buffer_.begin() + counter + 1, buffer_.end(), page);
    if(it1 == buffer_.end()) return cache_.end();

    list_iter it2 = cache_.begin();
    list_iter cor_it;
    int cor_length;
    int length;
    

    it1 = std::find(buffer_.begin() + counter + 1, buffer_.end(), *it2);
    if(it1 == buffer_.end()) {

        return cache_.begin();
    } else {

        cor_it = cache_.begin();
        cor_length = it1 - (buffer_.begin()) - counter;
        ++it2;
    }

    while(it2 != cache_.end()) {

        it1 = std::find(buffer_.begin() + counter + 1, buffer_.end(), *it2);
        if(it1 == buffer_.end()) {

            return it2;
        } else {
            length = it1 - (buffer_.begin()) - counter;
            if(length > cor_length) {

                cor_length = length;
                cor_it = it2;
            }
            ++it2;
        }  
    }
    return cor_it;
}

int slow_perfect::lookup_update(int page, int counter) {

    if(is_it_hit(page) == cache_.end() && cache_is_full()) {

        list_iter it = victim_finder(page, counter);
        if(it != cache_.end()) {
            cache_.erase(it);
            cache_.push_front(page);
        }
        return 0;
    } else if(is_it_hit(page) == cache_.end() && !cache_is_full()) {

        cache_.push_front(page);
        return 0;
    } else {

        return 1;
    } 
}

//-------------------------------------------------------------------------------------------------------------------------------------

class generator {

public:
        generator(int capacity, int numb_of_page, int min_value_of_page, int max_value_of_page) :
                capacity_{capacity}, 
                numb_of_page_{numb_of_page},
                min_value_of_page_{min_value_of_page},
                max_value_of_page_{max_value_of_page} {}
        void test_gen(int n); //generates n test with the specified parameters, counts the number of hits for both caches, writes the tests themselves and the answers to them to files
        

private:
        const int capacity_;
        const int numb_of_page_;
        const int min_value_of_page_;
        const int max_value_of_page_;

        int random(int min_val, int max_val);
}; //<-- class generator

int generator::random(int min_val, int max_val) {

    std::random_device rd;
    std::uniform_int_distribution<int> dist(min_val, max_val);
    return dist(rd);
}

void generator::test_gen(int n) {
    namespace fs = std::filesystem;

    if(!fs::is_directory("cache_data")) {
        fs::create_directory("cache_data");
        fs::create_directory("cache_data/tests");
        fs::create_directory("cache_data/answers");
    }

    int page;
    for(int i = 0; i < n; ++i) {
    
        int lfu_hits = 0;
        int perfect_hits = 0;
        slow_lfu temp_lfu(capacity_, numb_of_page_);
        slow_perfect temp_perfect(capacity_, numb_of_page_);

        std::ofstream file_test("cache_data/tests/test" + std::to_string(i + 1) + ".txt");
        std::ofstream file_answ("cache_data/answers/answer" + std::to_string(i + 1) + ".txt");
        file_test << capacity_ << ' ' << numb_of_page_ << ' ';

        for(int j = 0; j < numb_of_page_; ++j) {
            page = random(min_value_of_page_, max_value_of_page_);
            file_test << page << ' ';
            lfu_hits += temp_lfu.lookup_update(page);
            temp_perfect.one_iteration_initial(page);
        }

        for(int j = 0; j < numb_of_page_; ++j) {

            page = temp_perfect.get_page(j);
            perfect_hits += temp_perfect.lookup_update(page, j);
        }

        file_answ << "hits of lfu cache: " << lfu_hits << '\n';
        file_answ << "hits of perfect cache: " << perfect_hits << '\n';
    }
}
} // <-- namespace Tests

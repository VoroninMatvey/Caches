#include <list>
#include <unordered_map>
#include <iterator>
#include <cstdlib>

typedef int(*func_pointer)(int);
int slow_get_page(int key) {

        return key;
}

namespace Cache {

template<typename T, typename KeyT = int>
class lfu_cache {
public:

        lfu_cache(int capacity) : capacity_{capacity} {}
        int lookup_update(KeyT key, func_pointer slow_get_page);//does all operations in the class with resulting page
private:

        struct item;
        struct freqitem;
        using page_t = std::pair<KeyT, T>;
        using itemiter = typename std::list<item>::iterator;
        using freqiter = typename std::list<freqitem>::iterator;

        const int capacity_;
        std::list<freqitem> cache_;
        std::unordered_map<KeyT, itemiter> hashtable_;

        using hashiter = typename std::unordered_map<KeyT, itemiter>::iterator;

        struct item {
                page_t page_;
                freqiter freqIt_;

                item(page_t page) : page_{page} {}
        };

        struct freqitem {
                const int freq_;
                std::list<item> itemlist_;

                freqitem(int freq) : freq_{freq} {}
        };

        bool hash_is_full();
        void delete_from_hash(KeyT key); //deletes a node in the  itemlist, then delete pair in hashtable with the corresponding key
        void search_and_delete_from_hash();//searches page in cache that need to delete and delete_from_hash
	void insert_first_node(KeyT key, func_pointer slow_get_page);//inserts a node in the itemlist with a frequency of 1, if there is not such itemlist, method creates that itemlist, changes all iterators
        void frequency_increase(KeyT key, func_pointer slow_get_page);//deletes a node in the itemlist, if there is the freqitem with a frequency of 1 more, inserts at the beginning, else creates freqitem with the right frequency and repets the steps
}; // <-- class lfu_cache

template<typename T, typename KeyT>
bool lfu_cache<T, KeyT>::hash_is_full() {

        return hashtable_.size() == capacity_;
}

template<typename T, typename KeyT>
void lfu_cache<T, KeyT>::delete_from_hash(KeyT key) {

        hashiter it1 = hashtable_.find(key);
        itemiter it2 = it1 -> second;
        auto freq_it = it2 -> freqIt_;
        freq_it -> itemlist_.erase(it2);

        if(freq_it ->itemlist_.empty()) {
                cache_.erase(freq_it);
        }

        hashtable_.erase(it1);
}

template<typename T, typename KeyT>
void lfu_cache<T, KeyT>::search_and_delete_from_hash() {

        itemiter it = cache_.begin() -> itemlist_.end();
        --it;
        page_t page = it -> page_;
        delete_from_hash(page.first);
}

template<typename T, typename KeyT>
void lfu_cache<T, KeyT>::insert_first_node(KeyT key, func_pointer slow_get_page) { 

        if(cache_.empty() || cache_.begin() -> freq_ != 1) {
                cache_.push_front(1);
        }
	
	auto& it = cache_.begin() -> itemlist_;
        it.push_front(std::make_pair(key, slow_get_page(key)));
        it.begin() -> freqIt_ = cache_.begin();
        hashtable_[key] = it.begin();
}

template<typename T, typename KeyT>
void lfu_cache<T, KeyT>::frequency_increase(KeyT key, func_pointer slow_get_page) { 

        freqiter it1 = hashtable_.find(key) -> second -> freqIt_;
        freqiter it2 = it1;
        freqiter It1 = it1;//It1 won't change in cycle
        int nextfreq = It1 -> freq_ + 1;
        freqiter It2;

        if(It1 == cache_.end()) {
                cache_.push_back(nextfreq);
                It2 = cache_.end();
        }

        else if((++it1) -> freq_ != it2 -> freq_ + 1) {
                It2 = cache_.insert(++it2, nextfreq);
        }

        else {
                It2 = ++it2;
        }

        It2 -> itemlist_.push_front(std::make_pair(key, slow_get_page(key)));
        It2 -> itemlist_.begin() -> freqIt_ = It2;

        hashiter mapIt = hashtable_.find(key);
        itemiter oldIt = mapIt -> second;
        mapIt -> second = It2 -> itemlist_.begin();

        if(oldIt -> freqIt_ -> itemlist_.size() == 1) {
                cache_.erase(oldIt -> freqIt_);
        }
        else {
                oldIt -> freqIt_ -> itemlist_.erase(oldIt);
        }

 }

template<typename T, typename KeyT>
int lfu_cache<T, KeyT>::lookup_update(KeyT key, func_pointer slow_get_page) { 

        int hit = 0;

        if(hashtable_.find(key) != hashtable_.end()) {
                ++hit;
                frequency_increase(key, slow_get_page);
        }
        else if(hash_is_full()) {
                search_and_delete_from_hash();
                insert_first_node(key, slow_get_page);
        }
        else {
                insert_first_node(key, slow_get_page);
        }
        return hit;
}
} // <-- namespace Cache

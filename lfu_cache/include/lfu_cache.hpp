#include <list>
#include <unordered_map>
#include <iterator>
#include <cstdlib>

namespace Cache {

class lfu_cache {

public:

        lfu_cache(int capacity) : capacity_{capacity} {}
        int lookup_update(int page);//does all operations in the class with resulting page
private:

        struct item;
        struct freqitem;
        using itemiter = typename std::list<item>::iterator;
        using freqiter = typename std::list<freqitem>::iterator;

        const int capacity_;
        std::list<freqitem> cache_;
        std::unordered_map<int, itemiter> hashtable_;

        using hashiter = typename std::unordered_map<int, itemiter>::iterator;

        struct item {
                const int page_;
                freqiter freqIt_;

                item(int page) : page_{page} {}
        };

        struct freqitem {
                const int freq_;
                std::list<item> itemlist_;

                freqitem(int freq) : freq_{freq} {}
        };

        bool hash_is_full();
        void delete_from_hash(int page); //deletes a node in the  itemlist, then delete pair in hashtable with the corresponding key
        void search_and_delete_from_hash();//searches page in cache that need to delete and delete_from_hash
	void insert_first_node(int page);//inserts a node in the itemlist with a frequency of 1, if there is not such itemlist, method creates that itemlist, changes all iterators
        void frequency_increase(int page);//deletes a node in the itemlist, if there is the freqitem with a frequency of 1 more, inserts at the beginning, else creates freqitem with the right frequency and repets the steps
};

bool lfu_cache::hash_is_full() {

        return hashtable_.size() == capacity_;
}

void lfu_cache::delete_from_hash(int page) {

        hashiter it1 = hashtable_.find(page);
        itemiter it2 = it1 -> second;
        it2 -> freqIt_ -> itemlist_.erase(it2);

        if(it2 -> freqIt_ ->itemlist_.empty()) {
                cache_.erase(it2 -> freqIt_);
        }

        hashtable_.erase(it1);
}

void lfu_cache::search_and_delete_from_hash() {

        itemiter it = cache_.begin() -> itemlist_.end();
        --it;
        int page = it -> page_;
        delete_from_hash(page);
}

void lfu_cache::insert_first_node(int page) {

        if(cache_.empty() || cache_.begin() -> freq_ != 1) {
                cache_.push_front(1);
        }

        cache_.begin() -> itemlist_.push_front(page);
        cache_.begin() -> itemlist_.begin() -> freqIt_ = cache_.begin();
        hashtable_[page] = cache_.begin() -> itemlist_.begin();
}

 void lfu_cache::frequency_increase(int page) {

        freqiter it1 = hashtable_.find(page) -> second -> freqIt_;
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

        It2 -> itemlist_.push_front(page);
        It2 -> itemlist_.begin() -> freqIt_ = It2;

        hashiter mapIt = hashtable_.find(page);
        itemiter oldIt = mapIt -> second;
        mapIt -> second = It2 -> itemlist_.begin();

        if(oldIt -> freqIt_ -> itemlist_.size() == 1) {
                cache_.erase(oldIt -> freqIt_);
        }
        else {
                oldIt -> freqIt_ -> itemlist_.erase(oldIt);
        }

 }

 int lfu_cache::lookup_update(int page) {

        int hit = 0;

        if(hashtable_.find(page) != hashtable_.end()) {
                ++hit;
                frequency_increase(page);
        }
        else if(hash_is_full()) {
                search_and_delete_from_hash();
                insert_first_node(page);
        }
        else {
                insert_first_node(page);
        }
        return hit;
}
} // <-- namespace Cache

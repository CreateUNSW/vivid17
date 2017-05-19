#ifndef PRIORITY_Q_H
#define PRIORITY_Q_H

#include <vector>
using namespace std;

namespace std {
  void __throw_length_error(char const*) {}
}

struct Item {
    int key;
    int weight;
    
    Item(int key, int weight) {
        this->key = key;
        this->weight = weight;
    }
};

/**
 * PriorityQ implementations
 */
class PriorityQ {
    // INTERNAL NOTE: always stored descending i.e _items[0] > _items[1] ...
    vector <Item> _items;
    
public:
    
    static const int MAX_VALUE;
    
    /**
     * adds an item
     * @param key    key
     * @param weight weight of key
     */
    void insert(int key, int weight) {
        if(weight > this->MAX_VALUE) {
            weight = this->MAX_VALUE;
        }

        // Binary search
        vector<Item>::iterator mid = _items.begin();
        vector<Item>::iterator lo = _items.begin();
        vector<Item>::iterator hi = _items.end();
        int dist = std::distance(lo, hi);
        
        while(dist > 1) {
            mid = lo;
            std::advance(mid, dist/2);
        
            if(weight <= mid->weight) {
                // Searches right
                lo = mid;
            } else {
                // Searches left
                hi = mid;
            }
            dist = std::distance(lo, hi);
        }
        
        _items.insert(hi, Item(key, weight));
    };
    
    /**
     * deletes the minimum weighted element
     * @param  key returned weight
     * @return       the key
     */
    int delMin(int &weight) {
        Item thing(_items.back());
        _items.pop_back();
        weight = thing.weight;
        return thing.key;
    }
    
    /**
     * overloaded function
     * @return see above
     */
    int delMin() {
        int weight;
        return delMin(weight);
    }
    
    /**
     * empty test
     * @return true if it is empty (i.e there are no elements with value less than infinite)
     */
    bool isEmpty() {
        return _items.empty() || _items.back().weight >= this->MAX_VALUE;
    }
    
    /**
     * changes the weight of the key
     * @param key    key
     * @param weight new weight
     */
    void change(int key, int weight) {
        if(weight > this->MAX_VALUE) {
            weight = this->MAX_VALUE;
        }
        vector<Item>::iterator it;
        for(it = _items.begin();
            it != _items.end();
            it++
        ) {
            if(it->key == key) {
                _items.erase(it);
                this->insert(key, weight);
                break;
            }
        }
    }
};

const int PriorityQ::MAX_VALUE = 20000;

#endif

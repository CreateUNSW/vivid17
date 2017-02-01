#ifndef PRIORITY_Q_H
#define PRIORITY_Q_H

#include <vector>
using namespace std;

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
    
    static const int INFINITE = 20000;
    
    /**
     * adds an item
     * @param key    key
     * @param weight weight of key
     * TODO algo right now is O(n) make it O(logn) by using binary search
     */
    void insert(int key, int weight) {
        if(weight > this->INFINITE) {
            weight = this->INFINITE;
        }
        vector<Item>::iterator it;
        for(it = _items.begin();
            it != _items.end();
            it++
        ) {
            if(it->weight < weight) {
                break;
            }
        }
        _items.insert(it,Item(key,weight));
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
        return _items.empty() || _items.back().weight < this->INFINITE;
    }
    
    /**
     * cahgnes the weight of the key
     * @param key    key
     * @param weight new weight
     */
    void change(int key, int weight) {
        if(weight > this->INFINITE) {
            weight = this->INFINITE;
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

#endif
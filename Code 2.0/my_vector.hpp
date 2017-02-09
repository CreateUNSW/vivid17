#ifndef MY_VECTOR_H
#define MY_VECTOR_H

// uncomment below to log things properly
// #include <typeinfo>
// #include <iostream>
// #include <cxxabi.h>
// using namespace std;
// 
// template <typename T>
// char* realname() {
//     int status;
//     return abi::__cxa_demangle(typeid(T).name(), 0, 0, &status);
// }


template <typename T> 
struct _node {
    T* item;
    _node<T> *next, *prev;
    
    _node(T i, _node<T> * n){
        item = new T(i);
        next = n;
        prev = nullptr;
    }
    
    _node& operator=(T val) {
        item = val;
    }
    
    ~_node() {
        delete item;
    }
};

template <typename T>
class vector {
    
    _node<T> *_start, *_finish;
    int _size;
    
    void _purge() {
        _node<T> * ptr = _start;
        while( ptr != nullptr) {
            _node<T> * toDel = ptr;
            ptr = ptr -> next;
            delete toDel;
        }
        _size = 0;
        _start = _finish = nullptr;
    }
    
    void _resize(int size, T all) {
        _size = size;
        T* val = new T();
        _finish = new _node<T>(*val, nullptr);
        delete val;
        _node<T> * ptr = _finish;
        for(int i=0;i<size;i++) {
            ptr = new _node<T>(all,ptr);
            if(ptr->next != nullptr) {
                ptr->next->prev = ptr;
            }
        }
        _start = ptr;
        _start->prev = nullptr;
    }
    
public:
    class iterator {
        _node<T> * thing;
    public:
        //constructor
        iterator(_node <T> * n){
            thing = n;
        }
        iterator() {
            thing = nullptr;
        }
        
        //operators
        T* operator->() {
            return (thing->item);
        }
        iterator& operator=(iterator const rhs) {
            thing = rhs.thing;
            return *this;
        }
        bool operator!=(iterator const rhs) {
            return thing != rhs.thing;
        }
        iterator& operator++() {
            thing = thing->next;
            return *this;
        }
        iterator operator++(int) {
            iterator ret = *this;
            thing = thing->next;
            return ret;
        }
        iterator& operator--() {
            thing = thing->prev;
            return *this;
        }
        iterator operator--(int) {
            iterator ret = *this;
            thing = thing->prev;
            return ret;
        }
        bool operator==(iterator rhs) {
            return this->thing == rhs.thing;
        }
        
        //ATTENTION DO NOT CALL OUTSIDE THIS FILE
        void purge() {
            delete thing;
        }
        
        _node<T> *get() {
            return thing;
        }
    };
    
    //constructors
    vector(int size, T all) {
        _resize(size,all);
    }

    vector() {
        T* val = new T();
        _resize(0, *val);
        delete val;
    }
    
    vector(vector<T> &cpy) {
        _size = cpy.size();
        T* val = new T();
        _finish = new _node<T>(*val, nullptr);
        delete val;
        _node<T> * ptr = _finish;
        for(int i=0;i<_size;i++) {
            ptr = new _node<T>(cpy[i],ptr);
            if(ptr->next != nullptr) {
                ptr->next->prev = ptr;
            }
        }
        _start = ptr;
        _start->prev = nullptr;
    }
    
    ~vector() {
        _purge();
    }
    
    //iterators
    iterator begin() {
        return iterator(_start);
    }
    iterator end() {
        return iterator(_finish);
    }
    
    //accessors
    T back() {
        return *(_finish->prev->item);
    }
    
    //capacity 
    bool empty() {
        return _size == 0;
    }
    int size() {
        return _size;
    }
    
    //Mutators
    void pop_back() {
        if(_size == 0) {
            throw "empty vector";
        }
        erase(--end());
    }
    void erase(iterator index) {
        if (index == this->end()) {
            throw "invalid erasing";
        }
        _size --;
        _node<T> *prev, *next;
        
        if(index == this->begin()) {
            next = index.get()->next;
            _start = next;
            next->prev = nullptr;
            index.purge();
            return;
        }
        
        
        prev = index.get()->prev;
        next = index.get()->next;
        prev->next = next;
        next->prev = prev;
        index.purge();
        
    }
    void insert(iterator after,T item) {
        _size++;
        _node<T> *prev, *next;
        
        if(after == this->begin()) {
            _node<T> *next = after.get();
            _start = new _node<T> (item,next);
            _start->prev = nullptr;
            next->prev = _start;
            return;
        }
        
        prev = after.get()->prev;
        next = after.get();
        
        prev->next = new _node<T>(item,next);
        prev->next->prev = prev;
        next->prev = prev->next;
    }
    //NOTE: removes any old data that was already present
    void resize(int size, T all) {
        _purge();
        _resize(size, all);
    }
    
    //operators
    T& operator[](int index) {
        _node<T> *ptr = _start;
        for(int i=0;i<index;i++)
            ptr = ptr->next;
        
        return *(ptr->item);
    }
    
};

template<typename T>
int distance (typename vector<T>::iterator start,typename  vector<T>::iterator end) {
    int i = 0;
    while(start != end) {
        start++;
        i++;
    }
    return i;
}

template<typename T>
void advance (typename vector<T>::iterator &start,int steps) {
    for(int i=0;i<steps;i++)
        start++;
}

#endif
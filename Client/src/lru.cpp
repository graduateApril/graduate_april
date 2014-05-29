/*
* pursuit
* Created Time:  2014年01月22日 星期三 19时58分35秒
* File Name: asq_lru.cpp
*/

#include <iostream>
#include <ext/hash_map>
#include <cstdio>
using namespace __gnu_cxx;

template<typename K, typename T>
struct LruCacheEntry{
    int key;
    int value;
    struct LruCacheEntry* prev;
    struct LruCacheEntry* next;
};
    
    
template<typename K, typename T>
class LruCache {
private:
    hash_map<K, LruCacheEntry<K, T>* > _hashmap;
    int _size;
    LruCacheEntry<K, T>* _head;
    LruCacheEntry<K, T>* _tail;
    LruCacheEntry<K, T>*  _entries;
public:
    LruCache()
        : _entries(NULL)
        , _head(NULL)
        , _tail(NULL)
        , _size(0)
    {};
    ~LruCache() {};
    int create(int size);
    void destroy();
    int set(K key, T value);
    int get(K key, T* value);
private:
    void detach(LruCacheEntry<K, T>* node);
    void attach(LruCacheEntry<K, T>* node);
};

template<typename K, typename T>
int LruCache<K, T>::create(int size)
{
    _size = size;
    _entries = new(std::nothrow) LruCacheEntry<K, T>[size];
    if (_entries == NULL){
        return -1;
    }
    _head = new LruCacheEntry<K, T>;
    _tail = new LruCacheEntry<K, T>;
    if (_head == NULL || _tail == NULL) {
        return -1;
    }
    _head->prev = NULL;
    _head->next = _tail;
    _tail->prev = _head;
    _tail->next = NULL;
    return 0;
}

template<typename K, typename T>
void LruCache<K, T>::destroy()
{
    delete[] _entries;
    _entries = NULL;
    delete _head;
    _head = NULL;
    delete _tail;
    _tail = NULL;

}

template<typename K, typename T>
int LruCache<K, T>::set(K key, T value)
{
    LruCacheEntry<K, T>* node;
    node = _hashmap[key];
    if (node){
        node->value = value;
        detach(node);
        attach(node);
        return 0;
    }
    
    if (_size > 0) {
        _size--;
        node = _entries + _size;
        node->key = key;
        node->value = value;
        attach(node);
        _hashmap[key] = node;
    } else {
        node = _tail->prev;
        _hashmap.erase(node->key);
        node->key = key;
        node->value = value;
        detach(node);
        attach(node);
        _hashmap[key] = node;
    }

    return 0;
}

template<typename K, typename T>
int LruCache<K, T>::get(K key, T* value)
{
    LruCacheEntry<K, T>* node;
    node = _hashmap[key];
    if (node){
        detach(node);
        attach(node);
        *value = node->value;
        return 0;
    }

    return -1;
}   

template<typename K, typename T>
void LruCache<K, T>::detach(LruCacheEntry<K, T>* node)
{
    node->next->prev = node->prev;
    node->prev->next = node->next;
}

template<typename K, typename T>
void LruCache<K, T>::attach(LruCacheEntry<K, T>* node)
{
    _head->next->prev = node;
    node->next = _head->next;
    _head->next = node;
    node->prev = _head;
}

    

int main()
{
    LruCache<int, int> _lru;
    if (_lru.create(10) != 0){
        puts("error create");
        return -1;
    }
    
    int val = 0;
    for (int i = 0; i < 10; i++) {
        if (_lru.get(i, &val) != -1) {
            printf("is cached %d %d\n", i, val);
        } else {
            if(_lru.set(i, i+1) != 0){
                puts("error set");
            }
        }
    }
     for (int i = 5; i < 10; i++) {
        if (_lru.get(i, &val) != -1) {
            printf("is cached %d %d\n", i, val);
        } else {
            if(_lru.set(i, i+1) != 0){
                puts("error set");
            }
        }
    }
   
     _lru.destroy();
     return 0;
}
     

#include <bits/stdc++.h>

using namespace std;

class LFUCache {
private:
    int capacity, timer = 0, min_freq = 0;
    // key: { count, pointer to key-value pair }
    unordered_map<int, pair<int, list<pair<int, int>>::iterator>> cache;
    // count: { key-value pairs }
    unordered_map<int, list<pair<int, int>>> frequencies;

    void access(int key, int frequency, int value) {
        frequencies[frequency].push_back({key, value});
        cache[key] = { frequency, prev(frequencies[frequency].end()) };
    }

public:
    LFUCache(int capacity) {
        this->capacity = capacity;
    }
    
    int get(int key) {
        auto it = cache.find(key);
        if (it == cache.end()) {
            return -1;
        } else {
            auto [f, iter] = it->second;
            pair<int, int> kv = *iter;
            frequencies[f].erase(iter);
            if (frequencies[f].empty()) {
                frequencies.erase(f);
                if (min_freq == f) {
                    min_freq++;
                }
            }
            access(key, f + 1, kv.second);
            return kv.second;
        }
    }
    
    void put(int key, int value) {
        auto it = cache.find(key);
        if (it != cache.end()) {
            it->second.second->second = value;
            get(key);
        } else {
            if (capacity == cache.size()) {
                cache.erase(frequencies[min_freq].front().first);
                frequencies[min_freq].pop_front();
                if (frequencies[min_freq].empty()) {
                    frequencies.erase(min_freq);
                }
            }
            min_freq = 1;
            access(key, 1, value);
        }
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
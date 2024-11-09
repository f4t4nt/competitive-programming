#include <bits/stdc++.h>

using namespace std;

class RandomizedCollection {
private:
    vector<int> data;
    unordered_map<int, vector<int>> idxs;

public:
    RandomizedCollection() {
        
    }

    bool insert(int val) {
        int idx = data.size();
        data.push_back(val);
        auto it = idxs.find(val);
        if (it == idxs.end()) {
            idxs[val].push_back(idx);
            return true;
        } else {
            it->second.push_back(idx);
            return false;
        }
    }
    
    bool remove(int val) {
        auto it = idxs.find(val);
        if (it == idxs.end() || it->second.empty()) {
            return false;
        }

        int idx = it->second.back();
        it->second.pop_back();

        if (idx != (int) data.size() - 1) {
            int lastElement = data.back();
            data[idx] = lastElement;
            auto& lastElementIdxs = idxs[lastElement];
            if (lastElementIdxs.back() == (int) data.size() - 1) {
                lastElementIdxs.back() = idx;
            } else {
                for (int& i : lastElementIdxs) {
                    if (i == data.size() - 1) {
                        i = idx;
                        break;
                    }
                }
            }
        }

        data.pop_back();
        if (it->second.empty()) {
            idxs.erase(it);
        }
        return true;
    }
    
    int getRandom() {
        return data[rand() % data.size()];
    }
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection* obj = new RandomizedCollection();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
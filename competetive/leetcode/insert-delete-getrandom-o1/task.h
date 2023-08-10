#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <random>

#include <iostream>


class RandomizedSet {
    std::mt19937 gen;
    std::random_device rd;

    int length = 0;
    std::vector<int> values;
    std::unordered_map<int, int> key_map;
public:
    RandomizedSet() {
        gen.seed(rd());
    }
    
    bool insert(int val) {
        if (key_map.count(val) && key_map[val] < length)
            return false;
        
        key_map[val] = length;

        if (length >= values.size()) {
            values.push_back(val);
        } else {
            values[length] = val;
        }
        ++length;

        return true;
    }
    
    bool remove(int val) {
        if (!key_map.count(val) || key_map[val] >= length)
            return false;
        
        int idx = key_map[val];
        --length;

        if (length == 0)
            values.clear();
        else {
            std::swap(values[idx], values[length]);
            key_map[values[idx]] = idx;
            key_map[values[length]] = length + 1;
        }

        key_map.erase(val);

        return true;
    }
    
    int getRandom() {
        std::uniform_int_distribution<> dis(0, length - 1);
        return values[dis(gen)];
    }
};

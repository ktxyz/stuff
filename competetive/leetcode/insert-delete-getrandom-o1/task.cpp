#include <iostream>
#include <ctime>
#include <set>

#include "task.h"


class BruteRandomizedSet {
    std::set<int> set_;
public:
    bool insert(int val) {
        if (set_.find(val) != set_.end())
            return false;

        set_.insert(val);
        return true;
    }

    bool remove(int val) {
        if (set_.find(val) == set_.end())
            return false;

        set_.erase(val);
        return true;
    }

    int size() {
        return set_.size();
    }

    int getRandom() {
        int idx = std::rand() % set_.size();
        auto it = set_.begin();
        std::advance(it, idx);
        return *it;
    }
};

int main() {
    std::srand(time(0));

    auto brute = BruteRandomizedSet();
    auto random = RandomizedSet();

    while (true) {
        int action = std::rand() % 3;

        if (brute.size() == 0 && action == 2)
            action = std::rand() % 2;
        
        int val = std::rand() % 10;

        if (action == 0) {
            std::cout << "insert " << val << std::endl;
            if (brute.insert(val) != random.insert(val)) {
                std::cout << "insert failed" << std::endl;
                return 1;
            }
        } else if (action == 1) {
            std::cout << "remove " << val << std::endl;
            if (brute.remove(val) != random.remove(val)) {
                std::cout << "remove failed" << std::endl;
                return 1;
            }
        } else {
            std::cout << "getRandom" << std::endl;
            if (brute.size() == 0)
                continue;
            
            auto random_ans = random.getRandom();
            if (brute.insert(random_ans)) {
                std::cout << "getRandom failed: " << random_ans << std::endl;
                return 1;
            }
        }
    }
}
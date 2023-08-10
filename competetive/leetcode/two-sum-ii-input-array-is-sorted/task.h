#include <vector>
#include <algorithm>


class Solution {
    static constexpr int OFFSET = 1000;
    static constexpr int MAXVAL = 3000;
    
    bool CanBeUsed[MAXVAL + 1];
public:
    std::vector<int> twoSum(std::vector<int>& numbers, int target) {
        target += OFFSET;
        for(auto &v : numbers)
            v += OFFSET;
        
        for(int i = 0; i < numbers.size(); ++i) {
            auto &v = numbers[i];
            
            if (CanBeUsed[v]) {
                auto k = (int)(std::lower_bound(numbers.begin(), numbers.end(), (target - v + OFFSET)) - numbers.begin());
                return {k + 1, i + 1};
            }
            else 
                CanBeUsed[(target - v) + OFFSET] = i + 1;
        }
        return {};
    }
};
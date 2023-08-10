#include <vector>


class Solution {
public:
    int majorityElement(std::vector<int>& nums) {
        int x = 1;
        int element = -1;
        for(auto &v : nums) {
            if (v == element)
                ++x;
            else
                --x;

            if (x == 0)
                element = v, x = 1;
        }

        return element;
    }
};
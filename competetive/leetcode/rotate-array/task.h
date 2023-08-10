#include <algorithm>
#include <vector>


class Solution {
public:
    void rotate(std::vector<int>& nums, int k) {
        std::rotate(nums.rbegin(), nums.rbegin() + (k % nums.size()), nums.rend());
    }
};
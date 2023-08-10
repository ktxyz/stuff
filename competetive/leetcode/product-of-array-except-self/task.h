#include <vector>


class Solution {
public:
    std::vector<int> productExceptSelf(std::vector<int>& nums) {
        std::vector<int> product_left(nums.size(), 1);
        std::vector<int> product_right(nums.size(), 1);
        
        for(int i = 0; i < (nums.size() - 1); ++i)
            product_right[i] = product_right[i] * nums[i + 1];

        for(int i = nums.size() - 2; i >= 0; --i)
            product_right[i] *= product_right[i + 1];

        for(int i = (nums.size() - 1); i >= 1; --i)
            product_left[i] = product_left[i] * nums[i - 1];
        for(int i = 1; i < nums.size(); ++i)
            product_left[i] *= product_left[i - 1];

        std::vector<int> result;

        for(int i = 0; i < nums.size(); ++i)
            result.push_back(product_left[i] * product_right[i]);
        return result;
    }
};
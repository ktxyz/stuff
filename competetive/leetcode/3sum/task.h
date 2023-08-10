#include <vector>
#include <algorithm>


class Solution {
public:
    std::vector<std::vector<int>> threeSum(vector<int>& nums) {
        std::unordered_map<int, int> map;
        std::set<std::vector<int>> triplets;

        for(auto &v : nums)
            ++map[v];

        std::sort(nums.begin(), nums.end());
        nums.erase(std::unique(nums.begin(), nums.end()), nums.end());

        if (map[0] >= 3)
            triplets.insert({0, 0, 0});

        for(int i = 0; i < nums.size(); ++i) {
            for(int j = i + 1; j < nums.size(); ++j) {
                int k = -(nums[i] + nums[j]);

                int c = map[k] - (k == nums[j]) - (k == nums[i]);
                
                if (c < 1)
                    continue;
                
                std::vector<int> triplet = {nums[i], nums[j], k};
                std::sort(triplet.begin(), triplet.end());
                triplets.insert(triplet);
            }
        }

        return std::vector(triplets.begin(), triplets.end());
    }
};
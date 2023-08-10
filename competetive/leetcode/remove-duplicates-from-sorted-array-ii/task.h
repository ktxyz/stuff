class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int removed = 0;

        for(int i = 2; i < (nums.size() - removed);) {
            if (nums[i] == nums[i - 1] && nums[i] == nums[i - 2]) {
                removed += 1;
                for(int j = i; j < (nums.size() - removed); ++j)
                    std::swap(nums[j], nums[j + 1]);
            } else {
                ++i;
            }
        }

        return (nums.size() - removed);
    }
};
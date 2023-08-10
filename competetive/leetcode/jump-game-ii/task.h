#include <vector>


class Solution {
public:
    int jump(std::vector<int>& nums) {
        if (nums.size() < 2)
            return 0;

        int i = 0;
        int MaxJump = nums[0] + 1;
        int cost = 1;

        do {
            if (MaxJump >= nums.size())
                break;
            int NewMaxJump = MaxJump;
            while(i < MaxJump) {
                NewMaxJump = std::max(NewMaxJump, i + nums[i] + 1);
                ++i;
            };

            MaxJump = NewMaxJump;
            ++cost;
        } while (MaxJump > i);
        
        return cost;
    }
};
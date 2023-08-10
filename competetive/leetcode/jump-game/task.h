#include <vector>


class Solution {
public:
    bool canJump(std::vector<int>& nums) {
        int i = 0;
        int MaxJump = nums[0] + 1;

        do {
            if (MaxJump >= nums.size())
                return true;

            int NewMaxJump = MaxJump;
            while(i < MaxJump) {
                NewMaxJump = std::max(NewMaxJump, i + nums[i] + 1);
                ++i;
            };

            MaxJump = NewMaxJump;
        } while (MaxJump > i);

        return false;
    }
};
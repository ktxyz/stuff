#include <vector>


class Solution {
public:
    int minSubArrayLen(int target, std::vector<int>& nums) {
        // can also be solved with 2 pointers

        std::vector<int> prefix_sum(nums.size() + 1, 0);
        for(int i = 0; i < nums.size(); ++i)
            prefix_sum[i + 1] = nums[i] + prefix_sum[i];

        int answer = nums.size();

        if (prefix_sum.back() < target)
            return 0;
        
        for(int i = 0; i < nums.size(); ++i) {
            int low = i;
            int high = nums.size() - 1;

            for(int _ = 0; _ < 20; ++_) {
                int mid = (low + high) / 2;

                if (prefix_sum[mid + 1] - prefix_sum[i] >= target)
                    high = mid;
                else
                    low = mid + 1;
            }

            if (prefix_sum[high + 1] - prefix_sum[i] >= target)
                answer = std::min(high - i + 1, answer);
        }

        return answer;
    }
};
#include <vector>


class Solution {
public:
    int minSubArrayLen(int target, std::vector<int>& nums) {
        // can also be solved with binary search

        int answer = nums.size() + 1;

        int sum = 0;
        int left = 0, right = 0;
        while(right < nums.size() && sum < target)
            sum += nums[right++];

        if (sum < target)
            return 0;

        while (left < nums.size()) {
            while (sum >= target) {
                answer = std::min(answer, right - left);
                sum -= nums[left++];
            }

            while (right < nums.size() && sum < target)
                sum += nums[right++];

            if (sum < target)
                break;
        }

        return answer;
    }
};
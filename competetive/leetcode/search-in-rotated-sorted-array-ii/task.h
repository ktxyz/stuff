#include <vector>
#include <functional>
#include <algorithm>

#ifdef DEBUG
    #include <iostream>
    #define PRINT(x) std::cout << #x << " = " << x << std::endl;
    #define LOG(x) std::cout << x << std::endl;
#else
    #define PRINT(x)
    #define LOG(x)
#endif

class Solution {
public:
    bool search(std::vector<int>& nums, int target) {
        // finding pivot - we can do that in O(log^2 N) time
        if (nums.size() < 16) {
            auto it = std::find(nums.begin(), nums.end(), target);
            return it != nums.end();
        }

        auto find_answer = [&](bool comp_smaller) {
            std::function<int(int, int)> find_pivot;
            find_pivot = [&](int left, int right) -> int {
                if (left >= right) {
                    return 1e5;
                }

                int mid = (left + right) / 2;

                if (comp_smaller) {
                    if (nums[0] < nums[mid])
                        return std::min(mid, find_pivot(left, mid));
                    else
                        return std::min(find_pivot(left, mid), find_pivot(mid + 1, right));
                } else {
                    if (nums[0] > nums[mid])
                        return std::min(mid, find_pivot(left, mid));
                    else
                        return std::min(find_pivot(left, mid), find_pivot(mid + 1, right));
                }
            };

            auto pivot = find_pivot(0, nums.size() - 1);
            PRINT(pivot);

            // All values are equal
            if (pivot == 1e5)
                return target == nums[0];

            // Binary search
            auto left_val = std::lower_bound(nums.begin(), nums.begin() + pivot, target);
            auto right_val = std::lower_bound(nums.begin() + pivot, nums.end(), target);

            if (left_val != nums.end() && *left_val == target)
                return true;
            if (right_val != nums.end() && *right_val == target)
                return true;

            return false;
        };

        return find_answer(false) || find_answer(true);
    }
};
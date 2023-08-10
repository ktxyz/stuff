#include <vector>


class Solution {
public:
    int trap(std::vector<int>& height) {
        int n = height.size();
        int left = 0, right = n - 1;
        int maxLeft = 0, maxRight = 0;
        int waterTrapped = 0;

        while (left <= right) {
            if (height[left] <= height[right]) {
                maxLeft = std::max(maxLeft, height[left]);
                waterTrapped += maxLeft - height[left];
                left++;
            } else {
                maxRight = std::max(maxRight, height[right]);
                waterTrapped += maxRight - height[right];
                right--;
            }
        }

        return waterTrapped;
    }
};

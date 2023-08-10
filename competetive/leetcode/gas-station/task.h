#include <vector>


class Solution {
public:
    int canCompleteCircuit(std::vector<int>& gas, std::vector<int>& cost) {
        int gain = 0, max_gain = 0, max_gain_idx = 0;

        for(int i = 0; i < gas.size(); ++i) {
            gain += gas[i] - cost[i];
            max_gain += gas[i] - cost[i];

            if (gain < 0) {
                gain = 0;
                max_gain_idx = i + 1;
            }
        }

        if (max_gain < 0)
            return -1;
        return max_gain_idx;
    }
};
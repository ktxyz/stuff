#include <vector>
#include <algorithm>


class Solution {
public:
    int maxProfit(std::vector<int>& prices) {
        int answer = 0;
        int max = prices.back();

        for(int i = prices.size() - 2; i >= 0; --i) {
            answer = std::max(answer, max - prices[i]);
            max = std::max(max, prices[i]);
        }

        return answer;
    }
};
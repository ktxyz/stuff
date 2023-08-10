#include <vector>


class Solution {
public:
    int hIndex(std::vector<int>& citations) {
        std::vector<int> pref_sum(1001, 0);

        for(auto &c : citations)
            pref_sum[c] += 1;
        
        for(int i = pref_sum.size() - 2; i >= 0; --i)
            pref_sum[i] += pref_sum[i + 1];

        for(int i = 0; i < pref_sum.size(); ++i)
            if (pref_sum[i] < i)
                return i - 1;
        return 1000;
    }
};
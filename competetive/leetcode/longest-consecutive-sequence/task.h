#include <vector>
#include <algorithm>
#include <unordered_map>


class Solution {
public:
    int longestConsecutive(std::vector<int>& nums) {
        std::unordered_map<int, bool> visited;

        for(auto &n : nums)
            visited[n] = true;

        int n_length = 0;
        for(auto it : visited) {
            if (visited.count(it.first - 1))
                continue;
            int l = 1;
            int v = it.first;
            while(visited.count(v + 1)) {
                ++v;
                ++l;
            }
            n_length = std::max(n_length, l);
        }

        return n_length;        
    }
};
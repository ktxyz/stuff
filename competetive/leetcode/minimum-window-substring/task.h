#include <string>
#include <vector>


class Solution {
public:
    std::string minWindow(std::string s, std::string t) {
        std::vector<int> count(52, 0);
        
        int left = 0;
        int right = 0;
        int answer = s.size() + 1;
        int answer_idx = 0;

        auto char_val = [](char a) {
            if (a >= 'a' && a <= 'z') return a - 'a' + 26;
            return a - 'A';
        };

        auto is_valid = [&]() {
            for(auto &c : count)
                if (c > 0)
                    return false;
            return true;
        };

        for(auto &c : t)
            ++count[char_val(c)];

        while(right < s.size() && !is_valid())
            --count[char_val(s[right++])];
        
        if (!is_valid())
            return "";

        while (left < s.size()) {
            while (is_valid()) {
                if (right - left < answer) {
                    answer = right - left;
                    answer_idx = left;
                }

                ++count[char_val(s[left++])];
            }

            while (right < s.size() && !is_valid())
                --count[char_val(s[right++])];

            if (!is_valid())
                break;
        }

        return s.substr(answer_idx, answer);
    }
};
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int answer = 0;
        unordered_map<char, bool> M;
        int i = 0;
        int j = 0;
        while(i < s.size() && j < s.size()) {
            while(j < s.size() && M[s[j]] == false) {
                M[s[j++]] = true;
            }
            answer = max(answer, j - i);
            while(j < s.size() && M[s[j]] == true)
                M[s[i++]] = false;
        }
        return answer;
    }
};
class Solution:
    def getWordsInLongestSubsequence(self, n, words, groups):
        def _get_with_start(n, words, groups, start):
            ans = []
            idx = 0
            while idx < n and groups[idx] != start:
                idx += 1
            if idx == n:
                return ans
            ans += [words[idx]]
            prev_group = start ^ 1

            while idx < n:
                if groups[idx] == prev_group:
                    ans += [words[idx]]
                    prev_group ^= 1
                idx += 1
            return ans
        
        return max(_get_with_start(n, words, groups, 0), _get_with_start(n, words, groups, 1), key=len)
        
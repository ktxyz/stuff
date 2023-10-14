class Solution:
    def lastVisitedIntegers(self, words):
        ans = []
        numbers = []
        consecutive = 0
        for i in range(len(words)):
            if words[i] == "prev":
                consecutive += 1
                if consecutive > len(numbers):
                    ans += [-1]
                else:
                    ans += [numbers[-consecutive]]
            else:
                numbers += [int(words[i])]
                consecutive = 0
        return ans

sol = Solution()

print(sol.lastVisitedIntegers(["1", "2", "prev", "prev", "prev"]))
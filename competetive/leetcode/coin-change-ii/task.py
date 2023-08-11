from typing import List


class Solution:
    def change(self, amount: int, coins: List[int]) -> int:
        ways = [1] + [0] * amount

        for c in coins:
            for idx, val in enumerate(ways):
                if idx + c > amount:
                    break
                if ways[idx] > 0:
                    ways[idx + c] += ways[idx]

        return ways[amount]
from collections import defaultdict
from typing import List


class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        dicts = defaultdict(int)

        for i, num in enumerate(nums):
            if not dicts.get(target - num) is None:
                return [dicts.get(target - num), i]
            dicts[num] = i
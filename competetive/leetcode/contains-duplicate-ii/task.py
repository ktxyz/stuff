from typing import List


class Solution:
    def containsNearbyDuplicate(self, nums: List[int], k: int) -> bool:
        num_indices = {}
        
        for i, num in enumerate(nums):
            if num in num_indices and i - num_indices[num] <= k:
                return True
            num_indices[num] = i
        
        return False
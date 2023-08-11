from typing import List


class Solution:
    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        mapping = dict()

        for s in strs:
            mapping[str(sorted(s))] = mapping.get(str(sorted(s)), []) + [s]
        
        return list(mapping.values())
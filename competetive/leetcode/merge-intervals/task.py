from typing import List


class Solution:
    def merge(self, intervals: List[List[int]]) -> List[List[int]]:
        ranges = []

        events = []
        for r in intervals:
            events.append((r[0], 0))
            events.append((r[1], 1))
        events.sort()

        l = -1
        count = 0
        for ev in events:
            if ev[1] == 0:
                if count == 0:
                    l = ev[0]
                count += 1
            else:
                count -= 1
                if count == 0:
                    ranges.append([l, ev[0]])

        return ranges
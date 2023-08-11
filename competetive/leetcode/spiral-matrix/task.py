from typing import List


class Solution:
    def spiralOrder(self, matrix: List[List[int]]) -> List[int]:
        order = []
        min_h = 0
        min_w = 0
        max_h = len(matrix)
        max_w = len(matrix[0])

        dirIdx = 0
        dirs = [(0, 1), (1, 0), (0, -1), (-1, 0)]

        x = 0
        y = 0
        while min_w <= x < max_w or min_h <= y < max_h:
            ny = y + dirs[dirIdx][0]
            nx = x + dirs[dirIdx][1]

            if min_w <= nx < max_w and min_h <= ny < max_h:
                order.append(matrix[y][x])
                x, y = nx, ny
            else:
                dirIdx = (dirIdx + 1) % 4

                if dirIdx == 0:
                    min_w += 1
                elif dirIdx == 1:
                    min_h += 1
                elif dirIdx == 2:
                    max_w -= 1
                else:
                    max_h -= 1
        return order + [matrix[y][x]]

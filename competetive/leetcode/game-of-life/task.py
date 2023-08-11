from typing import List


class Solution:
    def gameOfLife(self, board: List[List[int]]) -> None:
        m, n = len(board), len(board[0])
        directions = [(1, 0), (-1, 0), (0, 1), (0, -1), (1, 1), (1, -1), (-1, 1), (-1, -1)]
        
        for i in range(m):
            for j in range(n):
                live_neighbors = 0
                for d_i, d_j in directions:
                    ni, nj = i + d_i, j + d_j
                    if 0 <= ni < m and 0 <= nj < n and abs(board[ni][nj]) == 1:
                        live_neighbors += 1
                
                if board[i][j] == 1 and (live_neighbors < 2 or live_neighbors > 3):
                    board[i][j] = -1
                if board[i][j] == 0 and live_neighbors == 3:
                    board[i][j] = 2
        
        for i in range(m):
            for j in range(n):
                if board[i][j] > 0:
                    board[i][j] = 1
                else:
                    board[i][j] = 0

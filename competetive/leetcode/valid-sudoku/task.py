from typing import List

class Solution:
    def isValidSudoku(self, board: List[List[str]]) -> bool:
        rows = [set() for _ in range(9)]
        columns = [set() for _ in range(9)]
        boxes = [set() for _ in range(9)]
        
        for i in range(9):
            for j in range(9):
                num = board[i][j]
                if num != '.':
                    if num in rows[i]:
                        return False
                    rows[i].add(num)
                    
                    if num in columns[j]:
                        return False
                    columns[j].add(num)
                    
                    box_index = (i // 3) * 3 + j // 3
                    if num in boxes[box_index]:
                        return False
                    boxes[box_index].add(num)
                    
        return True

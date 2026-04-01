from typing import List

class Solution:
    def reverseSubmatrix(self, grid: List[List[int]], x: int, y: int, k: int) -> List[List[int]]:
        # Flip vertically: swap rows within the submatrix
        for i in range(k // 2):
            top_row = x + i
            bottom_row = x + k - 1 - i
            for j in range(k):
                # Swap elements in the row at columns y..y+k-1
                grid[top_row][y + j], grid[bottom_row][y + j] = grid[bottom_row][y + j], grid[top_row][y + j]
        return grid
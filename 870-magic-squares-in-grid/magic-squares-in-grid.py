from typing import List

class Solution:
    def numMagicSquaresInside(self, grid: List[List[int]]) -> int:
        rows, cols = len(grid), len(grid[0])
        count = 0

        def is_magic(r: int, c: int) -> bool:
            # Center must be 5
            if grid[r+1][c+1] != 5:
                return False

            nums = set()
            for i in range(r, r+3):
                for j in range(c, c+3):
                    if grid[i][j] < 1 or grid[i][j] > 9:
                        return False
                    nums.add(grid[i][j])

            if len(nums) != 9:
                return False

            # Check rows and columns
            for i in range(3):
                if sum(grid[r+i][c:c+3]) != 15:
                    return False
                if grid[r][c+i] + grid[r+1][c+i] + grid[r+2][c+i] != 15:
                    return False

            # Check diagonals
            if grid[r][c] + grid[r+1][c+1] + grid[r+2][c+2] != 15:
                return False
            if grid[r][c+2] + grid[r+1][c+1] + grid[r+2][c] != 15:
                return False

            return True

        for r in range(rows - 2):
            for c in range(cols - 2):
                if is_magic(r, c):
                    count += 1

        return count

        
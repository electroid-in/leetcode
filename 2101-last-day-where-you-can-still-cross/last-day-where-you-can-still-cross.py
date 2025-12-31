from typing import List
from collections import deque

class Solution:
    def latestDayToCross(self, row: int, col: int, cells: List[List[int]]) -> int:
        
        directions = [(1,0), (-1,0), (0,1), (0,-1)]
        
        def can_cross(day: int) -> bool:
            # 0 = land, 1 = water
            grid = [[0] * col for _ in range(row)]
            
            # Flood cells up to given day
            for i in range(day):
                r, c = cells[i]
                grid[r - 1][c - 1] = 1
            
            q = deque()
            visited = [[False] * col for _ in range(row)]
            
            # Start BFS from top row land cells
            for c in range(col):
                if grid[0][c] == 0:
                    q.append((0, c))
                    visited[0][c] = True
            
            while q:
                r, c = q.popleft()
                if r == row - 1:
                    return True
                
                for dr, dc in directions:
                    nr, nc = r + dr, c + dc
                    if 0 <= nr < row and 0 <= nc < col:
                        if not visited[nr][nc] and grid[nr][nc] == 0:
                            visited[nr][nc] = True
                            q.append((nr, nc))
            
            return False
        
        left, right = 0, row * col
        answer = 0
        
        while left <= right:
            mid = (left + right) // 2
            if can_cross(mid):
                answer = mid
                left = mid + 1
            else:
                right = mid - 1
        
        return answer
        
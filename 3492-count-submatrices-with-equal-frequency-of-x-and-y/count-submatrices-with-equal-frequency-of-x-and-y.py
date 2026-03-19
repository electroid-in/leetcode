class Solution:
    def numberOfSubmatrices(self, grid):
        m, n = len(grid), len(grid[0])
        
        sum_pref = [[0]*n for _ in range(m)]
        x_pref = [[0]*n for _ in range(m)]
        
        def val(c):
            if c == 'X': return 1
            if c == 'Y': return -1
            return 0
        
        for i in range(m):
            for j in range(n):
                v = val(grid[i][j])
                x = 1 if grid[i][j] == 'X' else 0
                
                sum_pref[i][j] = v
                x_pref[i][j] = x
                
                if i > 0:
                    sum_pref[i][j] += sum_pref[i-1][j]
                    x_pref[i][j] += x_pref[i-1][j]
                if j > 0:
                    sum_pref[i][j] += sum_pref[i][j-1]
                    x_pref[i][j] += x_pref[i][j-1]
                if i > 0 and j > 0:
                    sum_pref[i][j] -= sum_pref[i-1][j-1]
                    x_pref[i][j] -= x_pref[i-1][j-1]
        
        ans = 0
        
        for i in range(m):
            for j in range(n):
                if sum_pref[i][j] == 0 and x_pref[i][j] > 0:
                    ans += 1
        
        return ans
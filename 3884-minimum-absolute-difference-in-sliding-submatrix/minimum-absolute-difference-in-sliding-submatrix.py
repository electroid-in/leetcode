class Solution:
    def minAbsDiff(self, grid, k):
        m, n = len(grid), len(grid[0])
        ans = [[0] * (n - k + 1) for _ in range(m - k + 1)]

        for i in range(m - k + 1):
            for j in range(n - k + 1):
                arr = set()  # use set to keep distinct values

                # collect elements
                for x in range(i, i + k):
                    for y in range(j, j + k):
                        arr.add(grid[x][y])

                arr = sorted(arr)

                # if only one unique value → answer = 0
                if len(arr) <= 1:
                    ans[i][j] = 0
                    continue

                min_diff = float('inf')
                for t in range(1, len(arr)):
                    min_diff = min(min_diff, arr[t] - arr[t - 1])

                ans[i][j] = min_diff

        return ans
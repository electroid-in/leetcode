 int largestMagicSquare(int** grid, int m, int* gridColSize) {
    int n = gridColSize[0];

    // Prefix sums
    int rowSum[51][51] = {0};
    int colSum[51][51] = {0};
    int diag1[51][51] = {0};
    int diag2[51][51] = {0};

    // Build prefix sums
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            rowSum[i][j + 1] = rowSum[i][j] + grid[i][j];
            colSum[i + 1][j] = colSum[i][j] + grid[i][j];
            diag1[i + 1][j + 1] = diag1[i][j] + grid[i][j];
            diag2[i + 1][j] = diag2[i][j + 1] + grid[i][j];
        }
    }

    int maxK = m < n ? m : n;

    // Try largest k first
    for (int k = maxK; k >= 2; k--) {
        for (int i = 0; i + k <= m; i++) {
            for (int j = 0; j + k <= n; j++) {

                int target = rowSum[i][j + k] - rowSum[i][j];
                int valid = 1;

                // Check rows
                for (int r = i; r < i + k && valid; r++) {
                    if (rowSum[r][j + k] - rowSum[r][j] != target)
                        valid = 0;
                }

                // Check columns
                for (int c = j; c < j + k && valid; c++) {
                    if (colSum[i + k][c] - colSum[i][c] != target)
                        valid = 0;
                }

                // Check diagonals
                if (valid) {
                    int d1 = diag1[i + k][j + k] - diag1[i][j];
                    int d2 = diag2[i + k][j] - diag2[i][j + k];
                    if (d1 != target || d2 != target)
                        valid = 0;
                }

                if (valid)
                    return k;
            }
        }
    }

    return 1; // Every 1x1 grid is magic
}

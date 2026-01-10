#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minimumDeleteSum(char* s1, char* s2) {
    int n = strlen(s1);
    int m = strlen(s2);

    // Allocate DP table
    int** dp = (int**)malloc((n + 1) * sizeof(int*));
    for (int i = 0; i <= n; i++) {
        dp[i] = (int*)malloc((m + 1) * sizeof(int));
    }

    // Base cases
    dp[0][0] = 0;

    for (int i = 1; i <= n; i++) {
        dp[i][0] = dp[i - 1][0] + s1[i - 1];
    }

    for (int j = 1; j <= m; j++) {
        dp[0][j] = dp[0][j - 1] + s2[j - 1];
    }

    // Fill DP table
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                int delete_s1 = dp[i - 1][j] + s1[i - 1];
                int delete_s2 = dp[i][j - 1] + s2[j - 1];
                dp[i][j] = delete_s1 < delete_s2 ? delete_s1 : delete_s2;
            }
        }
    }

    int result = dp[n][m];

    // Free memory
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

#include <limits.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int maxDotProduct(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    static int dp[501][501];
    int NEG_INF = -1000000000;

    // Initialize DP
    for (int i = 0; i <= nums1Size; i++) {
        for (int j = 0; j <= nums2Size; j++) {
            dp[i][j] = NEG_INF;
        }
    }

    for (int i = 1; i <= nums1Size; i++) {
        for (int j = 1; j <= nums2Size; j++) {
            int product = nums1[i - 1] * nums2[j - 1];

            dp[i][j] = max(
                product,
                dp[i - 1][j - 1] + product
            );

            dp[i][j] = max(dp[i][j], dp[i - 1][j]);
            dp[i][j] = max(dp[i][j], dp[i][j - 1]);
        }
    }

    return dp[nums1Size][nums2Size];
}

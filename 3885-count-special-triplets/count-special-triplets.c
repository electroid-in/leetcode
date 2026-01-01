#include <stdlib.h>
#include <string.h>

#define MOD 1000000007
#define MAXV 200000   // enough for 2 * max(nums[i])

int specialTriplets(int* nums, int numsSize) {
    long long result = 0;

    // Frequency arrays
    int leftCount[MAXV + 1];
    int rightCount[MAXV + 1];

    memset(leftCount, 0, sizeof(leftCount));
    memset(rightCount, 0, sizeof(rightCount));

    // Initialize rightCount
    for (int i = 0; i < numsSize; i++) {
        rightCount[nums[i]]++;
    }

    // Iterate j
    for (int j = 0; j < numsSize; j++) {
        int val = nums[j];
        int target = val * 2;

        // Remove current element from right
        rightCount[val]--;

        if (target <= MAXV) {
            result = (result +
                      (long long)leftCount[target] * rightCount[target]) % MOD;
        }

        // Add current element to left
        leftCount[val]++;
    }

    return (int)result;
}

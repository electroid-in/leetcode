#include <math.h>

int sumFourDivisors(int* nums, int numsSize) {
    int totalSum = 0;

    for (int i = 0; i < numsSize; i++) {
        int n = nums[i];
        int count = 0;
        int sum = 0;

        for (int d = 1; d * d <= n; d++) {
            if (n % d == 0) {
                int other = n / d;

                if (d == other) {
                    count += 1;
                    sum += d;
                } else {
                    count += 2;
                    sum += d + other;
                }

                if (count > 4)
                    break;
            }
        }

        if (count == 4) {
            totalSum += sum;
        }
    }

    return totalSum;
}

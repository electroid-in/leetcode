#include <limits.h>  // for LLONG_MAX
#include <stdlib.h>  // for llabs

long long maxMatrixSum(int** matrix, int matrixSize, int* matrixColSize) {
    long long sumAbs = 0;
    int negCount = 0;
    long long minAbs = LLONG_MAX;

    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixColSize[i]; j++) {
            long long val = matrix[i][j];

            if (val < 0) {
                negCount++;
            }

            long long absVal = llabs(val);
            sumAbs += absVal;

            if (absVal < minAbs) {
                minAbs = absVal;
            }
        }
    }

    // If odd number of negatives, one smallest absolute value must remain negative
    if (negCount % 2 == 1) {
        sumAbs -= 2 * minAbs;
    }

    return sumAbs;
}

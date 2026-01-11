#include <stdlib.h>

int max(int a, int b) {
    return a > b ? a : b;
}

// Largest Rectangle in Histogram
int largestRectangleArea(int* heights, int n) {
    int* stack = (int*)malloc(sizeof(int) * (n + 1));
    int top = -1;
    int maxArea = 0;

    for (int i = 0; i <= n; i++) {
        int h = (i == n) ? 0 : heights[i];

        while (top >= 0 && h < heights[stack[top]]) {
            int height = heights[stack[top--]];
            int width = (top < 0) ? i : i - stack[top] - 1;
            maxArea = max(maxArea, height * width);
        }
        stack[++top] = i;
    }

    free(stack);
    return maxArea;
}

// Main function
int maximalRectangle(char** matrix, int matrixSize, int* matrixColSize) {
    if (matrixSize == 0) return 0;

    int cols = matrixColSize[0];
    int* heights = (int*)calloc(cols, sizeof(int));
    int maxArea = 0;

    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == '1')
                heights[j]++;
            else
                heights[j] = 0;
        }
        maxArea = max(maxArea, largestRectangleArea(heights, cols));
    }

    free(heights);
    return maxArea;
}

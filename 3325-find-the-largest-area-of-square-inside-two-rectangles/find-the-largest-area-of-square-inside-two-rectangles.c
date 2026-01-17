long long largestSquareArea(int** bottomLeft, int bottomLeftSize, int* bottomLeftColSize,
                            int** topRight, int topRightSize, int* topRightColSize) {
    long long maxArea = 0;
    int n = bottomLeftSize;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {

            long long left   = bottomLeft[i][0] > bottomLeft[j][0] ? bottomLeft[i][0] : bottomLeft[j][0];
            long long right  = topRight[i][0] < topRight[j][0] ? topRight[i][0] : topRight[j][0];
            long long bottom = bottomLeft[i][1] > bottomLeft[j][1] ? bottomLeft[i][1] : bottomLeft[j][1];
            long long top    = topRight[i][1] < topRight[j][1] ? topRight[i][1] : topRight[j][1];

            if (right > left && top > bottom) {
                long long width  = right - left;
                long long height = top - bottom;
                long long side = width < height ? width : height;
                long long area = side * side;

                if (area > maxArea) {
                    maxArea = area;
                }
            }
        }
    }
    return maxArea;
}

double separateSquares(int** squares, int squaresSize, int* squaresColSize) {
    double totalArea = 0.0;
    double low = 1e18, high = -1e18;

    // Compute total area and y-range
    for (int i = 0; i < squaresSize; i++) {
        double y = squares[i][1];
        double l = squares[i][2];
        totalArea += l * l;
        if (y < low) low = y;
        if (y + l > high) high = y + l;
    }

    double target = totalArea / 2.0;

    // Binary search
    for (int iter = 0; iter < 60; iter++) {
        double mid = (low + high) / 2.0;
        double areaBelow = 0.0;

        for (int i = 0; i < squaresSize; i++) {
            double y = squares[i][1];
            double l = squares[i][2];

            if (mid <= y) {
                // contributes nothing
            } else if (mid >= y + l) {
                areaBelow += l * l;
            } else {
                areaBelow += l * (mid - y);
            }
        }

        if (areaBelow >= target) {
            high = mid;
        } else {
            low = mid;
        }
    }

    return low;
}

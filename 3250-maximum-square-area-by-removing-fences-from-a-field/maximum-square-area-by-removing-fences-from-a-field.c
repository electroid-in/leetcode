#include <stdlib.h>

#define MOD 1000000007LL

int cmp(const void* a, const void* b) {
    return (*(int*)a) - (*(int*)b);
}

int maximizeSquareArea(int m, int n, int* hFences, int hSize, int* vFences, int vSize) {
    // Add boundaries
    int* H = (int*)malloc((hSize + 2) * sizeof(int));
    int* V = (int*)malloc((vSize + 2) * sizeof(int));

    H[0] = 1;
    H[hSize + 1] = m;
    for (int i = 0; i < hSize; i++) H[i + 1] = hFences[i];

    V[0] = 1;
    V[vSize + 1] = n;
    for (int i = 0; i < vSize; i++) V[i + 1] = vFences[i];

    hSize += 2;
    vSize += 2;

    qsort(H, hSize, sizeof(int), cmp);
    qsort(V, vSize, sizeof(int), cmp);

    // Compute all possible heights
    int hCount = hSize * (hSize - 1) / 2;
    int* heights = (int*)malloc(hCount * sizeof(int));
    int idx = 0;
    for (int i = 0; i < hSize; i++) {
        for (int j = i + 1; j < hSize; j++) {
            heights[idx++] = H[j] - H[i];
        }
    }

    // Compute all possible widths
    int vCount = vSize * (vSize - 1) / 2;
    int* widths = (int*)malloc(vCount * sizeof(int));
    idx = 0;
    for (int i = 0; i < vSize; i++) {
        for (int j = i + 1; j < vSize; j++) {
            widths[idx++] = V[j] - V[i];
        }
    }

    qsort(heights, hCount, sizeof(int), cmp);
    qsort(widths, vCount, sizeof(int), cmp);

    // Two-pointer scan for maximum common value
    int i = hCount - 1, j = vCount - 1;
    while (i >= 0 && j >= 0) {
        if (heights[i] == widths[j]) {
            long long side = heights[i];
            long long area = (side * side) % MOD;
            free(H); free(V); free(heights); free(widths);
            return (int)area;
        } else if (heights[i] > widths[j]) {
            i--;
        } else {
            j--;
        }
    }

    free(H); free(V); free(heights); free(widths);
    return -1;
}

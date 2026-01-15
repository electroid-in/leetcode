#include <stdlib.h>

int cmp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int longestConsecutive(int* arr, int size) {
    if (size == 0) return 0;

    qsort(arr, size, sizeof(int), cmp);

    int longest = 1, curr = 1;
    for (int i = 1; i < size; i++) {
        if (arr[i] == arr[i - 1] + 1) {
            curr++;
        } else {
            if (curr > longest) longest = curr;
            curr = 1;
        }
    }
    if (curr > longest) longest = curr;

    return longest;
}

int maximizeSquareHoleArea(int n, int m,
                           int* hBars, int hBarsSize,
                           int* vBars, int vBarsSize) {
    int maxH = longestConsecutive(hBars, hBarsSize) + 1;
    int maxV = longestConsecutive(vBars, vBarsSize) + 1;

    int side = maxH < maxV ? maxH : maxV;
    return side * side;
}

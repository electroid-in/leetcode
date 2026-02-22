class Solution {
public:
    int binaryGap(int n) {
        int lastPos = -1;   // Position of previous 1
        int maxGap = 0;
        int position = 0;
        
        while (n > 0) {
            if (n & 1) {  // If current bit is 1
                if (lastPos != -1) {
                    maxGap = max(maxGap, position - lastPos);
                }
                lastPos = position;
            }
            n >>= 1;  // Shift right
            position++;
        }
        
        return maxGap;
    }
};
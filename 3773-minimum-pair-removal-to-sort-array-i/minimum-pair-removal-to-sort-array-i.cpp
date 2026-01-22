class Solution {
public:
    int minimumPairRemoval(vector<int>& nums) {
        int ops = 0;
        while (true) {
            // Check if array is non-decreasing
            bool sorted = true;
            for (int i = 1; i < nums.size(); i++) {
                if (nums[i] < nums[i-1]) {
                    sorted = false;
                    break;
                }
            }
            if (sorted) break;

            // Find minimum sum of adjacent pair
            int minSum = nums[0] + nums[1];
            int idx = 0;
            for (int i = 1; i < nums.size() - 1; i++) {
                int sum = nums[i] + nums[i+1];
                if (sum < minSum) {
                    minSum = sum;
                    idx = i;
                }
            }

            // Replace pair with sum
            nums[idx] = minSum;
            nums.erase(nums.begin() + idx + 1);

            ops++;
        }
        return ops;
    }
};

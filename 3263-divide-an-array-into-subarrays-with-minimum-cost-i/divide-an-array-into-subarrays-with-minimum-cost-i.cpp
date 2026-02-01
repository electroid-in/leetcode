class Solution {
public:
    int minimumCost(vector<int>& nums) {
        int n = nums.size();
        int ans = INT_MAX;

        for (int i = 1; i <= n - 2; i++) {
            for (int j = i + 1; j <= n - 1; j++) {
                ans = min(ans, nums[0] + nums[i] + nums[j]);
            }
        }

        return ans;
    }
};

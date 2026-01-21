class Solution {
public:
    vector<int> minBitwiseArray(vector<int>& nums) {
        vector<int> ans;
        
        for (int p : nums) {
            // Special case: no solution for 2
            if (p == 2) {
                ans.push_back(-1);
                continue;
            }
            
            // Count trailing ones in p
            int t = 0;
            int temp = p;
            while (temp & 1) {
                t++;
                temp >>= 1;
            }
            
            // If no trailing ones, no solution (theoretically won't happen for odd primes)
            if (t == 0) {
                ans.push_back(-1);
            } else {
                // Minimum x
                int x = p - (1 << (t - 1));
                ans.push_back(x);
            }
        }
        
        return ans;
    }
};

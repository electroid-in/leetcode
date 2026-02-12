class Solution {
public:
    int longestBalanced(string s) {
        int n = s.size();
        int ans = 0;

        for (int l = 0; l < n; l++) {
            vector<int> freq(26, 0);
            int distinct = 0;
            int maxFreq = 0;

            for (int r = l; r < n; r++) {
                int idx = s[r] - 'a';

                if (freq[idx] == 0)
                    distinct++;

                freq[idx]++;
                maxFreq = max(maxFreq, freq[idx]);

                int len = r - l + 1;

                if (maxFreq * distinct == len) {
                    ans = max(ans, len);
                }
            }
        }

        return ans;
    }
};

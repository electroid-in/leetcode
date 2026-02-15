class Solution {
public:
    int longestBalanced(string s) {
        int n = s.size();
        int ans = 1;  // <-- fix here (minimum is 1)

        // ---------- Case 1: Single letter ----------
        int count = 1;
        for (int i = 1; i < n; i++) {
            if (s[i] == s[i - 1]) {
                count++;
            } else {
                count = 1;
            }
            ans = max(ans, count);
        }

        // ---------- Case 2: Two letters ----------
        vector<pair<char,char>> pairs = {
            {'a','b'}, {'a','c'}, {'b','c'}
        };

        for (auto [x, y] : pairs) {
            unordered_map<int,int> mp;
            mp[0] = -1;
            int diff = 0;

            for (int i = 0; i < n; i++) {
                if (s[i] == x) diff++;
                else if (s[i] == y) diff--;
                else {
                    mp.clear();
                    mp[0] = i;
                    diff = 0;
                    continue;
                }

                if (mp.count(diff)) {
                    ans = max(ans, i - mp[diff]);
                } else {
                    mp[diff] = i;
                }
            }
        }

        // ---------- Case 3: Three letters ----------
        unordered_map<long long,int> mp;
        mp[0] = -1;

        int a = 0, b = 0, c = 0;

        for (int i = 0; i < n; i++) {
            if (s[i] == 'a') a++;
            else if (s[i] == 'b') b++;
            else c++;

            int d1 = a - b;
            int d2 = a - c;

            long long key = ((long long)d1 << 32) ^ d2;

            if (mp.count(key)) {
                ans = max(ans, i - mp[key]);
            } else {
                mp[key] = i;
            }
        }

        return ans;
    }
};

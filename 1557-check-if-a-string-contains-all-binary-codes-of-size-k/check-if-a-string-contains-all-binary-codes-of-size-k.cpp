class Solution {
public:
    bool hasAllCodes(string s, int k) {
        if (k > s.size()) return false; // Not enough length

        unordered_set<string> seen;
        int total = 1 << k; // 2^k possible binary codes

        for (int i = 0; i <= s.size() - k; i++) {
            seen.insert(s.substr(i, k));
            if (seen.size() == total) return true; // All codes found
        }

        return false;
    }
};
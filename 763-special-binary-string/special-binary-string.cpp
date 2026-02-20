class Solution {
public:
    string makeLargestSpecial(string s) {
        vector<string> parts;
        int count = 0, start = 0;
        
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '1') count++;
            else count--;
            
            // Found a balanced special substring
            if (count == 0) {
                // Recursively solve inside substring
                string inner = makeLargestSpecial(s.substr(start + 1, i - start - 1));
                parts.push_back("1" + inner + "0");
                start = i + 1;
            }
        }
        
        // Sort in descending lexicographical order
        sort(parts.begin(), parts.end(), greater<string>());
        
        // Concatenate all parts
        string result;
        for (auto &p : parts) {
            result += p;
        }
        
        return result;
    }
};
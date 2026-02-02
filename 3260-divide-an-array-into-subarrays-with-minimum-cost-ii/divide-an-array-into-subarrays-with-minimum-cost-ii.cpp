class Solution {
public:
    long long minimumCost(vector<int>& nums, int k, int dist) {
        int n = nums.size();
        long long ans = LLONG_MAX;

        multiset<int> small, big;
        long long sumSmall = 0;

        auto balance = [&]() {
            while ((int)small.size() > k - 2) {
                auto it = prev(small.end());
                sumSmall -= *it;
                big.insert(*it);
                small.erase(it);
            }
            while ((int)small.size() < k - 2 && !big.empty()) {
                auto it = big.begin();
                sumSmall += *it;
                small.insert(*it);
                big.erase(it);
            }
        };

        auto add = [&](int x) {
            if ((int)small.size() < k - 2) {
                small.insert(x);
                sumSmall += x;
            } else if (!small.empty() && x < *prev(small.end())) {
                auto it = prev(small.end());
                sumSmall += x - *it;
                big.insert(*it);
                small.erase(it);
                small.insert(x);
            } else {
                big.insert(x);
            }
            balance();
        };

        auto remove = [&](int x) {
            auto it = small.find(x);
            if (it != small.end()) {
                sumSmall -= x;
                small.erase(it);
            } else {
                big.erase(big.find(x));
            }
            balance();
        };

        /* initialize window for i1 = 1 */
        for (int i = 2; i <= min(n - 1, 1 + dist); i++) {
            add(nums[i]);
        }

        if ((int)small.size() == k - 2)
            ans = min(ans, nums[0] + nums[1] + sumSmall);

        for (int i1 = 2; i1 < n; i1++) {
            remove(nums[i1]);                 // i1+1 becomes invalid
            if (i1 + dist <= n - 1)
                add(nums[i1 + dist]);         // new enters window

            if ((int)small.size() == k - 2)
                ans = min(ans, nums[0] + nums[i1] + sumSmall);
        }

        return ans;
    }
};

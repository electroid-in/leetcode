class Solution {
public:
    int minimumPairRemoval(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return 0;

        vector<long long> val(nums.begin(), nums.end());
        vector<int> left(n), right(n);
        vector<bool> alive(n, true);

        for (int i = 0; i < n; i++) {
            left[i] = i - 1;
            right[i] = (i + 1 < n ? i + 1 : -1);
        }

        // Count initial violations
        int bad = 0;
        for (int i = 0; i + 1 < n; i++) {
            if (val[i] > val[i + 1]) bad++;
        }
        if (bad == 0) return 0;

        // Min-heap of (sum, index)
        priority_queue<
            pair<long long,int>,
            vector<pair<long long,int>>,
            greater<>
        > pq;

        for (int i = 0; i + 1 < n; i++) {
            pq.push({val[i] + val[i + 1], i});
        }

        int ops = 0;

        while (bad > 0) {
            auto [s, i] = pq.top();
            pq.pop();

            if (!alive[i] || right[i] == -1) continue;
            int j = right[i];
            if (!alive[j] || val[i] + val[j] != s) continue;

            // Remove old violations
            if (left[i] != -1 && val[left[i]] > val[i]) bad--;
            if (val[i] > val[j]) bad--;
            if (right[j] != -1 && val[j] > val[right[j]]) bad--;

            // Merge i and j
            val[i] += val[j];
            alive[j] = false;
            right[i] = right[j];
            if (right[j] != -1) left[right[j]] = i;

            // Add new violations
            if (left[i] != -1 && val[left[i]] > val[i]) bad++;
            if (right[i] != -1 && val[i] > val[right[i]]) bad++;

            // Push new adjacent sums
            if (left[i] != -1)
                pq.push({val[left[i]] + val[i], left[i]});
            if (right[i] != -1)
                pq.push({val[i] + val[right[i]], i});

            ops++;
        }

        return ops;
    }
};

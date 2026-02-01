class Solution {
public:
    static const long long BASE = 911382323;
    static const long long MOD  = 972663749;

    long long minimumCost(
        string source,
        string target,
        vector<string>& original,
        vector<string>& changed,
        vector<int>& cost
    ) {
        const long long INF = 1e18;
        int n = source.size();

        /* ---------- Rolling Hash ---------- */
        vector<long long> powBase(n + 1), hs(n + 1), ht(n + 1);
        powBase[0] = 1;

        for (int i = 0; i < n; i++) {
            powBase[i + 1] = (powBase[i] * BASE) % MOD;
            hs[i + 1] = (hs[i] * BASE + source[i]) % MOD;
            ht[i + 1] = (ht[i] * BASE + target[i]) % MOD;
        }

        auto getHash = [&](const vector<long long>& h, int l, int r) {
            return (h[r] - h[l] * powBase[r - l] % MOD + MOD) % MOD;
        };

        /* ---------- String Graph ---------- */
        unordered_map<string, int> id;
        vector<string> strs;

        auto getId = [&](const string& s) {
            if (!id.count(s)) {
                id[s] = strs.size();
                strs.push_back(s);
            }
            return id[s];
        };

        for (int i = 0; i < original.size(); i++) {
            getId(original[i]);
            getId(changed[i]);
        }

        int m = strs.size();
        vector<vector<long long>> dist(m, vector<long long>(m, INF));

        for (int i = 0; i < m; i++) dist[i][i] = 0;

        for (int i = 0; i < original.size(); i++) {
            int u = getId(original[i]);
            int v = getId(changed[i]);
            dist[u][v] = min(dist[u][v], (long long)cost[i]);
        }

        // Floyd–Warshall
        for (int k = 0; k < m; k++)
            for (int i = 0; i < m; i++)
                for (int j = 0; j < m; j++)
                    if (dist[i][k] < INF && dist[k][j] < INF)
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

        /* ---------- Group by Length ---------- */
        unordered_map<int,
            unordered_map<long long,
                unordered_map<long long, long long>>> trans;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                if (dist[i][j] == INF) continue;
                if (strs[i].size() != strs[j].size()) continue;

                int L = strs[i].size();
                long long h1 = 0, h2 = 0;

                for (char c : strs[i]) h1 = (h1 * BASE + c) % MOD;
                for (char c : strs[j]) h2 = (h2 * BASE + c) % MOD;

                auto& mp = trans[L][h1];
                if (!mp.count(h2) || mp[h2] > dist[i][j])
                    mp[h2] = dist[i][j];
            }
        }

        /* ---------- DP ---------- */
        vector<long long> dp(n + 1, INF);
        dp[n] = 0;

        for (int i = n - 1; i >= 0; i--) {
            if (source[i] == target[i]) {
                dp[i] = dp[i + 1];
            }

            for (auto& [L, mp] : trans) {
                if (i + L > n) continue;

                long long hs1 = getHash(hs, i, i + L);
                long long ht1 = getHash(ht, i, i + L);

                if (mp.count(hs1) && mp[hs1].count(ht1)) {
                    dp[i] = min(dp[i], mp[hs1][ht1] + dp[i + L]);
                }
            }
        }

        return dp[0] >= INF ? -1 : dp[0];
    }
};

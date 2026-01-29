#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minCost(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();
        using ll = long long;
        const ll INF = (ll)4e15;
        int N = m * n;

        // Flatten and sort cells by value (ascending)
        vector<array<int,3>> cells; cells.reserve(N);
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                cells.push_back({grid[i][j], i, j});
        sort(cells.begin(), cells.end());

        // map (r,c) -> sorted index
        vector<vector<int>> id(m, vector<int>(n));
        for (int p = 0; p < N; ++p) id[cells[p][1]][cells[p][2]] = p;

        // dist[t][p] = min cost to reach sorted-index p using <= t teleports (after relax)
        vector<vector<ll>> dist(k + 1, vector<ll>(N, INF));
        dist[0][ id[0][0] ] = 0; // start at (0,0)

        int dr[2] = {1, 0};
        int dc[2] = {0, 1};

        for (int t = 0; t <= k; ++t) {
            // 1) Fully relax normal moves (right/down) on layer t using Dijkstra
            priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;
            for (int p = 0; p < N; ++p) if (dist[t][p] < INF) pq.push({dist[t][p], p});

            while (!pq.empty()) {
                auto [cost, p] = pq.top(); pq.pop();
                if (cost != dist[t][p]) continue;

                int r = cells[p][1], c = cells[p][2];
                for (int d = 0; d < 2; ++d) {
                    int nr = r + dr[d], nc = c + dc[d];
                    if (nr < m && nc < n) {
                        int np = id[nr][nc];
                        ll ncst = cost + (ll)grid[nr][nc];
                        if (ncst < dist[t][np]) {
                            dist[t][np] = ncst;
                            pq.push({ncst, np});
                        }
                    }
                }
            }

            // 2) Teleport transition (group-wise suffix minimum) into t+1
            if (t == k) break;
            vector<ll> next(N, INF);
            ll best = INF;
            int p = N - 1;
            while (p >= 0) {
                // find group of equal values ending at p: group indices [g, p]
                int val = cells[p][0];
                int g = p;
                while (g - 1 >= 0 && cells[g-1][0] == val) --g;

                // compute groupMin = min dist[t][q] for q in [g..p]
                ll groupMin = INF;
                for (int q = g; q <= p; ++q) groupMin = min(groupMin, dist[t][q]);

                best = min(best, groupMin);
                // assign best to all items in this group
                for (int q = g; q <= p; ++q) next[q] = min(next[q], best);

                p = g - 1;
            }
            // merge next into dist[t+1]
            for (int i = 0; i < N; ++i) if (next[i] < dist[t+1][i]) dist[t+1][i] = next[i];
        }

        int target = id[m-1][n-1];
        ll ans = INF;
        for (int t = 0; t <= k; ++t) ans = min(ans, dist[t][target]);
        return ans >= INF ? -1 : (int)ans;
    }
};

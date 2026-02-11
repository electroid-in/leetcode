class Solution {
public:
    struct SegTree {
        int n;
        vector<int> mn, mx, lazy;

        SegTree(int n): n(n) {
            mn.assign(4*n, 0);
            mx.assign(4*n, 0);
            lazy.assign(4*n, 0);
        }

        void push(int node) {
            if (lazy[node] != 0) {
                for (int child : {node*2, node*2+1}) {
                    mn[child] += lazy[node];
                    mx[child] += lazy[node];
                    lazy[child] += lazy[node];
                }
                lazy[node] = 0;
            }
        }

        void pull(int node) {
            mn[node] = min(mn[node*2], mn[node*2+1]);
            mx[node] = max(mx[node*2], mx[node*2+1]);
        }

        void update(int node, int start, int end, int l, int r, int val) {
            if (r < start || end < l) return;
            if (l <= start && end <= r) {
                mn[node] += val;
                mx[node] += val;
                lazy[node] += val;
                return;
            }
            push(node);
            int mid = (start + end) / 2;
            update(node*2, start, mid, l, r, val);
            update(node*2+1, mid+1, end, l, r, val);
            pull(node);
        }

        int query(int node, int start, int end, int l, int r) {
            if (r < start || end < l) return -1;

            if (l <= start && end <= r) {
                if (mn[node] > 0 || mx[node] < 0) return -1;
                if (start == end) return start;
            }

            if (start == end) return -1;

            push(node);
            int mid = (start + end) / 2;

            // 🔥 Search RIGHT first (we want max r)
            int right = query(node*2+1, mid+1, end, l, r);
            if (right != -1) return right;
            return query(node*2, start, mid, l, r);
        }
    };

    int longestBalanced(vector<int>& nums) {
        int n = nums.size();

        unordered_map<int, vector<int>> pos;
        for (int i = 0; i < n; i++)
            pos[nums[i]].push_back(i);

        // pointer to current occurrence index
        unordered_map<int, int> ptr;

        SegTree seg(n);

        // Initialize for l = 0
        for (auto &[val, vec] : pos) {
            int sign = (val % 2 ? 1 : -1);
            int p = vec[0];
            seg.update(1, 0, n-1, p, n-1, sign);
            ptr[val] = 0;
        }

        int ans = 0;

        for (int l = 0; l < n; l++) {

            int r = seg.query(1, 0, n-1, l, n-1);
            if (r != -1)
                ans = max(ans, r - l + 1);

            int val = nums[l];
            int sign = (val % 2 ? 1 : -1);

            ptr[val]++;

            int next = (ptr[val] < pos[val].size())
                       ? pos[val][ptr[val]]
                       : n;

            seg.update(1, 0, n-1, 0, next-1, -sign);
        }

        return ans;
    }
};


//verified at 'https://beta.atcoder.jp/contests/abc014/submissions/1918746'
//LCA
struct LCA {
        const int LOGM = 30;
        vector<int> depth;
        vector<vector<int>> parent;
        LCA(int root, const vector<vector<int>> &g) {
                int n = g.size();
                depth.resize(n);
                parent.resize(LOGM);
                for (int i = 0; i < LOGM; i ++) parent[i].resize(n);
                function<void (int, int, int)> dfs = [&](int u, int prev, int d) {
                        parent[0][u] = prev;
                        depth[u] = d;
                        for (auto v : g[u]) if (v != prev) dfs(v, u, d + 1);
                };
                dfs(root, -1, 0);
                for (int k = 0; k < LOGM - 1; k ++) {
                        for (int i = 0; i < n; i ++) {
                                if (parent[k][i] < 0) parent[k + 1][i] = -1;
                                else parent[k + 1][i] = parent[k][parent[k][i]];
                        }
                }
        }
        int lca(int u, int v) { 
                if (depth[u] > depth[v]) swap(u, v);
                for (int k = 0; k < LOGM; k ++) {
                        if ((depth[v] - depth[u]) >> k & 1) { 
                                v = parent[k][v];
                        }
                }
                if (u == v) return u;
                for (int k = LOGM - 1; k >= 0; k --) {
                        if (parent[k][u] != parent[k][v]) {
                                u = parent[k][u];
                                v = parent[k][v];
                        }
                }
                return parent[0][u];
        }
        int dist(int u, int v) {
                return depth[u] + depth[v] - 2 * depth[lca(u, v)];
        }
};
//

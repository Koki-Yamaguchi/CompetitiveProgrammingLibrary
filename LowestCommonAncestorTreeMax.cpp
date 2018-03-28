struct LowestCommonAncestorTreeMax {
        const int LOGM = 30;
        vector<int> depth, par_w;
        vector<vector<int>> parent, parmax;
        LowestCommonAncestorTree(int root, const vector<vector<pair<int, int>>> &g) {
                int n = g.size();
                depth.resize(n);
                par_w.resize(n);
                parent.resize(LOGM);
                parmax.resize(LOGM);
                for (int i = 0; i < LOGM; i ++) { 
                        parent[i].resize(n);
                        parmax[i].resize(n);
                }
                function<void (int, int, int)> dfs = [&](int u, int prev, int d) {
                        parent[0][u] = prev;
                        parmax[0][u] = par_w[u];
                        depth[u] = d;
                        for (auto e : g[u]) { 
                                int v = e.first;
                                if (v != prev) { 
                                        par_w[v] = e.second;
                                        dfs(v, u, d + 1);
                                }
                        }
                };
                dfs(root, -1, 0);
                for (int k = 0; k < LOGM - 1; k ++) {
                        for (int i = 0; i < n; i ++) {
                                if (parent[k][i] < 0) { 
                                        parent[k + 1][i] = -1;
                                } else { 
                                        parent[k + 1][i] = parent[k][parent[k][i]];
                                        if (parent[k + 1][i] >= 0) {
                                                parmax[k + 1][i] = max(parmax[k][i], parmax[k][parent[k][i]]);
                                        }
                                }
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
        int getmax(int v, int ancestor) {
                int res = 0;
                int d = depth[v] - depth[ancestor];
                for (int k = 0; k < LOGM; k ++) {
                        if ((d >> k) & 1) {
                                res = max(res, parmax[k][v]);
                                v = parent[k][v];
                        }
                }
                return res;
        }
};

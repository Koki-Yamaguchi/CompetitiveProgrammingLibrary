struct LowLink {
        vector<pair<int, int>> bridge;
        vector<int> articulation, ord, low;
        vector<bool> used;
        vector<vector<int>> g;
        int n, k = 0;
        LowLink(const vector<vector<int>> &g) : g(g) {
                n = g.size();
                ord.resize(n, -1);
                low.resize(n, -1);
                used.resize(n, false);
        }
        void dfs(int u, int prev) {
                used[u] = true;
                ord[u] = k ++;
                low[u] = ord[u];
                bool is_articulation = false;
                int cnt = 0;
                for (auto v : g[u]) if (v != prev) {
                        if (!used[v]) {
                                cnt ++;
                                dfs(v, u);
                                low[u] = min(low[u], low[v]);
                                if (low[v] > ord[u]) {
                                        bridge.emplace_back(min(u, v), max(u, v));
                                } 
                                if (prev != -1 && low[v] >= ord[u]) {
                                        is_articulation = true;
                                }
                        } else {
                                low[u] = min(low[u], ord[v]);
                        }
                }
                if (prev == -1 && cnt > 1) is_articulation = true;
                if (is_articulation) articulation.push_back(u);
        }
};

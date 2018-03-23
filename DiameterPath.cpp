//verified by 'http://codeforces.com/contest/911/problem/F'
vector<int> DiameterPath(const vector<vector<int>> &g) {
        int n = g.size();
        if (n == 1) return vector<int> { 0 };
        //find the farthest point from the start
        auto farthest = [&](int start) {
                vector<int> depth(n);
                function<void (int, int, int)> get_depth = [&](int u, int prev, int d) {
                        depth[u] = d;
                        for (auto v : g[u]) if (v != prev) {
                                get_depth(v, u, d + 1);
                        }
                };
                get_depth(start, -1, 0);
                int maxd = 0;
                int res = 0;
                for (int i = 0; i < n; i ++) {
                        if (depth[i] > maxd) {
                                maxd = depth[i];
                                res = i;
                        }
                }
                return res;
        };
        //get end points
        int s = farthest(0);
        int t = farthest(s);
        //construct a diameter path
        vector<int> diameter_path;
        function<void (int, int, vector<int> &)> construct = [&](int u, int prev, vector<int> &path) {
                if (u == t) {
                        diameter_path = path;
                        return;
                }
                for (auto v : g[u]) if (v != prev) {
                        path.push_back(v);
                        construct(v, u, path);
                        path.pop_back();
                }
        };
        vector<int> tmp;
        tmp.push_back(s);
        construct(s, -1, tmp);
        return diameter_path;
}

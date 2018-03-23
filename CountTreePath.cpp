#include <cstdio>
#include <algorithm>
#include <vector>
#include <functional>
using namespace std;

int OneCentroid(int root, const vector<vector<int>> &g, const vector<bool> &dead) {
        static vector<int> sz(g.size()); //caution
        function<void (int, int)> get_sz = [&](int u, int prev) {
                sz[u] = 1;
                for (auto v : g[u]) if (v != prev && !dead[v]) {
                        get_sz(v, u);
                        sz[u] += sz[v];
                }
        };
        get_sz(root, -1);
        int n = sz[root];
        function<int (int, int)> dfs = [&](int u, int prev) {
                for (auto v : g[u]) if (v != prev && !dead[v]) {
                        if (sz[v] >= n / 2) {
                                return dfs(v, u);
                        }
                }
                return u;
        };
        return dfs(root, -1);
}

int count_pairs(vector<int> &distances, int k) {
        int cnt = 0;
        sort(distances.begin(), distances.end());
        int last = (int) distances.size();
        for (int i = 0; i < (int) distances.size(); i ++) {
                while (last > 0 && distances[i] + distances[last - 1] > k) last --;
                int self = last > i;
                cnt += last - self;
        }
        return cnt / 2;
}


int CountTreePath(const vector<vector<int>> &g, int k) {
        int res = 0;
        int n = (int) g.size();
        vector<bool> dead(n, false);
        function<void (int)> rec = [&](int start) {
                int c = OneCentroid(start, g, dead);
                dead[c] = true;
                //compute something within a subtree alone (without the centroid)
                for (auto u : g[c]) if (!dead[u]) {
                        rec(u);
                }
                //compute something with the centroid
                vector<int> distances;
                distances.push_back(0);
                for (auto u : g[c]) if (!dead[u]) {
                        vector<int> tmp_distances;
                        function<void (int, int, int)> enumerate_paths = [&](int u, int prev, int distance) {
                                tmp_distances.push_back(distance);
                                for (auto v : g[u]) if (v != prev && !dead[v]) {
                                        enumerate_paths(v, u, distance + 1);
                                }
                        };
                        enumerate_paths(u, c, 1);
                        res -= count_pairs(tmp_distances, k);
                        res += count_pairs(tmp_distances, k - 1);
                        distances.insert(distances.end(), tmp_distances.begin(), tmp_distances.end());
                }
                res += count_pairs(distances, k);
                res -= count_pairs(distances, k - 1);
                //
                dead[c] = false;
        };
        rec(0);
        return res;
}

int main() {
        int n, k;
        scanf("%d%d", &n, &k);
        vector<vector<int>> g(n);
        for (int i = 0; i < n - 1; i ++) {
                int a, b;
                scanf("%d%d", &a, &b);
                a --, b --;
                g[a].push_back(b);
                g[b].push_back(a);
        }
        int ans = CountTreePath(g, k);
        printf("%d\n", ans);
        return 0;
}

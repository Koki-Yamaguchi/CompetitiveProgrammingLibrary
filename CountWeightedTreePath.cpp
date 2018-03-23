#include <cstdio>
#include <algorithm>
#include <vector>
#include <functional>
using namespace std;

struct edge { int to, cost; };

vector<int> Centroid(int root, const vector<vector<edge>> &g, const vector<bool> &dead) {
        int n = g.size(), alive = 0;
        function<void (int, int)> count_alive = [&](int u, int prev) {
                alive ++;
                for (auto e : g[u]) { 
                        int v = e.to;
                        if (v != prev && !dead[v]) {
                                count_alive(v, u);
                        }
                }
        };
        count_alive(root, -1);
        vector<int> centroid, sz(n);
        function<void (int, int)> dfs = [&](int u, int prev) {
                sz[u] = 1;
                bool is_centroid = true;
                for (auto e : g[u]) { 
                        int v = e.to;
                        if (v != prev && !dead[v]) {
                                dfs(v, u);
                                sz[u] += sz[v];
                                if (sz[v] > alive / 2) is_centroid = false;
                        }
                }
                if (alive - sz[u] > alive / 2) is_centroid = false;
                if (is_centroid) centroid.push_back(u);
        };
        dfs(root, -1);
        return centroid;
}

int count_pairs(vector<int> &distances, int k) {
        int cnt = 0;
        sort(distances.begin(), distances.end());
        int last = (int) distances.size();
        for (int i = 0; i < distances.size(); i ++) {
                while (last > 0 && distances[i] + distances[last - 1] > k) last --;
                int self = last > i;
                cnt += last - self;
        }
        return cnt / 2;
}


int CountWeightedTreePath(const vector<vector<edge>> &g, int k) {
        int res = 0;
        int n = (int) g.size();
        vector<bool> dead(n, false);
        function<void (int)> rec = [&](int start) {
                auto centroid = Centroid(start, g, dead);
                int c = centroid[0];
                dead[c] = true;
                //within a subtree alone
                for (auto e : g[c]) {
                        int u = e.to;
                        if (dead[u]) continue;
                        rec(u);
                }
                //use c as a part of the path
                vector<int> distances;
                distances.push_back(0);
                for (auto e : g[c]) {
                        int u = e.to;
                        if (dead[u]) continue;
                        vector<int> tmp_distances;
                        function<void (int, int, int)> enumerate_paths = [&](int u, int prev, int distance) {
                                tmp_distances.push_back(distance);
                                for (auto e : g[u]) {
                                        int v = e.to;
                                        if (v == prev || dead[v]) continue;
                                        enumerate_paths(v, u, distance + e.cost);
                                }
                        };
                        enumerate_paths(u, c, e.cost);
                        res -= count_pairs(tmp_distances, k);
                        distances.insert(distances.end(), tmp_distances.begin(), tmp_distances.end());
                }
                res += count_pairs(distances, k);
                dead[c] = false;
        };
        rec(0);
        return res;
}

int main() {
        int n, k;
        scanf("%d%d", &n, &k);
        vector<vector<edge>> g(n);
        for (int i = 0; i < n - 1; i ++) {
                int a, b, c;
                scanf("%d%d%d", &a, &b, &c);
                a --, b --;
                g[a].push_back({b, c});
                g[b].push_back({a, c});
        }
        int ans = CountWeightedTreePath(g, k);
        printf("%d\n", ans);
        return 0;
}

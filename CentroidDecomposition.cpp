#include <iostream>
#include <vector>
#include <functional>
#include <map>
using namespace std;

//verified at 
//'https://csacademy.com/contest/round-58/task/path-inversions/'
//'http://codeforces.com/contest/914/problem/E'
int OneCentroid(int root, const vector<vector<int>> &g, const vector<bool> &dead) {
        static vector<int> sz(g.size());
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
                        if (sz[v] > n / 2) {
                                return dfs(v, u);
                        }
                }
                return u;
        };
        return dfs(root, -1);
}
void CentroidDecomposition(const vector<vector<int>> &g) {
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
                //piyo
                dead[c] = false;
        };
        rec(0);
}

int main() {
        int n;
        scanf("%d", &n);
        vector<vector<int>> g(n);
        for (int i = 0; i < n - 1; i ++) {
                int a, b;
                scanf("%d %d", &a, &b);
                a --, b --;
                g[a].push_back(b);
                g[b].push_back(a);
        }
        vector<bool> dead(n);
        cerr << OneCentroid(0, g, dead) << endl;
}

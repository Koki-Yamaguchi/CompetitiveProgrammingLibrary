#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <set>
#include <string>
#include <iostream>
#include <cassert>
#include <cmath>
using namespace std;

// subtree(v): [in[v], out[v])
// heavy path(v, the last vertex in ascending heavy path from v): [in[next[v]], in[v]]
struct SimpleHeavyLightDecomposition {
        int n, t = 0;
        vector<int> in, out, next, sz, rin;
        vector<vector<int>> g;
        SimpleHeavyLightDecomposition(int _n, int root, vector<vector<int>> const &_g) {
                n = _n;
                g = _g;
                in.resize(n);
                out.resize(n);
                next.resize(n);
                sz.resize(n);
                rin.resize(n + 1);
                dfs(root);
                hld(root);
        }
        void dfs(int u) {
                sz[u] = 1;
                for (auto &v : g[u]) {
                        dfs(v);
                        sz[u] += sz[v];
                        if (sz[v] > sz[g[u][0]]) {
                                swap(v, g[u][0]);
                        }
                }
        }
        void hld(int u) {
                in[u] = t ++;
                rin[in[u]] = u;
                for (auto v : g[u]) {
                        next[v] = (v == g[u][0] ? next[u] : v);
                        hld(v);
                }
                out[u] = t;
        }
};

int main() {
        int n;
        scanf("%d", &n);
        vector<vector<int>> g(n);
        for (int i = 1; i < n; i ++) {
                int p;
                scanf("%d", &p);
                p --;
                g[p].push_back(i);
        }
        SimpleHeavyLightDecomposition hld(n, 0, g);
        for (int i = 0; i < n; i ++) {
        }
        return 0;
}

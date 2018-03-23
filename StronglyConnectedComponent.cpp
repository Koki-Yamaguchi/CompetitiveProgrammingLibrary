#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

struct StronglyConnectedComponent {
        int n;
        vector<bool> used;
        vector<int> order, cmp;
        vector<vector<int>> g, rg;
        StronglyConnectedComponent(int x) {
                n = x;
                g.resize(x);
                rg.resize(x);
                used.resize(x);
                cmp.resize(x);
        }
        void add_edge(int from, int to) {
                g[from].push_back(to);
                rg[to].push_back(from);
        }
        void dfs(int u) {
                used[u] = true;
                for (auto v : g[u]) if (!used[v]) {
                        dfs(v);
                }
                order.push_back(u);
        }
        void rdfs(int u, int k) {
                used[u] = true;
                cmp[u] = k;
                for (auto v : rg[u]) if (!used[v]) {
                        rdfs(v, k);
                }
        }
        int init() {
                used.assign(n, false);
                for (int u = 0; u < n; u ++) {
                        if (!used[u]) {
                                dfs(u);
                        }
                }
                used.assign(n, false);
                int k = 0;
                for (int i = order.size() - 1; i >= 0; i --) {
                        if (!used[order[i]]) {
                                rdfs(order[i], k ++);
                        }
                }
                return k;
        }
};

int main() {
        int n, m;
        scanf("%d %d", &n, &m);
        StronglyConnectedComponent scc(n);
        for (int i = 0; i < m; i ++) {
                int a, b;
                scanf("%d %d", &a, &b);
                a --, b --;
                scc.add_edge(a, b);
        }
        scc.init();
        for (int i = 0; i < n; i ++) {
                cerr << scc.cmp[i] << endl;
        }
        return 0;
}

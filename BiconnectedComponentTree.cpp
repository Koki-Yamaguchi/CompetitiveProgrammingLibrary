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

//e2i[edge] -> index of the edge
//tree index : [0, 1, ..., bc.size() - 1] -> component
//tree index : [bc.size(), bc.size() + 1, ..., bc.size() + art.size() - 1] -> articulation
//cmp[index of edge] -> index of the node of the contructed tree
//cmp_node[index of node] -> -1 if it's not articulation, otherwise index of the node of the constructed tree
struct BiconnectedComponentTree {
        vector<int> ord, low, art, cmp, cmp_node;
        vector<bool> used;
        vector<vector<int>> g, tree;
        vector<vector<pair<int, int>>> bc;
        vector<pair<int, int>> tmp;
        map<pair<int, int>, int> e2i;
        int n, m, k = 0;
        BiconnectedComponentTree(const vector<vector<int>> &g, const map<pair<int, int>, int> &e2i) : g(g), e2i(e2i) {
                n = g.size();
                m = e2i.size();
                cmp_node.resize(n, -1);
                cmp.resize(m, -1);
                ord.resize(n, -1);
                low.resize(n, -1);
                used.resize(n, false);
        }
        void dfs(int u, int prev) {
                used[u] = true;
                ord[u] = k ++;
                low[u] = ord[u];
                bool is_art = false;
                int cnt = 0;
                for (auto v : g[u]) if (v != prev) {
                        if (ord[v] < ord[u]) { 
                                tmp.emplace_back(min(u, v), max(u, v));
                        }
                        if (!used[v]) {
                                cnt ++;
                                dfs(v, u);
                                low[u] = min(low[u], low[v]);
                                if (prev != -1 && low[v] >= ord[u]) {
                                        is_art = true;
                                }
                                if (low[v] >= ord[u]) {
                                        bc.push_back({});
                                        while (true) {
                                                pair<int, int> e = tmp.back();
                                                bc.back().emplace_back(e);
                                                tmp.pop_back();
                                                if (min(u, v) == e.first && max(u, v) == e.second) {
                                                        break;
                                                }
                                        }
                                }
                        } else {
                                low[u] = min(low[u], ord[v]);
                        }
                }
                if (prev == -1 && cnt > 1) is_art = true;
                if (is_art) art.push_back(u);
        }
        void build() {
                dfs(0, -1);
                for (int i = 0; i < (int) bc.size(); i ++) {
                        for (auto e : bc[i]) {
                                cmp[e2i[make_pair(min(e.first, e.second), max(e.first, e.second))]] = i;
                        }
                }
                tree.resize(bc.size() + art.size());
                for (int i = 0; i < (int) art.size(); i ++) {
                        int j = i + (int) bc.size();
                        cmp_node[art[i]] = j;
                        int u = art[i];
                        set<int> tmp;
                        for (auto v : g[u]) {
                                int t = cmp[e2i[make_pair(min(u, v), max(u, v))]];
                                if (tmp.count(t) == 0) {
                                        tmp.insert(t);
                                }
                        }
                        for (auto v : tmp) {
                                tree[j].push_back(v);
                                tree[v].push_back(j);
                        }
                }
        }
};

int main() {
        int n, m;
        scanf("%d%d", &n, &m);
        vector<vector<int>> g(n);
        map<pair<int, int>, int> e2i;
        for (int i = 0; i < m; i ++) {
                int a, b;
                scanf("%d%d", &a, &b);
                g[a].push_back(b);
                g[b].push_back(a);
                e2i[make_pair(min(a, b), max(a, b))] = i;
        }
        BiconnectedComponentTree bct(g, e2i);
        bct.build();
        return 0;
}
